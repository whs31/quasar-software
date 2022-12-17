#ifndef DISKTOOLS_H
#define DISKTOOLS_H

#include <QObject>
#include <QDir>
#include <QStringList>
#include <QFile>

#include "sconfig.h"
#include "imagemanager.h"
#include "debug.h"

class DiskTools : public QObject
{
    Q_OBJECT
public:
    static DiskTools* initialize(QObject *parent = nullptr);
    static void fetchDirectory();

signals:

private:
    static DiskTools* _instance;
    explicit DiskTools(QObject *parent = nullptr);
    static QByteArray convertToRawData(QString path);
};

#endif // DISKTOOLS_H
