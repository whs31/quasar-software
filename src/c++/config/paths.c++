#include "paths.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QSaveFile>
#include <QtCore/QTextStream>

#define PATH_MKDIR(name) QDir name##Directory(name());                                              \
                         if(not name##Directory.exists()) {                                         \
                             name##Directory.mkpath(name());                                        \
                             qInfo() << "[PATH] Created" << #name << "folder at" << name();         \
                         }

using namespace Config;

Paths::Paths(QObject *parent) : QObject{parent}
{
  this->createImageCache();

  PATH_MKDIR(config)
  PATH_MKDIR(mapConfig)
  PATH_MKDIR(themes)
  PATH_MKDIR(offlineTiles)
  PATH_MKDIR(logs)

  this->createMapConfigs();

  if(themesDirectory.isEmpty())
  {
    QFile::copy(":/themes/dark.json", themes() + "/dark.json");
    QFile::copy(":/themes/light.json", themes() + "/light.json");
    qInfo() << "[PATH] Default themes placed in folder";
  }
}

Paths *Paths::get() { static Paths instance; return &instance; }
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
QString Paths::config() { return root() + "/config"; }
QString Paths::logs() { return root() + "/logs"; }
QString Paths::themes() { return root() + "/themes"; }

void Paths::createImageCache() noexcept
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

void Paths::clearImageCache() noexcept
{
  QDir dir(imageCache());
  if(dir.exists())
    dir.removeRecursively();
  qWarning() << "[PATH] Deleted image cache";
  createImageCache();
}

void Paths::createMapConfigs() noexcept
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

