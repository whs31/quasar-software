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
    explicit ImageProcessing(LinkerQML* linker);
    bool InitialScan();
    bool PartialScan();
    bool getReadyStatus(void);
    int getFileCounter(void);
    int getVectorSize(void);
    void goLeft(void);
    void goRight(void);
    void showAllImages(bool showOnStart = false);
    void showPartialScanResult();
    void clearCache();
    void imageChecklistLoop();

    QVector<bool> imageChecklist;

signals:
    void setLeftButton(bool b);
    void setRightButton(bool b);
    void updateTopLabels(int total, int current);
    void updateMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, QString hexSum, QString datetime, bool match);
    void enableImageBar(bool b);

private:
    LinkerQML* qmlLinker;
    ImageManager* imageManager;

    uint32_t getChecksum(const void* data, size_t length, uint32_t previousCrc32 = 0);
    void decode(QStringList filelist, DecodeMode mode = DecodeMode::Initial);
    void updateLabels(int structureIndex);
    QStringList getEntryList(QString &path);

    struct image_metadata {
            double latitude;
            double longitude;
            float dx;
            float dy;
            float x0;
            float y0;
            float angle;
            float driftAngle;
            uint32_t checksum;
            QString filename;
            QString datetime;
            bool checksumMatch;
            QString base64encoding;
        };
    QVector<image_metadata> metadataList;

    QStringList diff;
    bool notNull = false;
    short newImagesCounter = 0;
    int fileCounter = 0;
};

#endif // IMAGEPROCESSING_H
