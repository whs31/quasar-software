#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QVector>
#include <QtEndian>

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
        };

    ImageProcessing::image_metadata decode(QString path);
    QVector<image_metadata> metadataList;

private:
    MainWindow* mainWindow;
};

#endif // IMAGEPROCESSING_H
