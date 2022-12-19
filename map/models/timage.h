#ifndef TIMAGE_H
#define TIMAGE_H

#include <QObject>
#include <QColor>
#include <QImage>

class TImage : public QObject
{
    Q_OBJECT
public:
    explicit TImage(QObject *parent = nullptr);

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

    QString cachedJPEGfilename = ""; //check
    QString base64 = "";
    qreal realWidth = 0;
    qreal realHeight = 0;
    
    bool checksumMatch = false; //check
    
    qint32 index = 0; //check
    qreal opacity = 1;
    bool visible = true;

    qreal horizontalCorrection = 0;
    qreal verticalCorrection = 0;
    qreal angleCorrection = 0;
    qreal scaleCorrection = 0;
    
    bool drawSARmarker = true;
    QString SARMarkerName = "";
    QColor SARMarkerColor = Qt::white;

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

signals:
};

#endif // TIMAGE_H
