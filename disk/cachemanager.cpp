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

}

void CacheManager::initialize()
{
    settingsPath = QCoreApplication::applicationDirPath()+"/appconfig";
    QDir settings(settingsPath);
    if(!settings.exists()) { settings.mkpath(settingsPath); }
}

void CacheManager::setupImageCache()
{

}

void CacheManager::clearImageCache()
{

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
    Debug::Log("?[FILEMANAGER] .png directory: "+CacheManager::pngCache);
    Debug::Log("?[FILEMANAGER] TCP Downloader directory: "+CacheManager::tcpDowloaderCache);
}
