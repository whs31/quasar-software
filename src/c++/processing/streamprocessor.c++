//
// Created by whs31 on 20.07.23.
//

#include "streamprocessor.h"
#include <cmath>
#include <QtCore/QDebug>
#include <QtCore/QBuffer>
#include <QtGui/QImage>
#include <QuasarSDK/Common>
#include <QuasarSDK/ImageDatagrams>
#include "config/internalconfig.h"
#include "processing/arrayreader.h"
#include "map/models/streamsegmentmodel.h"

using namespace QuasarSDK;
using std::vector;

namespace Processing
{
  StreamProcessor::StreamProcessor(QObject* parent)
    : QObject(parent)
    , m_model(new ::Map::StreamSegmentModel(this))
  {
    connect(this, &StreamProcessor::finished, this, &StreamProcessor::pass);
    connect(this, &StreamProcessor::queuePassed, this, &StreamProcessor::processChunk);
    connect(this, &StreamProcessor::queueFinished, this, [](){
      qDebug() << "$ [STREAM] Queue finished";
    });
  }

  ::Map::StreamSegmentModel* StreamProcessor::model() const { return m_model; }

  void StreamProcessor::process(const QByteArray& data) noexcept
  {
    m_queue.push(data);
    qDebug() << "$ [STREAM] Current queue size:" << m_queue.size();

    if(m_queue.size() == 1)
    {
      emit queuePassed();
      qDebug() << "$ [STREAM] Starting processing of queue";
    }
  }

  void StreamProcessor::processChunk() noexcept
  {
    if(m_queue.empty())
    {
      emit queueFinished();
      return;
    }

    QByteArray chunk = m_queue.front();
    m_queue.pop();

    const int MAX_PACKAGE_SIZE = ICFG<int>("PROCESSING_STRIP_PACKAGE_MAX_SIZE");

    MapImageSegment image;

    const uint8_t* data = reinterpret_cast<uint8_t*>(chunk.data());
    int data_size = chunk.size();

    const int header_size = sizeof(Datagrams::StripImageChunkHeader);
    uint8_t header[header_size];
    uint8_t buf[MAX_PACKAGE_SIZE - header_size];
    float fbuf[MAX_PACKAGE_SIZE - header_size];

    ArrayReader<uint8_t> array_reader((uint8_t*)data);

    int x = 0;
    int y = 0;
    vector<float> fmatrix;

    bool navigation_read = false;
    while(array_reader.readed() < data_size)
    {
      if((data_size - array_reader.readed()) < header_size)
        break;

      array_reader.read(header, header_size);
      ArrayReader<uint8_t>header_reader(header);

      Datagrams::StripImageChunkID head;
      Datagrams::StripImageChunkNav nav;
      Datagrams::StripImageChunkFormat img;

      header_reader.read((uint8_t*)&head, sizeof(Datagrams::StripImageChunkID));

      if(head.marker != 0xDEFA and head.marker != 0xFADE)
      {
        if(not m_queue.empty())
            emit queuePassed();
        return;
      }

      header_reader.read((uint8_t*)&nav, sizeof(Datagrams::StripImageChunkNav));
      header_reader.read((uint8_t*)&img, sizeof(Datagrams::StripImageChunkFormat));

      if(head.cnt == 0)
      {
        x = img.nx;
        y += img.ny;
      }

      if(not navigation_read)
      {
        image.setCoordinate(Utils::rad2deg(nav.latitude), Utils::rad2deg(nav.longitude));
        image.setAzimuth(Utils::rad2deg(nav.course));
        image.setRectSize(QSizeF(img.nx, img.ny));
        image.setRatio(img.dx);
        float x = -img.x0;
        float y = static_cast<float>(img.y)/ 10.0f;
        image.setOffset(QPointF(x * cos(image.azimuth()) + y * sin(image.azimuth()),
                                -x * sin(image.azimuth()) + y * cos(image.azimuth())));
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

    qInfo().noquote().nospace() << "$ [STREAM] Coords: { " << image.coordinate().latitude()
                                << ", " << image.coordinate().longitude()  << " }";
    qInfo().noquote().nospace() << "$ [STREAM] Azimuth: { " << image.azimuth() << " }";

    int out_size = x * y;
    uint8_t out_buf[out_size];

    // обратное масштабирование
    for(int i = 0; i < out_size; i++)
      out_buf[i] = static_cast<uint8_t>(fmatrix[i] / k);

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
    //strip_result = strip_result.mirrored(true, true);

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

    QByteArray temporary;
    QBuffer buffer(&temporary);
    buffer.open(QIODevice::WriteOnly);
    strip_result.save(&buffer, "PNG");

    image.setData(temporary);
    image.setVisible(ICFG<bool>("PROCESSING_IMAGE_INITIAL_VISIBILITY"));
    image.setOpacity(ICFG<float>("PROCESSING_IMAGE_INITIAL_OPACITY"));

    emit finished(image);
    if(not m_queue.empty())
        emit queuePassed();
  }

  void StreamProcessor::pass(const QuasarSDK::Map::MapImageSegment& segment) const { model()->add(segment); }
} // Processing