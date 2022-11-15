#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QVector>
#include <QtEndian>
#include <QDir>
#include <QFileInfo>

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

    QVector<image_metadata> metadataList;
    QStringList imageList;


private:
    MainWindow* mainWindow;
};

#endif // IMAGEPROCESSING_H
