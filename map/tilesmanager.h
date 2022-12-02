#ifndef TILESMANAGER_H
#define TILESMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QDir>

#include "sconfig.h"
#include "jsonmanager.h"

class TilesManager : public QObject
{
    Q_OBJECT
public:
    explicit TilesManager(QObject *parent = nullptr);
    static void InitializeConfig();
    static QString OSMConfigsPath;
    static QString TileServerPath;

signals:

};

#endif // TILESMANAGER_H
