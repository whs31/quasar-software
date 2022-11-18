#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QImage>

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = nullptr);

    bool CopyJPEG(const QString& path);
    bool MakePNG(QString jpeg);
    QString getCacheDirectory(void);
    QString getPNGDirectory(void);
    QImage swapAlpha(QImage i);

private:
    QString cacheDirectory;
    QString PNGDirectory;
    //QStringList

signals:

};

#endif // IMAGEMANAGER_H
