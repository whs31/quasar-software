#include "cachemanager.h"
#include <QDebug>

CacheManager *CacheManager::_instance = nullptr;

QString CacheManager::tcpDowloaderCache;
QString CacheManager::mapProviderCache;
QString CacheManager::tileServerCache;
QString CacheManager::dynamicResourcesCache;
QString CacheManager::pluginCache;
QString CacheManager::settingsPath;

CacheManager *CacheManager::get(QObject *parent)
{
    if (_instance != nullptr)
        return _instance;
    _instance = new CacheManager(parent);
    DiskTools::get(get());
    return _instance;
}

void CacheManager::initialize()
{
    settingsPath = QCoreApplication::applicationDirPath() + "/appconfig";
    QDir settings(settingsPath);
    if(!settings.exists())
        settings.mkpath(settingsPath);
    QDir logs(settingsPath + "/logs");
    if(!logs.exists())
        logs.mkpath(settingsPath + "/logs");

    mapProviderCache = QCoreApplication::applicationDirPath() + "/apposmconfig";
    QDir osmconfigs(mapProviderCache);
    osmconfigs.mkpath(mapProviderCache);

    tileServerCache = QCoreApplication::applicationDirPath() + "/app-offline-tiles";
    QDir tiles(tileServerCache);
    if(!tiles.exists())
        tiles.mkpath(tileServerCache);

    pluginCache = QCoreApplication::applicationDirPath() + "/app-plugins";
    QDir plugins(pluginCache);
    if(!plugins.exists())
        plugins.mkpath(pluginCache);

    qInfo() << "[CACHEMANAGER] Initial cache created";
}

void CacheManager::setupImageCache()
{
    tcpDowloaderCache = QCoreApplication::applicationDirPath() + "/appcache/tcpdcache";
    QDir tcp(tcpDowloaderCache);
    if (tcp.exists())
        tcp.mkpath(tcpDowloaderCache);
    qInfo() << "[CACHEMANAGER] Image cache created";
}

void CacheManager::clearImageCache()
{
    QDir tcp(tcpDowloaderCache);
    if (tcp.exists())
        tcp.removeRecursively();

    qInfo() << "[CACHEMANAGER] Cache cleared";

    setupImageCache();
}

QString CacheManager::getTcpDowloaderCache() { return CacheManager::tcpDowloaderCache; }
QString CacheManager::getMapProviderCache() { return mapProviderCache; }
QString CacheManager::getTileServerCache() { return tileServerCache; }
QString CacheManager::getDynamicResourcesCache() { return dynamicResourcesCache; }
QString CacheManager::getPluginsCache() { return pluginCache; }
QString CacheManager::getSettingsPath() { return settingsPath; }

CacheManager::CacheManager(QObject *parent) : QObject{parent}
{
    initialize();
    setupImageCache();

    qInfo() << ("[CACHEMANAGER] TCP Downloader directory: " + CacheManager::tcpDowloaderCache);
}
