#include "imageprocessing.h++"
#include "map/imagemodel.h++"
#include "config/paths.h++"
#include "config/config.h++"
#include "utils/utils.h++"
#include "utils/numeric.h++"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QtEndian>

using namespace Processing;

DECLARE_SINGLETON_IMPL(ImageProcessing)

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
    uint16_t crc16 = Utilities::crc16(crc_data, sizeof(Map::ImageMetadata) - sizeof(uint16_t));

    image.valid = crc16 == image.meta.crc16;
    if(not image.valid)
        qWarning().noquote().nospace() << "[PROCESSING] Image CRC16 seems to be incorrect: expected 0x"
                                       << Qt::hex << crc16 << ", received 0x" << image.meta.crc16 << Qt::dec;

    // геометрические преобразования
    if(CONFIG(useRadians))
    {
        image.meta.angle = Utilities::Numeric::radiansToDegrees(image.meta.angle)
                           + CONFIG(angleCorrection);
        image.meta.drift_angle = CONFIG(useDriftAngle)
                                     ? Utilities::Numeric::radiansToDegrees(image.meta.drift_angle)
                                     : 0;
        image.meta.div = Utilities::Numeric::radiansToDegrees(image.meta.div);
    }
    else
        image.meta.angle += CONFIG(angleCorrection);

    //! @todo: ly != real height
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

Map::ImageModel* ImageProcessing::model() const
{
    return this->m_model;
}

void ImageProcessing::processImage(const QString& filename)
{
    qDebug() << "[PROCESSING] Received image to process" << filename;

    this->asyncProcess(filename);
}

