#include "imageprocessing.h"
#include "map/imagemodel.h"
#include "map/entities/stripimage.h"
#include "config/paths.h"
#include "config/config.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QtEndian>
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtConcurrent/QtConcurrent>
#include <cmath>
#include <LPVL/Math>
#include <LPVL/Crypto>
#include <CCL/Geomath>

using namespace Processing;

ImageProcessing::ImageProcessing(QObject* parent)
    : QObject{parent}
    , m_model(new Map::ImageModel(this))
{
    qRegisterMetaType<Map::Image>("Map::Image");
    qRegisterMetaType<Map::StripImage>("Map::StripImage");
    qRegisterMetaType<vector<uint8_t>>("vector<uint8_t>");

    connect(this, &ImageProcessing::processImageFinished, this, &ImageProcessing::passImage, Qt::QueuedConnection);
}

void ImageProcessing::processList(const QList<QString>& list)
{
    qDebug() << "[PROCESSING] Received list of" << list.size() << "images and binaries";

    QThreadPool pool1;
    pool1.setMaxThreadCount(2);

    QThreadPool pool2;
    pool2.setMaxThreadCount(4);

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
                qCritical() << "?";
                break;
            }
        }
    }

    setProcessingImage(true);
}

void ImageProcessing::asyncProcess(const QString& filename)
{
    Map::Image image;

    image.filename = filename;
    image.path.first = Config::Paths::lod(0) + "/" + filename;
    QByteArray data = fileToByteArray(image.path.first);

    char* data_ptr = data.data();
    uint16_t* marker = reinterpret_cast<uint16_t*>(data_ptr + image.header.JPEG_HEADER_SIZE);
    if(*marker != image.header.meta_marker and *marker != qFromBigEndian<uint16_t>(image.header.meta_marker))
    {
        qCritical().noquote().nospace() << "[PROCESSING] Marker mismatch: expected 0x"
                                        << Qt::hex << image.header.meta_marker << " or 0x"
                                        << qFromBigEndian<uint16_t>(image.header.meta_marker)
                                        << ", received 0x" << *marker << Qt::dec;
        return;
    }

    // заполнение структуры метаданными
    uint16_t* meta_size = reinterpret_cast<uint16_t*>(data_ptr + image.header.JPEG_HEADER_SIZE
                                                      + sizeof(uint16_t));
    *meta_size = qToBigEndian(*meta_size) - sizeof(uint16_t);
    memcpy(&image.meta, (data_ptr + image.header.JPEG_HEADER_SIZE + sizeof(uint32_t)), *meta_size);

    // проверка контрольной суммы
    char* crc_data = (char*)&image.meta;
    uint16_t crc16 = LPVL::crc16(crc_data, sizeof(Map::ImageMetadata) - sizeof(uint16_t));

    image.valid = crc16 == image.meta.crc16;
    if(not image.valid)
        qWarning().noquote().nospace() << "[PROCESSING] Image CRC16 seems to be incorrect: expected 0x"
                                       << Qt::hex << crc16 << ", received 0x" << image.meta.crc16 << Qt::dec;

    // геометрические преобразования
    if(CONFIG(useRadians))
    {
        image.meta.angle = LPVL::rad2deg(image.meta.angle)
                           + CONFIG(angleCorrection);
        image.meta.drift_angle = CONFIG(useDriftAngle)
                                     ? LPVL::rad2deg(image.meta.drift_angle)
                                     : 0;
        image.meta.div = LPVL::rad2deg(image.meta.div);
    }
    else
        image.meta.angle += CONFIG(angleCorrection);

    QImage image_data(image.path.first);

    if(CONFIG(overrideImageHeight))
        image.meta.ly = image_data.height();

    QString target_filename = filename;
    target_filename.chop(3);
    target_filename += "png";

    if(not CONFIG(cutImage))
    {
        bool ret = image_data.save(Config::Paths::lod(0) + "/" + target_filename);
        if(ret)
            qInfo() << "[PROCESSING] Image saved successfully without correction";
        else
            qCritical() << "[PROCESSING] Failed to save image";
    }
    else
    {
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

        const int top[8] = {
            0, (int)((image.meta.ly / 2) - 2
               * image.meta.x0
               * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
               / 2))),
            0, 0,
            (int)image.meta.lx, 0,
            (int)image.meta.lx, (int)((image.meta.ly / 2) -
                                (2 * image.meta.x0 + image.meta.lx)
                                * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
                                / 2)))
        };

        const int bottom[8] = {
            0, (int)((image.meta.ly / 2) + 2
               * image.meta.x0
               * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
               / 2))),
            0, (int)image.meta.ly,
            (int)image.meta.lx, (int)image.meta.ly,
            (int)image.meta.lx, (int)((image.meta.ly / 2)
                                + (2 * image.meta.x0 + image.meta.lx)
                                * tan(LPVL::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
                                / 2)))
        };

        p1.setPoints(4, top);
        p2.setPoints(4, bottom);
        painter.drawPolygon(p1);
        painter.drawPolygon(p2);
        path.addPolygon(p1);
        path.addPolygon(p2);

        painter.fillPath(path, brush);
        painter.end();

        bool ret = image_data.save(Config::Paths::lod(0) + "/" + target_filename);
        if(ret)
            qInfo() << "[PROCESSING] Image saved successfully with correction";
        else
            qCritical() << "[PROCESSING] Failed to save image";
    }

    image.path.first = Config::Paths::lod(0) + "/" + target_filename;
    QFile::remove(Config::Paths::lod(0) + "/" + filename);

    image.opacity = INITIAL_OPACITY;
    image.shown = INITIAL_VISIBILITY;
    image.mercator_zoom_level = CCL::mqiZoomLevel(image.meta.latitude, image.meta.dx);

    setProcessingImage(false);
    emit processImageFinished(image);
}

void ImageProcessing::asyncStripProcess(const QString& filename)
{
    Map::StripImage image;
    bool is_compressed = false;

    image.filename = filename;
    image.path.first = Config::Paths::lod(0) + "/" + filename;

    QByteArray chunks_unknown_ws;
    int ws = 0;
    QByteArray data = fileToByteArray(image.path.first);
    char* data_ptr = data.data();
    int rows, columns;

    qInfo() << "$ <i>Entered cycle</i>";

    int offset = 0;
    forever
    {     
        if(offset >= data.size())
            break;

        Map::StripImageDatagram datagram;
        memcpy(&datagram.header, data_ptr + offset, sizeof(datagram.header));
        memcpy(&datagram.nav, data_ptr + offset + sizeof(datagram.header), sizeof(datagram.nav));
        memcpy(&datagram.format, data_ptr + offset + sizeof(datagram.header) + sizeof(datagram.nav),
               sizeof(datagram.format));

        if(datagram.format.word_size == 0)
        {
            is_compressed = true;
            // for now I will just hardcode it
            datagram.format.word_size = 1;
        }

        int chunk_size = datagram.header.size * datagram.format.word_size;

        if(not ws)
        {
            ws = datagram.format.word_size;
            columns = (int)(datagram.format.dx * datagram.format.nx);
        }

        char chunk[chunk_size];
        float fchunk[chunk_size];

        if(is_compressed)
        {
            QByteArray chunk_compressed;
            chunk_compressed.resize(datagram.header.size);
            chunk_compressed.replace(0, datagram.header.size, data_ptr + offset + sizeof(datagram.header) + sizeof(datagram.nav)
                                                              + sizeof(datagram.format));
            memcpy(chunk, chunk_compressed.constData(), chunk_size);
        }
        else
            memcpy(chunk, data_ptr + offset + sizeof(datagram.header) + sizeof(datagram.nav)
                              + sizeof(datagram.format), chunk_size);

        for(size_t i = 0; i < chunk_size; ++i)
        {
            fchunk[i] = chunk[i];
            chunks_unknown_ws.push_back(fchunk[i]);
        }

        offset += (sizeof(datagram.header) + sizeof(datagram.nav) + sizeof(datagram.format) + chunk_size); //84 + chunk_size
    }
    qInfo() << "$ <i>Cycle finished</i>";

    if(ws == 0) {
        qCritical() << "[PROCESSING] Failed to decode word size";
        return;
    }

    QDataStream out(chunks_unknown_ws);
    QVector<uint8_t> chunks8_t;
    int vl = chunks_unknown_ws.length() / ws;
    int pixel_count = 0;
    if(ws == 1)
    {
        chunks8_t.resize(vl);
        for (int i = 0; i < vl; i++)
            out >> chunks8_t[i];
        rows = (int)(chunks8_t.size() / columns);
        pixel_count = chunks8_t.size();

        vector<uint8_t> out = vector<uint8_t>(chunks8_t.begin(), chunks8_t.end());

        if(DEBUG_SAVE_STRIP_DATA_DESERIALIZED)
        {
            QFile file(Config::Paths::lod(0) + "/debug_strip_data.bin");
            if(file.open(QIODevice::WriteOnly))
            {
                file.write(reinterpret_cast<const char*>(out.data()), out.size());
                file.close();
            }
            else
                qWarning() << "[PROCESSING] Failed to save debug strip data to file.";
        }

        QImage strip_result(columns, rows, QImage::Format_Grayscale16);
        vector<vector<float>> data;
        data.resize(rows);
        for(size_t i = 0; i < rows; ++i)
        {
            data[i].resize(columns);
            for(size_t j = 0; j < columns; ++j)
                data[i][j] = out[j + columns * i];
        }
        float max = *std::max_element(out.begin(), out.end());
        for(size_t row = 0; row < data.size(); ++row)
        {
            for(size_t column = 0; column < data[row].size(); ++column)
            {
                float t = (data[row][column] * 255) / max;
                uint8_t d[4] = {static_cast<uint8_t>(t), static_cast<uint8_t>(t), static_cast<uint8_t>(t), 255};
                uint32_t* rs = (uint32_t*)d;
                strip_result.setPixel(column, row, *rs);
            }
        }

        QString result_name = filename.chopped(3) + "png";
        strip_result.save(Config::Paths::lod(0) + "/" + result_name, "PNG");
        qInfo() << "$ [PROCESSING] Saved strip image" << (Config::Paths::lod(0) + "/" + result_name);

        if(DEBUG_SHOW_STRIP_DATA_MATRIX)
            emit stripVector8bit(out, rows, columns);
    }
    else {
        qCritical() << "[PROCESSING] Word size is not supported (only uint8_t)";
        return;
    }

    qDebug() << "[PROCESSING] Decoded strip image vector with"
             << pixel_count
             << "elements ( sizeof:" << ws << ")";
    qInfo().nospace() << "$ <b><u>[PROCESSING] Strip [x/y]: " << columns << "x" << rows << "</u></b>";

    if(not DEBUG_PRESERVE_BINARY)
        QFile::remove(Config::Paths::lod(0) + "/" + filename);

    setProcessingStrip(false);
}

QByteArray ImageProcessing::fileToByteArray(const QString& path)
{
    QFile file(path);
    if(not file.open(QIODevice::ReadOnly))
    {
        qCritical().noquote() << "[PROCESSING] Error opening file |" << path << "| for converting to raw bytes data";
        return QByteArray();
    }

    return file.readAll();
}

Map::ImageModel* ImageProcessing::model() { return this->m_model; }
void ImageProcessing::passImage(const Map::Image& image) { model()->add(image); }

bool ImageProcessing::exists(const QString& name)
{
    for(const Map::Image &image : *model()->direct())
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

bool ImageProcessing::processingImage() const { return m_processingImage; }
void ImageProcessing::setProcessingImage(bool other) {
    if (m_processingImage == other)
        return;
    m_processingImage = other;
    emit processingImageChanged();
}

bool ImageProcessing::processingStrip() const { return m_processingStrip; }
void ImageProcessing::setProcessingStrip(bool other) {
    if (m_processingStrip == other)
        return;
    m_processingStrip = other;
    emit processingStripChanged();
}