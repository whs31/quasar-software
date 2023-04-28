#include "paths.h++"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QSaveFile>
#include <QtCore/QTextStream>

using namespace Config;

Paths *Paths::instance = nullptr;
Paths *Paths::get(QObject *parent)
{
    if(instance != nullptr)
        return instance;
    instance = new Paths(parent);
    return instance;
}
Paths::Paths(QObject *parent) : QObject{parent}
{
    this->createImageCache();

    QDir dir(mapConfig());
    if(not dir.exists())
    {
        dir.mkpath(mapConfig());
        qInfo() << "[PATH] Created map config folder at " << mapConfig();
    }

    this->createMapConfigs();

    QDir dir1(plugins());
    if(not dir1.exists())
    {
        dir1.mkpath(plugins());
        qInfo() << "[PATH] Created plugins folder at " << plugins();
    }

    QDir dir2(config());
    if(not dir2.exists())
    {
        dir2.mkpath(config());
        qInfo() << "[PATH] Created config folder at " << config();
    }

    QDir dir3(logs());
    if(not dir3.exists())
    {
        dir3.mkpath(logs());
        qInfo() << "[PATH] Created logs folder at " << logs();
    }

    QDir dir4(themes());
    if(not dir4.exists())
    {
        dir4.mkpath(themes());
        qInfo() << "[PATH] Created themes folder at" << themes();
    }

    QString default_theme_buffer;

    QFile default_theme_source(":/themes/nord.json");
    default_theme_source.open(QIODevice::ReadOnly);
    default_theme_buffer = default_theme_source.readAll();

    QSaveFile default_theme_destination(themes() + "/nord.json");
    default_theme_destination.open(QIODevice::WriteOnly);
    QTextStream out1(&default_theme_destination);
    out1 << default_theme_buffer;
    default_theme_destination.commit();

    qInfo() << "[PATH] Default theme placed in folder";
}

QString Paths::root() { return QCoreApplication::applicationDirPath(); }
QString Paths::imageCache() { return root() + "/cache"; }
QString Paths::mapConfig() { return config() + "/map"; }
QString Paths::plugins() { return root() + "/plugins"; }
QString Paths::config() { return root() + "/config"; }
QString Paths::logs() { return root() + "/logs"; }
QString Paths::themes() { return root() + "/themes"; }

void Paths::createImageCache(void)
{
    QDir dir(imageCache());
    if(not dir.exists())
        dir.mkpath(imageCache());
    qInfo() << "[PATH] Created image cache at " << imageCache();
}

void Paths::clearImageCache(void)
{
    QDir dir(imageCache());
    if(dir.exists())
        dir.removeRecursively();
    qWarning() << "[PATH] Deleted image cache";
    createImageCache();
}

//========== private part ==========

void Paths::createMapConfigs(void)
{
    QString _satellite;
    QString _terrain;
    QString _transit;
    QString _cycle;
    QString _hiking;
    QString _nighttransit;
    QString _street;

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

    QSaveFile satellite(mapConfig() + "/satellite");
    satellite.open(QIODevice::WriteOnly);
    QTextStream out1(&satellite);
    out1 << _satellite;
    satellite.commit();

    QSaveFile terrain(mapConfig() + "/terrain");
    terrain.open(QIODevice::WriteOnly);
    QTextStream out2(&terrain);
    out2 << _terrain;
    terrain.commit();

    QSaveFile transit(mapConfig() + "/transit");
    transit.open(QIODevice::WriteOnly);
    QTextStream out3(&transit);
    out3 << _transit;
    transit.commit();

    QSaveFile cycle(mapConfig() + "/cycle");
    cycle.open(QIODevice::WriteOnly);
    QTextStream out4(&cycle);
    out4 << _cycle;
    cycle.commit();

    QSaveFile hiking(mapConfig() + "/hiking");
    hiking.open(QIODevice::WriteOnly);
    QTextStream out5(&hiking);
    out5 << _hiking;
    hiking.commit();

    QSaveFile nighttransit(mapConfig() + "/night-transit");
    nighttransit.open(QIODevice::WriteOnly);
    QTextStream out6(&nighttransit);
    out6 << _nighttransit;
    nighttransit.commit();
    _street = "{\r\n    \"UrlTemplate\" : \""
              "file:///" +
              mapConfig() +
              "/%z/%x/%y.png"
              "\",\r\n    \"ImageFormat\" : \"png\",\r\n    "
              "\"QImageFormat\" : \"Indexed8\",\r\n    \"MaximumZoomLevel\" : 18,\r\n    \"ID\" : \"wmf-intl-1x\",\r\n    \"MapCopyRight\" : "
              "\"<a href=\'https://wikimediafoundation.org/wiki/Terms_of_Use\'>WikiMedia Foundation</a>\",\r\n    \"DataCopyRight\" : "
              "\"<a href=\'http://www.openstreetmap.org/copyright\'>OpenStreetMap</a> contributors\",\r\n    \"Timestamp\" : \"2019-02-01\"\r\n}\r\n";
    QSaveFile street(mapConfig() + "/street");
    street.open(QIODevice::WriteOnly);
    QTextStream out7(&street);
    out7 << _street;
    street.commit();
    qDebug() << "[PATH] Map configs placed in folder";
}

