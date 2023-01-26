#include "timage.h"

TImage::TImage(QObject *parent, QByteArray data, QString filePath, ImageMode mode, qreal predefinedCorrection, bool globalRadians, qreal thetaAzimuthCorrection,
                bool globalDriftAngle)
    : QObject{parent}, predefinedCorrection(predefinedCorrection), globalRadians(globalRadians), thetaAzimuthCorrection(thetaAzimuthCorrection),
    globalDriftAngle(globalDriftAngle)
{
    cachedJPEGfilename = filePath;

    //конвертируем путь к файлу в его имя и расширение
    QStringList _cutFilename;
    _cutFilename = filePath.split("/");
    gui.filename = _cutFilename.last();

    //декодирование метаданных из изображения и проверка на совпадение маркера
    decode(data) ? valid = true : valid = false;

    if(valid)
    {
        //конвертируем метаданные в строки для интерфейса, сохраняем время приема картинки
        assignUIStrings(gui.filename);
        //конвертируем данные в картинку с альфа-каналом (если mode не Raw)
        image = dataToQImage(data, mode);
        //конвертируем в base64 обработанное изображение для упрощения передачи его в QML
        base64 = QImageToBase64(image);     
        //TODO: make small image triange from x0 point to lowerbound
    }

}

bool TImage::isValid()
{
    return valid;
}

bool TImage::decode(QByteArray data)
{
    char* chardata = data.data();
    uint16_t *metaMarker = reinterpret_cast<uint16_t *>(chardata + JPEG_HEADER_SIZE);
    if (*metaMarker == 0xE1FF)
    {
        // заполнение структуры метаданными
        uint16_t *metaSize = reinterpret_cast<uint16_t *>(chardata + JPEG_HEADER_SIZE + 2);
        *metaSize = qToBigEndian(*metaSize) - 2;
        memcpy(&meta, (chardata + JPEG_HEADER_SIZE + 4), *metaSize);

        // проверка контрольной суммы
        char* structData = (char*)malloc(sizeof(meta)); 
        memcpy((char *)structData, (char *)&meta, *metaSize);
        uint32_t recalculatedChecksum = SChecksum::calculateCRC16(structData, *metaSize);
        QString recalculatedChecksumHex = QString("%1").arg(recalculatedChecksum, 4, 16, QLatin1Char('0')); //TODO:  to uint16 -> crc16
        checksumMatch = (recalculatedChecksum == meta.checksum) ? 1 : 0;
        if (!checksumMatch)
            Debug::Log("![IMAGETOOLS] Checksum seems to be incorrect");

        // геометрические преобразования
        if (globalRadians)
        {
            meta.angle = SMath::radiansToDegrees(meta.angle) + predefinedCorrection;
            meta.driftAngle = globalDriftAngle ? SMath::radiansToDegrees(meta.driftAngle) : 0;
            meta.thetaAzimuth = SMath::radiansToDegrees(meta.thetaAzimuth);
        } else {
            meta.angle += predefinedCorrection;
        }
        return true;
    }
    else
    {
        Debug::Log("!![IMAGE] Marker error!");
        return false;
    }
}

void TImage::assignUIStrings(QString filename)
{
    gui.latitude = QString::number(meta.latitude, 'f', 8) + "°";
    gui.longitude = QString::number(meta.longitude, 'f', 8) + "°";
    gui.dx = QString::number(meta.dx, 'f', 1);
    gui.dy = QString::number(meta.dy, 'f', 1);
    gui.x0 = QString::number(meta.x0, 'f', 0) + " м";
    gui.y0 = QString::number(meta.y0, 'f', 0) + " м";
    gui.angle = QString::number(meta.angle, 'f', 3) + "°" 
        + "<font color=\"#43a1ca\"> + " + QString::number(predefinedCorrection) + "°</font>";
    gui.driftAngle = globalDriftAngle ? QString::number(meta.driftAngle, 'f', 3) + "°" : "<font color=\"#b16573\">отключен в настройках</font>";
    gui.lx = QString::number(meta.lx, 'f', 0) + " м";
    gui.ly = QString::number(meta.ly, 'f', 0) + " м";
    gui.thetaAzimuth = QString::number(meta.thetaAzimuth, 'f', 3) + "°" 
        + "<font color=\"#43a1ca\"> [ " + QString::number(meta.thetaAzimuth - thetaAzimuthCorrection) + "° ]</font>";
    gui.checksum = "<font color=\"#a385cf\">0x" + QStringLiteral("%1").arg(meta.checksum, 4, 16, QLatin1Char('0')).toUpper() + "</font>"; //@TODO to uint16
    gui.filename = "<font color=\"#c7a750\">" + filename + "</font>";

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy в hh:mm");
    gui.creationTime = formattedTime;
}

QImage TImage::dataToQImage(QByteArray data, ImageMode mode)
{
    data.reserve(sizeof(data));
    QImage qimage = QImage::fromData(data, "JPEG");
    realWidth = qimage.width();
    realHeight = qimage.height();
      
    if (mode == ImageMode::Raw)
        return qimage;
    else if (mode == ImageMode::GeometricAlphaMask)
    {
        //костыль для включения альфа-канала у картинки
        qimage = enableAlphaChannel(qimage);
        //применяем маску альфа-канала
        qimage = applyAlphaMask(qimage);
        return qimage;
    }
    Debug::Log("!![IMAGE] ImageMode is incorrect.");
    return QImage();
}

QString TImage::QImageToBase64(QImage image)
{
    QByteArray arr;
    QBuffer buffer(&arr);
    image.save(&buffer, "PNG");
    return QString::fromLatin1(arr.toBase64().data());
}

QImage TImage::enableAlphaChannel(QImage image)
{
    QImage sample(image.width(), image.height(), QImage::Format_ARGB32_Premultiplied); 
    sample.fill(QColor(254, 254, 254));
    image.setAlphaChannel(sample);
    return image;
}

QImage TImage::applyAlphaMask(QImage image)
{
    QPainter painter;
    painter.begin(&image);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setPen(QPen(Qt::transparent, 10));
    painter.setRenderHint(QPainter::Antialiasing);
    const int top[8] = {
        0, (int)((realHeight / 2) - 2 * meta.x0 * qTan(qDegreesToRadians((meta.thetaAzimuth - thetaAzimuthCorrection) / 2))),
        0, 0,
        (int)realWidth, 0,
        (int)realWidth, (int)((realHeight / 2) - (2 * meta.x0 + realWidth) * qTan(qDegreesToRadians((meta.thetaAzimuth - thetaAzimuthCorrection) / 2)))
        };
    const int bottom[8] = {
        0, (int)((realHeight / 2) + 2 * meta.x0 * qTan(qDegreesToRadians((meta.thetaAzimuth - thetaAzimuthCorrection) / 2))),
        0, (int)realHeight,
        (int)realWidth, (int)realHeight,
        (int)realWidth, (int)((realHeight / 2) + (2 * meta.x0 + realWidth) * qTan(qDegreesToRadians((meta.thetaAzimuth - thetaAzimuthCorrection)/ 2)))
        };
    QPolygon p1, p2;
    p1.setPoints(4, top);    p2.setPoints(4, bottom);
    painter.drawPolygon(p1); painter.drawPolygon(p2);
    QPainterPath fillp;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); brush.setColor(Qt::transparent);
    fillp.addPolygon(p1);    fillp.addPolygon(p2);
    painter.fillPath(fillp, brush);
    painter.end();
    return image;
}
