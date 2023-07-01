#include "streamprocessing.h"
#include <QtCore/QDebug>
#include <QtCore/QFile> // todo rm & to base64
#include <QtCore/QDateTime> //
#include <QtGui/QImage> //
#include <SDK/Math>
#include <SDK/GeoMath>
#include "config/paths.h" //
#include "config/internalconfig.h"
#include "processing/imageprocessing.h"
#include "processing/arrayreader.h"
#include "map/models/stripmodel.h"

namespace Processing
{

  StreamProcessing* StreamProcessing::get() { static StreamProcessing instance; return &instance; }
  StreamProcessing::StreamProcessing(QObject* parent)
    : QObject(parent)
  {
    connect(this, &StreamProcessing::processingFinished, this, &StreamProcessing::passChunk);
    connect(this, &StreamProcessing::passQueue, this, &StreamProcessing::processChunk);
    connect(this, &StreamProcessing::finishedQueue, this, [](){
      qDebug() << "$ [STREAM] Queue finished";
    });
  }

  Map::StripModel* StreamProcessing::model() { return ImageProcessing::get()->stripModel(); }

  void StreamProcessing::append(const QByteArray& data) noexcept
  {
    m_queue.push(data);
    qInfo() << "$ " << data.size();
    qDebug() << "$ [STREAM] Current queue size:" << m_queue.size();

    if(m_queue.size() == 1)
    {
      emit passQueue();
      qDebug() << "$ [STREAM] Starting processing of queue";
    }
  }

  void StreamProcessing::processChunk() noexcept
  {
    if(m_queue.empty())
    {
      emit finishedQueue();
      return;
    }

    QByteArray chunk = m_queue.front();
    m_queue.pop();

    const int MAX_PACKAGE_SIZE = ICFG<int>("PROCESSING_STRIP_PACKAGE_MAX_SIZE");

    Map::StripImage image;

    const uint8_t* data = reinterpret_cast<uint8_t*>(chunk.data());
    int data_size = chunk.size();

    const int header_size = sizeof(Map::StripHeaderMetadata) + sizeof(Map::StripFormatMetadata) + sizeof(Map::StripNavigationMetadata);
    uint8_t header[header_size];
    uint8_t buf[MAX_PACKAGE_SIZE - header_size];
    float fbuf[MAX_PACKAGE_SIZE - header_size];

    ArrayReader<uint8_t> array_reader((uint8_t*)data);

    int x = 0;
    int y = 0;
    std::vector<float> fmatrix;

    bool navigation_read = false;
    while(array_reader.readed() < data_size)
    {
      if((data_size - array_reader.readed()) < header_size)
        break;

      array_reader.read(header, header_size);
      ArrayReader<uint8_t>header_reader(header);

      Map::StripHeaderMetadata head;
      Map::StripNavigationMetadata nav;
      Map::StripFormatMetadata img;

      header_reader.read((uint8_t*)&head, sizeof(Map::StripHeaderMetadata));

      if(head.marker != 0xDEFA and head.marker != 0xFADE)
      {
        if(not m_queue.empty())
          emit passQueue();
        return;
      }

      header_reader.read((uint8_t*)&nav, sizeof(Map::StripNavigationMetadata));
      header_reader.read((uint8_t*)&img, sizeof(Map::StripFormatMetadata));

      if(head.cnt == 0)
      {
        x = img.nx;
        y += img.ny;
      }

      if(not navigation_read)
      {
        image.coordinate = { SDK::rad2deg(nav.latitude), SDK::rad2deg(nav.longitude) };
        image.azimuth = img.course;
        image.lx = img.nx;
        image.ly = img.ny;
        image.dx = img.dx;
        image.offset_x = img.x0;
        image.offset_y = static_cast<float>(static_cast<float>(img.y) / 10);
        navigation_read = true;
      }

      array_reader.read((uint8_t*)buf, head.size);

      // запись промежуточного результата в матрицу
      for(int i = 0; i < head.size; i++)
      {
        if(i >= MAX_PACKAGE_SIZE - header_size)
          break;
        auto f = static_cast<float>(static_cast<float>(buf[i]) * img.k);
        fmatrix.push_back(f);
      }
    }

    // Эти значения нужно пересчитывать каждый раз при выводе матрицы на экран
    // Лучше сделать вычисление максимального значения рекуррентно
    const float max_value = *max_element(fmatrix.begin(), fmatrix.end());
    const float k = max_value / 255.0f;

    qInfo().noquote().nospace() << "$ [STREAM] Matrix size: { " << x << ", " << y << " }";
    qInfo().noquote().nospace() << "$ [STREAM] Max value: { " << max_value << " }";
    qInfo().noquote().nospace() << "$ [STREAM] Size: { " << x * y << " }";
    qInfo().noquote().nospace() << "$ [STREAM] Coords: { " << image.coordinate.latitude()
                                << ", " << image.coordinate.longitude()  << " }";

    int out_size = x * y;
    uint8_t out_buf[out_size];

    // обратное масштабирование
    for(int i = 0; i < out_size; i++)
      out_buf[i] = fmatrix[i] / k;

    vector<uint8_t> output(out_buf, out_buf + out_size);

    QImage strip_result(x, y, QImage::Format_Grayscale16);
    vector<vector<float>> image_result;
    image_result.resize(y);
    for(size_t i = 0; i < y; ++i)
    {
      image_result[i].resize(x);
      for(size_t j = 0; j < x; ++j)
        image_result[i][j] = output[j + x * i];
    }

    for(size_t row = 0; row < image_result.size(); ++row)
    {
      for(size_t column = 0; column < image_result[row].size(); ++column)
      {
        float t = (image_result[row][column]);
        uint8_t d[4] = { static_cast<uint8_t>(t), static_cast<uint8_t>(t), static_cast<uint8_t>(t), 255 };
        auto* rs = (uint32_t*)d;
        strip_result.setPixel(column, row, *rs);
      }
    }

    image.filename = "strip_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".png";

    QString result_path = Config::Paths::lod(0) + "/" + image.filename;
    strip_result.save(result_path, "PNG");
    image.path.first = result_path;
    image.valid = true;
    qInfo() << "$ [STREAM] Saved strip image to" << result_path;

    image.opacity = ICFG<float>("PROCESSING_IMAGE_INITIAL_OPACITY");
    image.shown = ICFG<bool>("PROCESSING_IMAGE_INITIAL_VISIBILITY");
    image.mercator_zoom_level = SDK::Cartography::mqi_zoom_level(image.coordinate.latitude(), image.dx);

    emit processingFinished(image);
    if(not m_queue.empty())
      emit passQueue();
  }

  void StreamProcessing::passChunk(Map::StripImage image) { model()->add(image); }
} // Processing