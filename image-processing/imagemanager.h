#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = nullptr);

    QString cacheDirectory;
    bool CopyJPEG(const QString& path);
    QString getCacheDirectory();

signals:

};

#endif // IMAGEMANAGER_H
