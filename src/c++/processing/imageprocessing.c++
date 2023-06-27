#include "imageprocessing.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QtEndian>
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtConcurrent/QtConcurrent>
#include <LPVL/Math>
#include <LPVL/Crypto>
#include <SDK/GeoMath>
#include "map/models/imagemodel.h"
#include "map/models/stripmodel.h"
#include "config/paths.h"
#include "config/config.h"
#include "config/internalconfig.h"
#include "arrayreader.h"

using namespace Processing;

ImageProcessing* ImageProcessing::get() { static ImageProcessing instance; return &instance; }

ImageProcessing::ImageProcessing(QObject* parent)
  : QObject{parent}
  , m_model(new Map::ImageModel(this))
  , m_stripModel(new Map::StripModel(this))
  , m_progress(0)
  , m_total(0)
  , m_processed(0)
{
  Config::InternalConfig::get();
  qRegisterMetaType<Map::TelescopicImage>("Map::TelescopicImage");
  qRegisterMetaType<Map::StripImage>("Map::StripImage");
  qRegisterMetaType<vector<uint8_t>>("vector<uint8_t>");

  connect(this, &ImageProcessing::processImageFinished, this, &ImageProcessing::passImage, Qt::QueuedConnection);
  connect(this, &ImageProcessing::processStripFinished, this, &ImageProcessing::passStrip, Qt::QueuedConnection);
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
        case Strip:
        {
          QFuture<void> future = QtConcurrent::run(&pool2, [=](){
            this->asyncStripProcess(filename);
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

  if(CONFIG(overrideImageHeight))
    image.meta.ly = static_cast<float>(image_data.height());

  QString target_filename = filename;
  target_filename.chop(3);
  target_filename += "png";

  if(CONFIG(cutImage) and image.meta.image_type == 0)
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

void ImageProcessing::asyncStripProcess(const QString& filename)
{
  const int MAX_PACKAGE_SIZE = ICFG<int>("PROCESSING_STRIP_PACKAGE_MAX_SIZE");
  Map::StripImage image;
  image.filename = filename;
  image.path.first = Config::Paths::lod(0) + "/" + filename;
  QByteArray file = fileToByteArray(image.path.first);

  const uint8_t* data = reinterpret_cast<uint8_t*>(file.data());
  int data_size = file.size();
  const int header_size = sizeof(Map::StripHeaderMetadata) + sizeof(Map::StripFormatMetadata) + sizeof(Map::StripNavigationMetadata);
  ArrayReader<uint8_t> ar((uint8_t*)data);
  auto* header = (uint8_t*)malloc(header_size);
  auto* buf = (uint8_t*)malloc(MAX_PACKAGE_SIZE - header_size);
  auto* fbuf = (float*)malloc((MAX_PACKAGE_SIZE - header_size) * sizeof(float));

  int x = 0;
  int y = 0;
  std::vector<float> fmatrix;

  bool navigation_read = false;
  while(ar.readed() < data_size)
  {
    if((data_size - ar.readed()) < header_size)
      break;

    ar.read(header, header_size);
    ArrayReader<uint8_t>header_reader(header);

    Map::StripHeaderMetadata head;
    Map::StripNavigationMetadata nav;
    Map::StripFormatMetadata img;

    header_reader.read((uint8_t*)&head, sizeof(Map::StripHeaderMetadata));
    header_reader.read((uint8_t*)&nav, sizeof(Map::StripNavigationMetadata));
    header_reader.read((uint8_t*)&img, sizeof(Map::StripFormatMetadata));

    if(head.cnt == 0)
    {
      x = img.nx;
      y += img.ny;
    }

    if(not navigation_read)
    {
      image.coordinate = { nav.latitude, nav.longitude };
      image.azimuth = nav.track_ang;
      image.lx = img.nx;
      image.ly = img.ny;
      image.dx = img.dx;
      navigation_read = true;
    }

    ar.read((uint8_t*) buf, head.size );

    // запись промежуточного результата в матрицу
    for(int i = 0; i < head.size; i++)
      fmatrix.push_back( (float)buf[i] * img.k);
  }

  // Эти значения нужно пересчитывать каждый раз при выводе матрицы на экран
  // лучше сделать вычисление максимального значения рекуррентно,
  // т.к. с ростом матрицы многократно увеличится объем обработки и будет lag
  const float max_value = *max_element(fmatrix.begin(), fmatrix.end());
  const float k = max_value / 255.0f;

  qInfo().noquote().nospace() << "$ [PROCESSING] Matrix size: { " << x << ", " << y << " }";
  qInfo().noquote().nospace() << "$ [PROCESSING] Max value: { " << max_value << " }";
  qInfo().noquote().nospace() << "$ [PROCESSING] Size: { " << x * y << " }";
  qInfo().noquote().nospace() << "$ [PROCESSING] Coords: { " << image.coordinate.latitude()
                              << ", " << image.coordinate.longitude()  << " }";

  int out_size = x * y;
  auto* out_buf = (uint8_t*)malloc(out_size);

  // обратное масштабирование
  for(int i = 0; i < out_size; i++)
    out_buf[i] = fmatrix[i] / k;

  if(ICFG<bool>("PROCESSING_DEBUG_SAVE_STRIP_MATRIX"))
  {
    QFile file(Config::Paths::lod(0) + "/matrix_" + filename);
    if(file.open(QIODevice::WriteOnly))
    {
      file.write(reinterpret_cast<const char*>(out_buf), out_size);
      file.close();
    }
    else
      qWarning() << "[PROCESSING] Failed to save debug strip data to file.";
  }

  vector<uint8_t> output(out_buf, out_buf + out_size);

  if(ICFG<bool>("PROCESSING_DEBUG_SHOW_STRIP_WINDOW"))
    emit stripVector8bit(output, y, x);

  QImage strip_result(x, y, QImage::Format_Grayscale16);
  vector<vector<float>> image_result;
  image_result.resize(y);
  for(size_t i = 0; i < y; ++i)
  {
    image_result[i].resize(x);
    for(size_t j = 0; j < x; ++j)
      image_result[i][j] = output[j + x * i];
  }
  float max = *std::max_element(output.begin(), output.end());
  for(size_t row = 0; row < image_result.size(); ++row)
  {
    for(size_t column = 0; column < image_result[row].size(); ++column)
    {
      float t = (image_result[row][column] * 255) / max;
      uint8_t d[4] = {static_cast<uint8_t>(t), static_cast<uint8_t>(t), static_cast<uint8_t>(t), 255};
      auto* rs = (uint32_t*)d;
      strip_result.setPixel(column, row, *rs);
    }
  }

  QString result_path = Config::Paths::lod(0) + "/" + filename.chopped(3) + "png";
  strip_result.save(result_path, "PNG");
  image.path.first = result_path;
  image.valid = true;
  qInfo() << "$ [PROCESSING] Saved strip image to" << result_path;

  free((void*)header);
  free((void*)buf);
  free((void*)fbuf);
  free((void*)out_buf);

  if(not ICFG<bool>("PROCESSING_DEBUG_PRESERVE_BINARY"))
    QFile::remove(Config::Paths::lod(0) + "/" + filename);

  emit concurrencyFinished();
  emit passStrip(image);
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
  uint16_t crc16 = LPVL::crc16(crc_data, sizeof(Map::ImageMetadata) - sizeof(uint16_t));

  image.valid = crc16 == image.meta.crc16;
  if(not image.valid)
    qWarning().noquote().nospace() << "[PROCESSING] Image CRC16 seems to be incorrect: expected 0x"
                                   << Qt::hex << crc16 << ", received 0x" << image.meta.crc16 << Qt::dec;

  if(CONFIG(useRadians))
  {
    image.meta.angle = LPVL::rad2deg(image.meta.angle) + CONFIG(angleCorrection);
    image.meta.drift_angle = CONFIG(useDriftAngle) ? LPVL::rad2deg(image.meta.drift_angle) : 0;
    image.meta.div = LPVL::rad2deg(image.meta.div);
  }
  else
    image.meta.angle += CONFIG(angleCorrection);

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
      0, (int)((image.meta.ly / 2) - 2 * image.meta.x0 * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection)) / 2))),
      0, 0,
      (int)image.meta.lx, 0,
      (int)image.meta.lx, (int)((image.meta.ly / 2) - (2 * image.meta.x0 + image.meta.lx) * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection)) / 2)))
    };

  const int bottom[8] =
    {
      0, (int)((image.meta.ly / 2) + 2 * image.meta.x0 * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection)) / 2))),
      0, (int)image.meta.ly,
      (int)image.meta.lx, (int)image.meta.ly,
      (int)image.meta.lx, (int)((image.meta.ly / 2) + (2 * image.meta.x0 + image.meta.lx) * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection)) / 2)))
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
Map::StripModel* ImageProcessing::stripModel() { return this->m_stripModel; }
void ImageProcessing::passImage(Map::TelescopicImage image) { model()->add(image); }
void ImageProcessing::passStrip(Map::StripImage image) { stripModel()->add(image); }

bool ImageProcessing::exists(const QString& name)
{
  for(const Map::Image& image : *model()->direct())
  {
    if(image.filename == name)
      return true;

    if(image.filename.chopped(4) == name.chopped(4))
      return true;
  }

  for(const Map::StripImage& image : *stripModel()->direct())
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
