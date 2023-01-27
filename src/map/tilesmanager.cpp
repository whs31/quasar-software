#include "tilesmanager.h"

TilesManager* TilesManager::_instance = nullptr;

QString TilesManager::_street;
QString TilesManager::_satellite;
QString TilesManager::_terrain;
QString TilesManager::_transit;
QString TilesManager::_cycle;
QString TilesManager::_hiking;
QString TilesManager::_nighttransit;

TilesManager::TilesManager()
{
    InitializeConfig();
    Debug::Log("?[TILESERVER] Path initialized");
}

TilesManager* TilesManager::get()
{
    if(_instance != NULL)
        return _instance;
    _instance = new TilesManager();
    return _instance;
}

void TilesManager::InitializeConfig()
{
    QFile f_satellite(":/osmconfigs/satellite");
    f_satellite.open(QIODevice::ReadOnly);
    _satellite = f_satellite.readAll();

    QFile f_terrain(":/osmconfigs/terrain");
    f_terrain.open(QIODevice::ReadOnly);
    _terrain = f_terrain.readAll();

    QFile f_transit(":/osmconfigs/transit");
    f_transit.open(QIODevice::ReadOnly);
    _transit = f_transit.readAll();

    QFile f_cycle(":/osmconfigs/cycle");
    f_cycle.open(QIODevice::ReadOnly);
    _cycle = f_cycle.readAll();

    QFile f_hiking(":/osmconfigs/hiking");
    f_hiking.open(QIODevice::ReadOnly);
    _hiking = f_hiking.readAll();

    QFile f_nighttransit(":/osmconfigs/night-transit");
    f_nighttransit.open(QIODevice::ReadOnly);
    _nighttransit = f_nighttransit.readAll();

    QSaveFile satellite(CacheManager::getMapProviderCache() + "/satellite");
    satellite.open(QIODevice::WriteOnly);
    QTextStream out1(&satellite);
    out1 << _satellite;
    satellite.commit();

    QSaveFile terrain(CacheManager::getMapProviderCache() + "/terrain");
    terrain.open(QIODevice::WriteOnly);
    QTextStream out2(&terrain);
    out2 << _terrain;
    terrain.commit();

    QSaveFile transit(CacheManager::getMapProviderCache() + "/transit");
    transit.open(QIODevice::WriteOnly);
    QTextStream out3(&transit);
    out3 << _transit;
    transit.commit();

    QSaveFile cycle(CacheManager::getMapProviderCache() + "/cycle");
    cycle.open(QIODevice::WriteOnly);
    QTextStream out4(&cycle);
    out4 << _cycle;
    cycle.commit();

    QSaveFile hiking(CacheManager::getMapProviderCache() + "/hiking");
    hiking.open(QIODevice::WriteOnly);
    QTextStream out5(&hiking);
    out5 << _hiking;
    hiking.commit();

    QSaveFile nighttransit(CacheManager::getMapProviderCache() + "/night-transit");
    nighttransit.open(QIODevice::WriteOnly);
    QTextStream out6(&nighttransit);
    out6 << _nighttransit;
    nighttransit.commit();
    _street = "{\r\n    \"UrlTemplate\" : \""
              "file:///" +
              CacheManager::getTileServerCache() +
                "/%z/%x/%y.png"
                "\",\r\n    \"ImageFormat\" : \"png\",\r\n    "
                "\"QImageFormat\" : \"Indexed8\",\r\n    \"MaximumZoomLevel\" : 18,\r\n    \"ID\" : \"wmf-intl-1x\",\r\n    \"MapCopyRight\" : "
                "\"<a href=\'https://wikimediafoundation.org/wiki/Terms_of_Use\'>WikiMedia Foundation</a>\",\r\n    \"DataCopyRight\" : "
                "\"<a href=\'http://www.openstreetmap.org/copyright\'>OpenStreetMap</a> contributors\",\r\n    \"Timestamp\" : \"2019-02-01\"\r\n}\r\n";
    QSaveFile street(CacheManager::getMapProviderCache() + "/street");
    street.open(QIODevice::WriteOnly);
    QTextStream out7(&street);
    out7 << _street;
    street.commit();
}
