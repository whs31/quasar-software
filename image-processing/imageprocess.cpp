#include "imageprocess.h"

ImageProcess::ImageProcess(QObject *parent)
    : QObject{parent}
{
}

bool ImageProcess::decode(QByteArray data, TImage& image)
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
        QString recalculatedChecksumHex = QString("%1").arg(recalculatedChecksum, 8, 16, QLatin1Char('0'));
        image.checksumMatch = (recalculatedChecksum == image.meta.checksum) ? 1 : 0;

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

void ImageProcess::assignUIStrings(TImage& image, QString filename)
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

QImage ImageProcess::dataToImage(QByteArray data, ImageMode mode)
{
    QImage qimage = QImage::fromData(data,"PNG");
    if(mode == ImageMode::Raw)
        return qimage;
    else if (mode == ImageMode::GeometricAlphaMask)
    {
        //make transparent and etc
    }
    Debug::Log("!![IMAGETOOLS] ImageMode is incorrect.");
    return QImage();
}

QString ImageProcess::imageToBase64(QImage image)
{
    QByteArray arr;
    QBuffer buffer(&arr);
    image.save(&buffer, "PNG");
    QString encoded = QString::fromLatin1(arr.toBase64().data());
    return encoded;
}