#include "imageprocess.h"

ImageProcess::ImageProcess(QObject *parent)
    : QObject{parent}
{
}

void decode(QByteArray data, TImage &image)
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
    }
    else
    {
        Debug::Log("!![IMG] Marker error!");
    }
}
