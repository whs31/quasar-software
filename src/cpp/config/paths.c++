#include "paths.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QSaveFile>
#include <QtCore/QTextStream>

using namespace Config;

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

    QDir dir5(offlineTiles());
    if(not dir5.exists())
    {
        dir5.mkpath(offlineTiles());
        qInfo() << "[PATH] Created offline tiles folder at" << offlineTiles();
    }

    QDir dir6(runtimeBash());
    if(not dir6.exists())
    {
        dir6.mkpath(runtimeBash());
        qInfo() << "[PATH] Created bash and runtime bash folders at" << runtimeBash();
    }

    if(dir4.isEmpty())
    {
        QFile::copy(":/themes/nord.json", themes() + "/nord.json");
        QFile::copy(":/themes/catpuccin.json", themes() + "/catpuccin.json");
        qInfo() << "[PATH] Default themes placed in folder";
    }

    QDir dir_bash(bash());
    if(dir_bash.isEmpty(QDir::Files))
    {
        QFile::copy(":/wrapped/poweroff.sh", bash() + "/poweroff.sh");
        QFile::copy(":/wrapped/reboot.sh", bash() + "/reboot.sh");
    }
}

QString Paths::root() { return QCoreApplication::applicationDirPath(); }
QString Paths::imageCache() { return root() + "/cache"; }

QString Paths::lod(int level)
{
    if(level > LOD_LEVELS - 1) {
        qCritical() << "[PATH] Someone asked for non-existent LOD folder";
        return "Invalid LOD level";
    }
    return imageCache() + "/lod" + QString::number(level);
}

QString Paths::tcp() { return imageCache() + "/tcp"; }
QString Paths::mapConfig() { return config() + "/map"; }
QString Paths::offlineTiles() { return root() + "/offline"; }
QString Paths::plugins() { return root() + "/plugins"; }
QString Paths::config() { return root() + "/config"; }
QString Paths::logs() { return root() + "/logs"; }
QString Paths::themes() { return root() + "/themes"; }
QString Paths::bash() { return root() + "/bash"; }
QString Paths::runtimeBash() { return bash() + "/custom"; }

void Paths::createImageCache(void)
{
    QDir dir(imageCache());
    if(not dir.exists())
    {
        dir.mkpath(imageCache());
        dir.mkpath(tcp());
        for(size_t i = 0; i < LOD_LEVELS; ++i)
            dir.mkpath(lod(i));
    }
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

void Paths::createMapConfigs(void)
{
    QFile::copy(":/osmconfigs/satellite", mapConfig() + "/satellite");
    QFile::copy(":/osmconfigs/terrain", mapConfig() + "/terrain");
    QFile::copy(":/osmconfigs/transit", mapConfig() + "/transit");
    QFile::copy(":/osmconfigs/cycle", mapConfig() + "/cycle");
    QFile::copy(":/osmconfigs/hiking", mapConfig() + "/hiking");
    QFile::copy(":/osmconfigs/night-transit", mapConfig() + "/night-transit");

    QString _street = "{\r\n    \"UrlTemplate\" : \""
              "file:///" +
              offlineTiles() +
              "/%z/%x/%y"
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

