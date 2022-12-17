#include "imageprocess.h"

ImageProcess::ImageProcess(QObject *parent)
    : QObject{parent}
{
}

bool ImageProcess::decode(QByteArray data, TImage &image)
{
    char *chardata = data.data();
    uint16_t *metaMarker = reinterpret_cast<uint16_t *>(chardata + JPEG_HEADER_SIZE);
    if (*metaMarker == 0xE1FF)
    {
        // заполнение структуры метаданными
        uint16_t *metaSize = reinterpret_cast<uint16_t *>(chardata + JPEG_HEADER_SIZE + 2);
        *metaSize = qToBigEndian(*metaSize) - 2;
        memcpy(&image.meta, (chardata + JPEG_HEADER_SIZE + 4), *metaSize);

        // проверка контрольной суммы
        void *structData = (void *)malloc(1024);
        memcpy((char *)structData, (void *)&image.meta, *metaSize);
        uint32_t recalculatedChecksum = SChecksum::calculateChecksum(structData, *metaSize);
        QString recalculatedChecksumHex = QString("%1").arg(recalculatedChecksum, 8, 16, QLatin1Char('0')); //@TODO to uint16 -> crc16
        image.checksumMatch = (recalculatedChecksum == image.meta.checksum) ? 1 : 0;
        if (!image.checksumMatch)
            Debug::Log("![IMAGETOOLS] Checksum seems to be incorrect");

        // геометрические преобразования
        if (SConfig::getHashBoolean("GlobalRadians"))
        {
            image.meta.angle = SMath::radiansToDegrees(image.meta.angle) + SConfig::getHashFloat("AnglePredefinedCorrection");
            image.meta.driftAngle = SMath::radiansToDegrees(image.meta.driftAngle);
            image.meta.thetaAzimuth = SMath::radiansToDegrees(image.meta.thetaAzimuth);
        }
        return 1;
    }
    else
    {
        Debug::Log("!![IMAGETOOLS] Marker error!");
        return 0;
    }
}

void ImageProcess::assignUIStrings(TImage &image, QString filename)
{
    image.gui.latitude = QString::number(image.meta.latitude, 'f', 8);
    image.gui.longitude = QString::number(image.meta.longitude, 'f', 8);
    image.gui.dx = QString::number(image.meta.dx, 'f', 1);
    image.gui.dy = QString::number(image.meta.dy, 'f', 1);
    image.gui.x0 = QString::number(image.meta.x0, 'f', 0);
    image.gui.y0 = QString::number(image.meta.y0, 'f', 0);
    image.gui.angle = QString::number(image.meta.angle, 'f', 3);
    image.gui.driftAngle = QString::number(image.meta.driftAngle, 'f', 3);
    image.gui.lx = QString::number(image.meta.lx, 'f', 0);
    image.gui.ly = QString::number(image.meta.ly, 'f', 0);
    image.gui.thetaAzimuth = QString::number(image.meta.thetaAzimuth, 'f', 3);
    image.gui.checksum = "0x" + QStringLiteral("%1").arg(image.meta.checksum, 8, 16, QLatin1Char('0')).toUpper(); //@TODO to uint16
    image.gui.filename = filename;

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy в hh:mm");
    image.gui.creationTime = formattedTime;
}

QImage ImageProcess::dataToImage(QByteArray data, ImageMode mode, TImage& image)
{
    data.reserve(sizeof(data));
    QImage qimage = QImage::fromData(data, "JPEG");
    image.realWidth = qimage.width();
    image.realHeight = qimage.height();

                
    if (mode == ImageMode::Raw)
        return qimage;
    else if (mode == ImageMode::GeometricAlphaMask)
    {
        qimage = enableAlphaSupport(qimage);
        qimage = addAlphaMask(qimage, image.realWidth, image.realHeight, image.meta.thetaAzimuth, image.meta.x0);
        return qimage;
    }
    Debug::Log("!![IMAGETOOLS] ImageMode is incorrect.");
    return QImage();
}

QString ImageProcess::imageToBase64(QImage &image)
{
    QByteArray arr;
    QBuffer buffer(&arr);
    image.save(&buffer, "PNG");
    QString encoded = QString::fromLatin1(arr.toBase64().data());
    return encoded;
}

QImage ImageProcess::enableAlphaSupport(QImage image)
{                                                                                      //      перевод картинки в формат, поддерживающий прозрачность (да, это костыль)
    QImage sample(image.width(), image.height(), QImage::Format_ARGB32_Premultiplied); //      сюда надо будет добавить прозрачность из слайдера (или сделать это в qml)
    sample.fill(QColor(254, 254, 254));
    image.setAlphaChannel(sample);
    return image;
}

QImage ImageProcess::addAlphaMask(QImage image, float width, float height, float thetaAzimuth, float x0)
{
    QPainter painter;
    painter.begin(&image);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setPen(QPen(Qt::transparent, 10));
    painter.setRenderHint(QPainter::Antialiasing);
    const int top[8] = {
        0, (int)((height / 2) - 2*x0*qTan(qDegreesToRadians(thetaAzimuth / 2))),
        0, 0,
        (int)width, 0,
        (int)width, (int)((height / 2) - (2*x0 + width) * qTan(qDegreesToRadians(thetaAzimuth / 2)))
        };
    const int bottom[8] = {
        0, (int)((height / 2) + 2*x0*qTan(qDegreesToRadians(thetaAzimuth / 2))),
        0, (int)height,
        (int)width, (int)height,
        (int)width, (int)((height / 2) + (2*x0 + width) * qTan(qDegreesToRadians(thetaAzimuth / 2)))
        };
    QPolygon p1, p2;
    p1.setPoints(4, top);
    p2.setPoints(4, bottom);
    painter.drawPolygon(p1);
    painter.drawPolygon(p2);
    QPainterPath fillp;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::transparent);
    fillp.addPolygon(p1);
    fillp.addPolygon(p2);
    painter.fillPath(fillp, brush);
    painter.end();
    return image;
}
