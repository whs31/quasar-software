#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QObject>
#include <QByteArray>
#include <QtEndian>

#include "models/timage.h"
#include "schecksum.h"
#include "sconfig.h"
#include "smath.h"

#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4

class ImageProcess : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcess(QObject *parent = nullptr);
    TImage decode(QByteArray data, TImage& image);

signals:

};

#endif // IMAGEPROCESS_H
