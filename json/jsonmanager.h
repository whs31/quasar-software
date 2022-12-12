#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QFile>
#include <QSaveFile>
#include <QJsonObject>
#include <QJsonDocument>

#include "debug.h"


class JSONManager : public QObject
{
    Q_OBJECT
public:
    explicit JSONManager();
    static QJsonObject parseJSON(QString path);
    //static void editJSONValue(QJsonObject object, QString key, QString value);

signals:

};

#endif // JSONMANAGER_H
