#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QVector>
#include <QMessageBox>

#include "models/timage.h"
#include "linkerqml.h"
#include "config/sconfig.h"
#include "config/runtimedata.h"


class ImageManager : public QObject
{
    Q_OBJECT
public:
    static ImageManager* initialize(QObject *parent = nullptr);
    static void newImage(QString filename, QByteArray rawData);
    static bool checkForOccurence(QString filename);
    Q_INVOKABLE static bool removeImage(qint32 index);
    Q_INVOKABLE static void clearAll(void);

signals:

private:
    explicit ImageManager(QObject *parent = nullptr);
    static ImageManager* _instance;
    static QVector<TImage*> imageList;

    
};

#endif // IMAGEMANAGER_H
