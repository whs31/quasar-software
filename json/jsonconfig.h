#ifndef JSONCONFIG_H
#define JSONCONFIG_H

#include <QObject>

#include "jsonmanager.h"

class JsonConfig : public QObject
{
    Q_OBJECT
public:
    explicit JsonConfig(QString filename);

signals:

};

#endif // JSONCONFIG_H
