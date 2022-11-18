#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include "qt-includes.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagemanager.h"

#include "linkerqml.h"

#define JPEG_HEADER_SIZE 20
#define JPEG_CHECKSUM_SIZE 4
class MainWindow;

class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(LinkerQML* linker);//QMLLinker* linker) : linker(linker);//uimanager
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

    bool processPath(QString path);
    void decode(QStringList filelist);
    void updateLabels(int structureIndex);

    bool getReadyStatus();
    int getFileCounter();
    int getVectorSize();
    uint32_t getChecksum(const void* data, size_t length, uint32_t previousCrc32 = 0);

    QVector<image_metadata> metadataList;
    QStringList imageList;

    int fileCounter = 0;
    bool notNull = false;
    void goLeft();
    void goRight();
    void updateUpperLabels();
    void showAllImages();

private:
    MainWindow* mainWindow;
    LinkerQML* qmlLinker;
    ImageManager* imageManager;
};

#endif // IMAGEPROCESSING_H
