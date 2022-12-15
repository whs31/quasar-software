#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QObject>
#include <QByteArray>
#include <QtEndian>
#include <QDateTime>
#include <QImage>
#include <QBuffer>

#include "models/timage.h"
#include "schecksum.h"
#include "sconfig.h"
#include "smath.h"

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
    QImage dataToImage(QByteArray data, ImageMode mode);
    QString imageToBase64(QImage& image);

signals:

};

#endif // IMAGEPROCESS_H
