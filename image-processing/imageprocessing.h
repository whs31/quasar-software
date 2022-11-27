#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QtEndian>
#include <QImageReader>
#include <QMessageBox>
#include <QDateTime>

#include "coreui.h"
#include "imagemanager.h"
#include "linkerqml.h"

#include <QElapsedTimer>

#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4

class CoreUI;
class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(LinkerQML* linker, CoreUI* parent);
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

    QStringList getEntryList(QString &path);
    bool processPath(QString path);
    void decode(QStringList filelist);
    void updateLabels(int structureIndex);

    bool getReadyStatus(void);
    int getFileCounter(void);
    int getVectorSize(void);
    uint32_t getChecksum(const void* data, size_t length, uint32_t previousCrc32 = 0);

    QVector<image_metadata> metadataList;

    int fileCounter = 0;
    bool notNull = false;
    void goLeft(void);
    void goRight(void);
    void showAllImages(bool showOnStart = false);
    ImageManager* imageManager;

private:
    CoreUI* core;
    LinkerQML* qmlLinker;

    QStringList diff;
};

#endif // IMAGEPROCESSING_H
