#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include "qt-includes.h"

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
