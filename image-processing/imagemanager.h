#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QtMath>
#include <QSet>

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = nullptr);

    QStringList getDiff(const QString &path, QStringList existingFileList);
    QStringList diffConvert(QStringList diff, const int format); // { 0 1 2 } => { blank .jpg .png }
    QStringList CopyJPEG(const QString& path, QStringList diff);
    QString MakePNG(QString jpeg);
    QString getCacheDirectory(void);
    QString getPNGDirectory(void);
    QImage swapAlpha(QImage i);
    QImage enableAlphaSupport(QImage i);
    bool addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth = 10, float horizontalCut = 0, float driftAngle = 0);

private:
    QString cacheDirectory;
    QString PNGDirectory;

signals:

};

#endif // IMAGEMANAGER_H
