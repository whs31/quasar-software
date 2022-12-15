#include "cachemanager.h"

CacheManager* CacheManager::_instance = nullptr;

QString CacheManager::tcpDowloaderCache;
QString CacheManager::mapProviderCache;
QString CacheManager::tileServerCache;
QString CacheManager::dynamicResourcesCache;
QString CacheManager::settingsPath;

CacheManager* CacheManager::initializeCache()
{
    if(_instance != nullptr)
        return _instance;
    _instance = new CacheManager();
    DiskTools::initialize(initializeCache());
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
    tcpDowloaderCache = QCoreApplication::applicationDirPath()+"/appcache/tcpdcache";
    QDir tcp(tcpDowloaderCache);
    if(!tcp.exists()) { tcp.mkpath(tcpDowloaderCache); }
    SConfig::setHashValue("FlightPath", tcpDowloaderCache);
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
    {}
    Debug::Log("[CACHEMANAGER] Cache cleared");
    setupImageCache();
}

QString CacheManager::getTcpDowloaderCache() { return CacheManager::tcpDowloaderCache; }
QString CacheManager::getMapProviderCache() { return mapProviderCache; }
QString CacheManager::getTileServerCache() { return tileServerCache; }
QString CacheManager::getDynamicResourcesCache() { return dynamicResourcesCache; }
QString CacheManager::getSettingsPath() { return settingsPath; }

CacheManager::CacheManager()
{
    initialize();
    setupImageCache();
    Debug::Log("?[CACHEMANAGER] TCP Downloader directory: "+CacheManager::tcpDowloaderCache);

}
