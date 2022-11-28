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

enum MaskFormat : short int
{
    Geometric,
    AlphaSwap,
    Combined
};

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = nullptr);

    QStringList GetDiff(QStringList existingFileList);
    QStringList GetInitialList(const QString& path, QStringList diff = {});
    QStringList GetPartialList(const QString& path, QStringList diff = {});
    bool saveRawData(QByteArray data, QString filename);
    QString addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth = 10, float horizontalCut = 0, float driftAngle = 0, MaskFormat format = MaskFormat::Geometric);

    static QString getPNGDirectory(void);
    static QString getTCPDirectory (void);
    static void clearCache(ClearMode mode = ClearMode::ClearAll);
    static void setupCache(void);
    static QStringList diffConvert(QStringList diff, ImageFormat format = ImageFormat::OnlyFilename);

private:
    static QString PNGDirectory;
    static QString TCPDirectory;

    QImage enableAlphaSupport(QImage i);
    QString convertToBase64(QImage image);
    QString MakePNG(QString jpeg);

signals:

};

#endif // IMAGEMANAGER_H
