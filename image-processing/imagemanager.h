#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QSaveFile>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QtMath>

#include <QBuffer>

#include "sconfig.h"
#include "debug.h"
#include "profiler.h"
#include "cachemanager.h"
#include "alphamask.h"

enum ImageFormat : short int
{
    OnlyFilename,
    JPEG,
    PNG
};

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = nullptr);

    QStringList GetDiff(QStringList existingFileList);
    QStringList GetInitialList(const QString& path, QStringList diff = {});
    QStringList GetPartialList(const QString& path, QStringList diff = {});
    bool saveRawData(QByteArray data, QString filename); //to disk

    static QStringList diffConvert(QStringList diff, ImageFormat format = ImageFormat::OnlyFilename);

private:
    QString MakePNG(QString jpeg);

signals:

};

#endif // IMAGEMANAGER_H
