#ifndef DISKTOOLS_H
#define DISKTOOLS_H

#include <QObject>
#include <QDir>
#include <QStringList>
#include <QFile>

#include "image-processing/imagemanager.h"
#include "config/runtimedata.h"
#include "gui/thememanager.h"
#include "func/stext.h"

class DiskTools : public QObject
{
    Q_OBJECT
public:
    static DiskTools* initialize(QObject *parent = nullptr);
    Q_INVOKABLE static void fetchDirectory();
    Q_INVOKABLE static void clearCache(); //redirect to cachemanager due to internal issue with initializing it in main.cpp

signals:

private:
    static DiskTools* _instance;
    explicit DiskTools(QObject *parent = nullptr);
    static QByteArray convertToRawData(QString path);
};

#endif // DISKTOOLS_H
