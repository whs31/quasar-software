#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QObject>
#include <QByteArray>
#include <QtEndian>
#include <QDateTime>
#include <QImage>
#include <QBuffer>
#include <QPainter>
#include <QPainterPath>
#include <QImageReader>

#include "models/timage.h"
#include "schecksum.h"
#include "sconfig.h"
#include "smath.h"
//#include "style.h"

#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4

enum ImageMode {
    Raw,
    GeometricAlphaMask,
    ChannelSwapAlphaMask
};

class ImageProcess : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcess(QObject *parent = nullptr);

    bool decode(QByteArray data, TImage& image);
    void assignUIStrings(TImage& image, QString filename);
    QImage dataToImage(QByteArray data, ImageMode mode, TImage& image);
    QString imageToBase64(QImage& image);

signals:

private:
    QImage enableAlphaSupport(QImage image);
    QImage addAlphaMask(QImage image, float width, float height, float thetaAzimuth, float rayInitialWidth);
};

#endif // IMAGEPROCESS_H
