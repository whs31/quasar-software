#ifndef TILESMANAGER_H
#define TILESMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QSaveFile>
#include <QDir>

#include "cachemanager.h"

#include <QTextStream>

class TilesManager : public QObject
{
    Q_OBJECT
public:
    explicit TilesManager(bool useLocalTileServer = false);
    static void InitializeConfig();

private:
    static QString _street;
    static QString _satellite;
    static QString _terrain;
    static QString _transit;
    static QString _cycle;
    static QString _hiking;
    static QString _nighttransit;

    static bool useLocalTileServer;

signals:

};

#endif // TILESMANAGER_H
