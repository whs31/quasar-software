#include "imageprocessing.h"
#include "map/imagemodel.h"
#include "map/entities/stripimage.h"
#include "config/paths.h"
#include "config/config.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QtEndian>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtConcurrent/QtConcurrent>
#include <cmath>
#include <ccl/ccl_core.h>

using namespace Processing;

ImageProcessing::ImageProcessing(QObject* parent)
    : QObject{parent}
    , m_model(new Map::ImageModel(this))
{
}

void ImageProcessing::asyncProcess(const QString& filename)
{
    Map::Image image;

    image.filename = filename;
    image.path.first = Config::Paths::imageCache() + "/lod0/" + filename;
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
    uint16_t *meta_size = reinterpret_cast<uint16_t *>(data_ptr + image.header.JPEG_HEADER_SIZE
                                                       + sizeof(uint16_t));
    *meta_size = qToBigEndian(*meta_size) - sizeof(uint16_t);
    memcpy(&image.meta, (data_ptr + image.header.JPEG_HEADER_SIZE + sizeof(uint32_t)), *meta_size);

    // проверка контрольной суммы
    char *crc_data = (char *) &image.meta;
    uint16_t crc16 = ccl::crc16(crc_data, sizeof(Map::ImageMetadata) - sizeof(uint16_t));

    image.valid = crc16 == image.meta.crc16;
    if(not image.valid)
        qWarning().noquote().nospace() << "[PROCESSING] Image CRC16 seems to be incorrect: expected 0x"
                                       << Qt::hex << crc16 << ", received 0x" << image.meta.crc16 << Qt::dec;

    // геометрические преобразования
    if(CONFIG(useRadians))
    {
        image.meta.angle = ccl::rad2deg(image.meta.angle)
                           + CONFIG(angleCorrection);
        image.meta.drift_angle = CONFIG(useDriftAngle)
                                     ? ccl::rad2deg(image.meta.drift_angle)
                                     : 0;
        image.meta.div = ccl::rad2deg(image.meta.div);
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
        bool ret = image_data.save(Config::Paths::imageCache() + "/lod0/" + target_filename);
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
               * tan(ccl::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
               / 2))),
            0, 0,
            (int)image.meta.lx, 0,
            (int)image.meta.lx, (int)((image.meta.ly / 2) -
                                (2 * image.meta.x0 + image.meta.lx)
                                * tan(ccl::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
                                / 2)))
        };

        const int bottom[8] = {
            0, (int)((image.meta.ly / 2) + 2
               * image.meta.x0
               * tan(ccl::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
               / 2))),
            0, (int)image.meta.ly,
            (int)image.meta.lx, (int)image.meta.ly,
            (int)image.meta.lx, (int)((image.meta.ly / 2)
                                + (2 * image.meta.x0 + image.meta.lx)
                                * tan(ccl::deg2rad((image.meta.div - CONFIG(thetaAzimuthCorrection))
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

        bool ret = image_data.save(Config::Paths::imageCache() + "/lod0/" + target_filename);
        if(ret)
            qInfo() << "[PROCESSING] Image saved successfully with correction";
        else
            qCritical() << "[PROCESSING] Failed to save image";
    }

    image.path.first = Config::Paths::imageCache() + "/lod0/" + target_filename;
    QFile::remove(Config::Paths::imageCache() + "/lod0/" + filename);

    image.opacity = INITIAL_OPACITY;
    image.shown = INITIAL_VISIBILITY;
    image.mercator_zoom_level = ccl::mqi_zoom_level(image.meta.latitude, image.meta.dx);

    model()->add(image);
}

void ImageProcessing::asyncStripProcess(const QString& filename)
{
    Map::StripImage image;

    image.filename = filename;
    image.path.first = Config::Paths::imageCache() + "/lod0/" + filename;
    QByteArray data = fileToByteArray(image.path.first);

    char* data_ptr = data.data();
    memcpy(&image.header, data_ptr, sizeof(Map::StripHeaderMetadata));
    memcpy(&image.nav, data_ptr + sizeof(Map::StripHeaderMetadata), sizeof(Map::StripNavigationMetadata));
    memcpy(&image.format, data_ptr + sizeof(Map::StripHeaderMetadata) + sizeof(Map::StripNavigationMetadata),
           sizeof(Map::StripFormatMetadata));

    qInfo() << "$ Image header:"
            << "Marker:" << image.header.marker
            << "Version:" << image.header.version
            << "Size:" << image.header.size
            << "Count:" << image.header.cnt
            << "ID:" << image.header.id
            << "Type:" << image.header.type;

    qInfo() << "$ Image navigation:"
             << "Pitch:" << image.nav.pitch
             << "Roll:" << image.nav.roll
             << "Elevation:" << image.nav.elevation
             << "Latitude:" << image.nav.latitude
             << "Longitude:" << image.nav.longitude
             << "Velocity:" << image.nav.velocity
             << "Course:" << image.nav.course
            << "TrackAng:" << image.nav.track_ang;

    qInfo() << "$ Image format:"
            << "dx:" << image.format.dx
             << "dy:" << image.format.dy
             << "Course:" << image.format.course
             << "Roll:" << image.format.roll
             << "x0:" << image.format.x0
             << "WordSize:" << image.format.word_size
             << "Polarization:" << image.format.polarization
             << "Y:" << image.format.y
             << "nx:" << image.format.nx
             << "ny:" << image.format.ny
            << "k:" << image.format.k;

    /* EXPECTED (from plot.py)
    {☑ 'marker': 57082,
     ☑ 'version': 1,
     ☑ 'size': 500,
     ☑ 'cnt': 0,
     ☑ 'id': 85,
     ☑ 'type': 1}
    {☑ 'pitch': 0.0,
     ☑ 'roll': 0.0,
     ☑ 'ele': 158.23333740234375,
     'lat': 51.50708866649204,
     'lon': 39.110633833143446,
     'velocity': 15.699403762817383,
     'course': 192.38999938964844,
     'track_ang': 192.38999938964844}
    {'dx': 1.0,
     'dy': 1.0,
     'course': 0.0,
     'roll': 0.0,
     'x0': 50.0,
     'word_size': 1,
     'polarization': 0,
     'y': 0,
     'nx': 500,
     'ny': 1,
     'k': 1.897916316986084}
    */
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

Map::ImageModel* ImageProcessing::model()
{
    return this->m_model;
}

void ImageProcessing::processImage(const QString& filename)
{
    qDebug() << "[PROCESSING] Received image to process" << filename;

    this->asyncProcess(filename);

    //! @todo busy
}

void ImageProcessing::processStripImage(const QString& filename)
{
    qDebug() << "[PROCESSING] Received binary to process" << filename;

    this->asyncStripProcess(filename);

    //! @todo busy
}

bool ImageProcessing::exists(const QString& name)
{
    for(Map::Image image : *model()->direct())
    {
        if(image.filename == name)
            return true;

        if(image.filename.chopped(4) == name.chopped(4))
            return true;
    }
    return false;
}

bool ImageProcessing::busy() const { return m_busy; }
void ImageProcessing::setBusy(bool other) {
    if (m_busy == other)
        return;
    m_busy = other;
    emit busyChanged();
}
