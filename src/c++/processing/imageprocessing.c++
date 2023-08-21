#include "imageprocessing.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QtEndian>
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>
#include <QtCore/QDateTime>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtConcurrent/QtConcurrent>
#include <QuasarSDK/CRC>
#include <LPVL/Math>
#include <SDK/GeoMath>
#include "map/models/imagemodel.h"
#include "config/paths.h"
#include "config/settings.h"
#include "config/internalconfig.h"
#include "arrayreader.h"

using namespace Processing;

ImageProcessing* ImageProcessing::get() { static ImageProcessing instance; return &instance; }

ImageProcessing::ImageProcessing(QObject* parent)
  : QObject{parent}
  , m_model(new Map::ImageModel(this))
  , m_progress(0)
  , m_total(0)
  , m_processed(0)
{
  Config::InternalConfig::get();
  qRegisterMetaType<Map::TelescopicImage>("Map::TelescopicImage");
  qRegisterMetaType<Map::StripImage>("Map::StripImage");
  qRegisterMetaType<vector<uint8_t>>("vector<uint8_t>");

  connect(this, &ImageProcessing::processImageFinished, this, &ImageProcessing::passImage, Qt::QueuedConnection);
  connect(this, &ImageProcessing::concurrencyFinished, this, [this](){
    m_processed++;
    this->setProgress((float)m_processed / (float)m_total);
  }, Qt::QueuedConnection);
}

void ImageProcessing::processList(QList<QString> list)
{
  qDebug() << "[PROCESSING] Received list of" << list.size() << "images and binaries";

  m_total = list.size();
  m_processed = 0;
  this->setProgress(0);

  QFuture<void> wrap = QtConcurrent::run([this, list](){
    QThreadPool pool1;
    pool1.setMaxThreadCount(ICFG<int>("PROCESSING_CONCURRENCY_THREADS_TELESCOPIC"));

    QThreadPool pool2;
    pool2.setMaxThreadCount(ICFG<int>("PROCESSING_CONCURRENCY_THREADS_STRIP"));

    for(const QString& filename : list)
    {
      ImageType T = filename.endsWith(".bin") ? Strip : Telescopic;
      switch (T)
      {
        case Telescopic:
        {
          QFuture<void> future = QtConcurrent::run(&pool1, [=](){
            this->asyncProcess(filename);
          });
          break;
        }
        default:
        {
          qCritical() << "[PROCESSING] Incorrect image list format";
          break;
        }
      }
    }
  });
}

void ImageProcessing::asyncProcess(const QString& filename)
{
  Map::TelescopicImage image;
  try
  {
    image = decodeTelescopic(Config::Paths::lod(0) + "/" + filename);
  }
  catch(const std::runtime_error& err)
  {
    qCritical() << "[PROCESSING] Caught exception";
    qCritical() << err.what();
    return;
  }

  image.filename = filename;
  image.opacity = ICFG<float>("PROCESSING_IMAGE_INITIAL_OPACITY");
  image.shown = ICFG<bool>("PROCESSING_IMAGE_INITIAL_VISIBILITY");
  image.mercator_zoom_level = SDK::Cartography::mqi_zoom_level(image.meta.latitude, image.meta.dx);

  QImage image_data(image.path.first);
  if(image_data.isNull()) {
    qCritical() << "[PROCESSING] Bad image file";
  }

  image.meta.ly = static_cast<float>(image_data.height());

  QString target_filename = filename;
  target_filename.chop(3);
  target_filename += "png";

  if(Config::Settings::get()->value<bool>("image/cut") and image.meta.image_type == 0)
    image_data = cutImage(image);

  bool ret = image_data.save(Config::Paths::lod(0) + "/" + target_filename);
  if(ret)
    qInfo() << "[PROCESSING] Image saved successfully";
  else
    qCritical() << "[PROCESSING] Failed to save image";

  image.path.first = Config::Paths::lod(0) + "/" + target_filename;
  QFile::remove(Config::Paths::lod(0) + "/" + filename);

  emit concurrencyFinished();
  emit processImageFinished(image);
}

QByteArray ImageProcessing::fileToByteArray(const QString& path)
{
  QFile file(path);
  if(not file.open(QIODevice::ReadOnly))
  {
    qCritical().noquote() << "[PROCESSING] Error opening file |" << path << "| for converting to raw bytes data";
    return {};
  }

  return file.readAll();
}

Map::TelescopicImage ImageProcessing::decodeTelescopic(const QString& path)
{
  Map::TelescopicImage image;
  image.path.first = path;
  QByteArray data = fileToByteArray(image.path.first);

  char* data_ptr = data.data();
  auto* marker = reinterpret_cast<uint16_t*>(data_ptr + image.header.JPEG_HEADER_SIZE);

  if(*marker != image.header.meta_marker and *marker != qFromBigEndian<uint16_t>(image.header.meta_marker))
    throw std::runtime_error("[PROCESSING] Marker mismatch exception");

  auto* meta_size = reinterpret_cast<uint16_t*>(data_ptr + image.header.JPEG_HEADER_SIZE + sizeof(uint16_t));
  *meta_size = qToBigEndian(*meta_size) - sizeof(uint16_t);
  memcpy(&image.meta, (data_ptr + image.header.JPEG_HEADER_SIZE + sizeof(uint32_t)), *meta_size);

  char* crc_data = (char*)&image.meta;
  uint16_t crc16 = QuasarSDK::Utils::crc16(crc_data, sizeof(Map::ImageMetadata) - sizeof(uint16_t));

  image.valid = crc16 == image.meta.crc16;
  if(not image.valid)
    qWarning().noquote().nospace() << "[PROCESSING] Image CRC16 seems to be incorrect: expected 0x"
                                   << Qt::hex << crc16 << ", received 0x" << image.meta.crc16 << Qt::dec;

  if(Config::Settings::get()->value<bool>("image/radians"))
  {
    image.meta.angle = LPVL::rad2deg(image.meta.angle);
    image.meta.drift_angle = Config::Settings::get()->value<bool>("image/drift-angle")
                           ? LPVL::rad2deg(image.meta.drift_angle) : 0;
    image.meta.div = LPVL::rad2deg(image.meta.div);
  };

  if(qIsNaN(image.meta.drift_angle))
    image.meta.drift_angle = 0;

  return image;
}

QImage ImageProcessing::cutImage(const Map::TelescopicImage& image) noexcept
{
  QImage image_data(image.path.first);
  QImage sample(image_data.width(), image_data.height(), QImage::Format_ARGB32_Premultiplied);
  sample.fill(QColor(254, 254, 254));
  image_data.setAlphaChannel(sample);

  QPainter painter;
  QPainterPath path;
  QBrush brush(Qt::transparent, Qt::SolidPattern);
  QPolygon p1, p2;

  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::transparent);
  painter.begin(&image_data);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.setPen(QPen(Qt::transparent, 10));
  painter.setRenderHint(QPainter::Antialiasing);

  const int top[8] =
    {
      0, (int)((image.meta.ly / 2) - 2 * image.meta.x0 * tan(LPVL::deg2rad((image.meta.div - Config::Settings::get()->value<float>("image/div-correction")) / 2))),
      0, 0,
      (int)image.meta.lx, 0,
      (int)image.meta.lx, (int)((image.meta.ly / 2) - (2 * image.meta.x0 + image.meta.lx) * tan(LPVL::deg2rad((image.meta.div - Config::Settings::get()->value<float>("image/div-correction")) / 2)))
    };

  const int bottom[8] =
    {
      0, (int)((image.meta.ly / 2) + 2 * image.meta.x0 * tan(LPVL::deg2rad((image.meta.div - Config::Settings::get()->value<float>("image/div-correction")) / 2))),
      0, (int)image.meta.ly,
      (int)image.meta.lx, (int)image.meta.ly,
      (int)image.meta.lx, (int)((image.meta.ly / 2) + (2 * image.meta.x0 + image.meta.lx) * tan(LPVL::deg2rad((image.meta.div - Config::Settings::get()->value<float>("image/div-correction")) / 2)))
    };

  p1.setPoints(4, top);
  p2.setPoints(4, bottom);
  painter.drawPolygon(p1);
  painter.drawPolygon(p2);
  path.addPolygon(p1);
  path.addPolygon(p2);

  painter.fillPath(path, brush);
  painter.end();

  return image_data;
}

Map::ImageModel* ImageProcessing::model() { return this->m_model; }
void ImageProcessing::passImage(Map::TelescopicImage image) { model()->add(image); }

bool ImageProcessing::exists(const QString& name)
{
  for(const Map::Image& image : *model()->direct())
  {
    if(image.filename == name)
      return true;

    if(image.filename.chopped(4) == name.chopped(4))
      return true;
  }
  return false;
}

int ImageProcessing::indexFrom(const QString& name) noexcept
{
  for(size_t i = 0; i < model()->direct()->size(); ++i)
  {
    if(model()->direct()->at(i).filename == name)
      return i;
    if(model()->direct()->at(i).filename.chopped(4) == name.chopped(4))
      return i;
  }

  return -1;
}

float ImageProcessing::progress() const { return m_progress; }
void ImageProcessing::setProgress(float other) {
  if (qFuzzyCompare(m_progress, other * 100))
    return;
  m_progress = other * 100;
  emit progressChanged();
}
