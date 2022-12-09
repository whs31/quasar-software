#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include "debug.h"
#include "sconfig.h"

enum ClearMode : short int
{
    ClearAll,
    ClearTCP,
    ClearPNG
};

class CacheManager : public QObject
{
    Q_OBJECT
public:
    static CacheManager* initializeCache();
    static void setupImageCache(void);
    static void clearImageCache(ClearMode mode = ClearMode::ClearAll);

    static QString getTcpDowloaderCache();
    static QString getPngCache();
    static QString getMapProviderCache();
    static QString getTileServerCache();
    static QString getDynamicResourcesCache();

    static QString getSettingsPath();

signals:

private:
    explicit CacheManager(); 
    static CacheManager* _instance;
    static void initialize(void);

    static QString tcpDowloaderCache;
    static QString pngCache;
    static QString mapProviderCache;
    static QString tileServerCache;
    static QString dynamicResourcesCache;

    static QString settingsPath;

};

#endif // CACHEMANAGER_H
