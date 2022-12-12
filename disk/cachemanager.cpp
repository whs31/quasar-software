#include "cachemanager.h"

CacheManager* CacheManager::_instance = NULL;

QString CacheManager::tcpDowloaderCache;
QString CacheManager::pngCache;
QString CacheManager::mapProviderCache;
QString CacheManager::tileServerCache;
QString CacheManager::dynamicResourcesCache;
QString CacheManager::settingsPath;

CacheManager* CacheManager::initializeCache()
{
    if(_instance != NULL)
        return _instance;
    _instance = new CacheManager();
    return _instance;
}

void CacheManager::initialize()
{
    settingsPath = QCoreApplication::applicationDirPath()+"/appconfig";
    QDir settings(settingsPath);
    if(!settings.exists()) { settings.mkpath(settingsPath); }

    mapProviderCache = QCoreApplication::applicationDirPath()+"/apposmconfig";
    QDir osmconfigs(mapProviderCache);
    osmconfigs.mkpath(mapProviderCache);

    tileServerCache = QCoreApplication::applicationDirPath()+"/-Tiles";
    QDir tiles(tileServerCache);
    if(!tiles.exists()) { tiles.mkpath(tileServerCache); }
    Debug::Log("?[CACHEMANAGER] Initial cache created");
}

void CacheManager::setupImageCache()
{
    pngCache = QCoreApplication::applicationDirPath()+"/appcache/pngcache";
    tcpDowloaderCache = QCoreApplication::applicationDirPath()+"/appcache/tcpdcache";
    QDir png(pngCache);
    QDir tcp(tcpDowloaderCache);
    if(!png.exists()) { png.mkpath(pngCache); }
    if(!tcp.exists()) { tcp.mkpath(tcpDowloaderCache); }
    SConfig::CACHEPATH = tcpDowloaderCache;
    Debug::Log("?[CACHEMANAGER] Image cache created");
}

void CacheManager::clearImageCache(ClearMode mode)
{
    if(mode == ClearMode::ClearAll || mode == ClearMode::ClearTCP)
    {
        QDir tcp(tcpDowloaderCache);
        if(tcp.exists()) { tcp.removeRecursively(); }
    }
    if(mode == ClearMode::ClearAll || mode == ClearMode::ClearPNG)
    {
        QDir png(pngCache);
        if(png.exists()) { png.removeRecursively(); }
    }
    Debug::Log("[CACHEMANAGER] Cache cleared");
    setupImageCache();
}

QString CacheManager::getTcpDowloaderCache() { return CacheManager::tcpDowloaderCache; }
QString CacheManager::getPngCache() { return CacheManager::pngCache; }
QString CacheManager::getMapProviderCache() { return mapProviderCache; }
QString CacheManager::getTileServerCache() { return tileServerCache; }
QString CacheManager::getDynamicResourcesCache() { return dynamicResourcesCache; }
QString CacheManager::getSettingsPath() { return settingsPath; }

CacheManager::CacheManager()
{
    initialize();
    setupImageCache();
    Debug::Log("?[CACHEMANAGER] .png directory: "+CacheManager::pngCache);
    Debug::Log("?[CACHEMANAGER] TCP Downloader directory: "+CacheManager::tcpDowloaderCache);
}
