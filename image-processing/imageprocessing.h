#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QtEndian>
#include <QImageReader>
#include <QMessageBox>
#include <QDateTime>

#include "imagemanager.h"
#include "linkerqml.h"
#include "debug.h"
#include "smath.h"
#include "schecksum.h"

#include "profiler.h"


#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4

enum DecodeMode
{
    Initial,
    Partial
};

class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing();
    bool InitialScan();
    bool PartialScan();
    bool getReadyStatus(void);
    int getFileCounter(void);
    int getVectorSize(void);
    void goLeft(void);
    void goRight(void);
    void showInitialScanResult(bool showOnStart = false);
    void showPartialScanResult();
    void clearCache();
    void imageChecklistLoop();

    QVector<bool> imageChecklist;

signals:
    void setLeftButton(bool b);
    void setRightButton(bool b);
    void updateTopLabels(int total, int current);
    void updateMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, float lx, float ly, float divAngle, QString hexSum, QString datetime, bool match);
    void enableImageBar(bool b);

private:
    struct image_metadata {
            double latitude;
            double longitude;
            float dx;
            float dy;
            float x0;
            float y0;
            float angle;
            float driftAngle;
            float lx;
            float ly;
            float div;
            uint32_t checksum;
            QString filename;
            QString datetime;
            bool checksumMatch;
            QString base64encoding;
        };
    LinkerQML* qmlLinker;
    ImageManager* imageManager;

    void Decode(QStringList filelist, DecodeMode mode = DecodeMode::Initial);
    void UpdateLabels(int structureIndex);
    QStringList getEntryList(QString &path);


    QVector<image_metadata> metadataList;

    QStringList diff;
    bool notNull = false;
    short newImagesCounter = 0;
    int fileCounter = 0;
};

#endif // IMAGEPROCESSING_H
