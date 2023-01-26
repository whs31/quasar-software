#ifndef TIMAGE_H
#define TIMAGE_H

#include <QObject>
#include <QColor>
#include <QImage>
#include <QByteArray>
#include <QtEndian>
#include <QDateTime>
#include <QBuffer>
#include <QPainter>
#include <QPainterPath>
#include <QImageReader>

#include "func/schecksum.h"
#include "func/smath.h"
#include "misc/debug.h"

#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4

enum ImageMode {
    Raw,
    GeometricAlphaMask,
    ChannelSwapAlphaMask
};

class TImage : public QObject
{
    Q_OBJECT
public:
    explicit TImage(QObject *parent, QByteArray data = QByteArray(), QString filePath = "", ImageMode mode = ImageMode::Raw, qreal predefinedCorrection = 0,
                    bool globalRadians = false, qreal thetaAzimuthCorrection = 0, bool globalDriftAngle = true);
    bool isValid();

    QString cachedJPEGfilename = ""; //check
    QString base64 = "";
    qreal realWidth = 0;
    qreal realHeight = 0;
    
    bool checksumMatch = false; //check
    qint32 index = 0; //check

    struct Metadata
    {
        double latitude = 0;
        double longitude = 0;
        float dx = 0;
        float dy = 0;
        float x0 = 0;
        float y0 = 0;
        float angle = 0;
        float driftAngle = 0;
        float lx = 0;
        float ly = 0;
        float thetaAzimuth = 0;
        uint32_t checksum = 0;
    };
    struct Interface
    {
        QString latitude = "";
        QString longitude = "";
        QString dx = "";
        QString dy = "";
        QString x0 = "";
        QString y0 = "";
        QString angle = "";
        QString driftAngle = "";
        QString lx = "";
        QString ly = "";
        QString thetaAzimuth = "";
        QString checksum = "";
        QString filename = "";
        QString creationTime = "";
    };
    Metadata meta; //check
    Interface gui; //check
    QImage image; //check

private:
    bool decode(QByteArray data);
    void assignUIStrings(QString filename);
    QImage dataToQImage(QByteArray data, ImageMode mode);
    QString QImageToBase64(QImage image);
    QImage enableAlphaChannel(QImage image);
    QImage applyAlphaMask(QImage image);

    bool valid = true;
    qreal predefinedCorrection;
    bool globalRadians;
    qreal thetaAzimuthCorrection;
    bool globalDriftAngle;

signals:
};

#endif // TIMAGE_H
