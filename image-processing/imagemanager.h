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

#include "sconfig.h"

enum ImageFormat : short int
{
    OnlyFilename,
    JPEG,
    PNG
};

enum ClearMode : short int
{
    ClearAll,
    ClearTCP,
    ClearPNG
};

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = nullptr);

    QStringList getDiff(const QString &path, QStringList existingFileList);
    QStringList diffConvert(QStringList diff, ImageFormat format = ImageFormat::OnlyFilename);
    QStringList CopyJPEG(const QString& path, QStringList diff);
    QString MakePNG(QString jpeg);
    static QString getCacheDirectory(void);
    static QString getPNGDirectory(void);
    static QString getTCPDirectory (void);
    bool saveRawData(QByteArray data, QString filename);
    QImage swapAlpha(QImage i);
    QImage enableAlphaSupport(QImage i);
    bool addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth = 10, float horizontalCut = 0, float driftAngle = 0);

    static void clearCache(ClearMode mode = ClearMode::ClearAll);

private:
    static QString cacheDirectory;
    static QString PNGDirectory;
    static QString TCPDirectory;

signals:

};

#endif // IMAGEMANAGER_H
