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

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = nullptr);

    QStringList CopyJPEG(const QString& path);
    QString MakePNG(QString jpeg);
    QString getCacheDirectory(void);
    QString getPNGDirectory(void);
    QImage swapAlpha(QImage i);
    QImage evilFormatConversion(QImage i);
    bool addAlphaMask(QString path, float width, float height, float thetaAzimuth, float rayInitialWidth = 10, float horizontalCut = 0, float driftAngle = 0);

private:
    QString cacheDirectory;
    QString PNGDirectory;

signals:

};

#endif // IMAGEMANAGER_H
