#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QtEndian>
#include <QImageReader>
#include <QMessageBox>
#include <QDateTime>

#include "mainwindow.h"
#include "imagemanager.h"
#include "linkerqml.h"

#include <QElapsedTimer>

#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4

class MainWindow;
class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(LinkerQML* linker, MainWindow* parent);
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

private:
    MainWindow* mainWindow;
    LinkerQML* qmlLinker;
    ImageManager* imageManager;

    QStringList diff;
};

#endif // IMAGEPROCESSING_H
