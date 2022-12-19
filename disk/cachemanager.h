#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include "debug.h"
#include "sconfig.h"
#include "disktools.h"

class CacheManager : public QObject
{
    Q_OBJECT
public:
    static CacheManager* initializeCache();
    static void setupImageCache(void);
    Q_INVOKABLE static void clearImageCache(); 

    static QString getTcpDowloaderCache();
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
    static QString mapProviderCache;
    static QString tileServerCache;
    static QString dynamicResourcesCache;

    static QString settingsPath;

};

#endif // CACHEMANAGER_H
