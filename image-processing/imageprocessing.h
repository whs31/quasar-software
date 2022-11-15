#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include "qt-includes.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define JPEG_HEADER_SIZE 20
class MainWindow;

class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(QObject *parent = nullptr);
    struct image_metadata {
            double latitude;
            double longitude;
            float dx;
            float dy;
            float x0;
            float y0;
            float angle;
            QString filename;
            QString datetime;
        };

    void decode(QStringList filelist);
    void processPath(QString path);
    void updateLabels(int structureIndex);

    bool getReadyStatus();
    int getFileCounter();
    int getVectorSize();

    QVector<image_metadata> metadataList;
    QStringList imageList;

    int fileCounter = 0;
    void goLeft();
    void goRight();
    void updateUpperLabels();
    void showAllImages();

private:
    MainWindow* mainWindow;
};

#endif // IMAGEPROCESSING_H
