#include "alphamask.h"

AlphaMask::AlphaMask()
{

}

QImage AlphaMask::enableAlphaSupport(QImage i)                                     //      этот метод нужен для конверсии изображения
{                                                                                     //      в формат, поддерживающий прозрачность
    QImage sample(i.width(),i.height(), QImage::Format_ARGB32_Premultiplied);         //      сюда надо будет добавить прозрачность из слайдера (или сделать это в qml)
    sample.fill(QColor(254,254,254));
    i.setAlphaChannel(sample);
    return i;
}

QString AlphaMask::addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth, float horizontalCut, float driftAngle, MaskFormat format)
{
    QImage base(path);
    if(format == 0 || format == 2)
    {

        QPainter painter;
        painter.begin(&base);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.setPen(QPen(Qt::transparent, 2));
        painter.setRenderHint(QPainter::Antialiasing);
        const int top[8] = {
            0, (int)(height/2+rayInitialWidth),
            0, (int)height,
            (int)width, (int)height,
            (int)width, static_cast<int>((height/2)+width*(qTan(qDegreesToRadians(thetaAzimuth/2))))
        };
        const int bottom[8] = {
            0, (int)(height/2-rayInitialWidth),
            0, 0,
            (int)width, 0,
            (int)width, static_cast<int>((height/2)-width*(qTan(qDegreesToRadians(thetaAzimuth/2))))
        };
        QPolygon p1, p2;
        p1.setPoints(4, top); p2.setPoints(4, bottom);
        painter.drawPolygon(p1);
        painter.drawPolygon(p2);
        QPainterPath fillp;
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::transparent);
        fillp.addPolygon(p1); fillp.addPolygon(p2);
        painter.fillPath(fillp, brush);
        painter.end();
    }
    if(format == 1 || format == 2)
    {
        QImage alphaImage = base;
        alphaImage.createMaskFromColor(QColor("black").rgb(), Qt::MaskOutColor);
        base.setAlphaChannel(alphaImage);
    }
    if(SConfig::USEBASE64)
    {
        QString r = convertToBase64(base);
        return r;
    } else {
        bool s = base.save(path);
    }
    return "";
}

QString AlphaMask::convertToBase64(QImage image)
{
    QByteArray arr;
    QBuffer buffer(&arr);
    image.save(&buffer, "PNG");
    QString encoded = QString::fromLatin1(arr.toBase64().data());
    return encoded;
}
