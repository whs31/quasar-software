#include "filesystem.h"
#include "config/settings.h"
#include "config/paths.h"
#include "processing/imageprocessing.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDebug>

using namespace OS;

Filesystem::Filesystem(QObject* parent)
  : QObject{parent}
{}

Filesystem *Filesystem::get() { static Filesystem instance; return &instance; }

bool Filesystem::fetchImageDirectory()
{
  QString folder = Config::Settings::get()->value<QString>("state/folder");
  if(folder.startsWith("file://"))
  {
    #ifdef Q_OS_WINDOWS
    folder.remove(0, strlen("file:///"));
    #else
    folder.remove(0, strlen("file://"));
    #endif
  }

  qDebug().noquote() << "[FILESYSTEM] Fetching images from" << folder;
  QList<QString> pass = this->fetchBinaryList(folder);

  QList<QString> path_list;
  QDir directory(folder, {"*.jpg"}, QDir::Name | QDir::IgnoreCase,
                 QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

  for (const QString& filename : directory.entryList())
    path_list.push_back(folder + "/" + filename);

  if(path_list.empty()) {
    qWarning() << "[FILESYSTEM] Target catalogue is empty, throwing warning window...";
    return false;
  }

  for(size_t i = 0; i < directory.entryList().size(); ++i)
  {
    if(not Processing::ImageProcessing::get()->exists(directory.entryList().at(i)))
    {
      qInfo().noquote().nospace() << "[FILESYSTEM] Found image " << directory.entryList().at(i)
                                  << " at path " << path_list.at(i).left(15) << "...";
      QFile::copy(path_list.at(i), Config::Paths::lod(0) + "/" + directory.entryList().at(i));
      pass.push_back(directory.entryList().at(i));
    }
    else
      qDebug() << "[FILESYSTEM] Occurrence found, skipping...";
  }

  emit imageListCached(pass);
  return true;
}

void Filesystem::fetchTCPCache()
{
  qDebug().noquote() << "[FILESYSTEM] Fetching images from" << Config::Paths::imageCache() + "/tcp";

  QList<QString> pass = this->fetchBinaryList(Config::Paths::imageCache() + "/tcp");
  QList<QString> path_list;

  QDir directory(Config::Paths::tcp(), {"*.jpg"}, QDir::Name | QDir::IgnoreCase,
                 QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

  for (const QString& filename : directory.entryList())
    path_list.push_back(Config::Paths::tcp() + "/" + filename);

  if(path_list.empty()) {
    qWarning() << "[FILESYSTEM] Target catalogue is empty, throwing warning window";
    return;
  }

  for(size_t i = 0; i < directory.entryList().size(); ++i)
  {
    qInfo().noquote().nospace() << "[FILESYSTEM] Found image " << directory.entryList().at(i)
                                << " at path " << path_list.at(i).left(15) << "...";
    QFile::copy(path_list.at(i), Config::Paths::lod(0) + "/" + directory.entryList().at(i));
    QFile::remove(path_list.at(i));
    pass.push_back(directory.entryList().at(i));

    if(int ndex = Processing::ImageProcessing::get()->indexFrom(directory.entryList().at(i)))
    {
      qDebug() << "[FILESYSTEM] Occurrence found in TCP cache. Replacing...";
      qDebug() << "$ [PROCESSING] Replacing is not implemented for now.";
      //Processing::ImageProcessing::get()->model()->remove(ndex);
    }
  }

  emit imageListCached(pass);
}

void Filesystem::exportImagesToFolder(const QList<QString>& ls, const QString& folder)
{
  auto folder_fixed = folder;
  if(folder_fixed.startsWith("file:"))
    #ifdef Q_OS_WIN
    folder_fixed.remove("file:///");
    #else
    folder_fixed.remove("file://");
  #endif

  int i = 0;
  for(const auto& img : ls)
  {
    i++;
    QString dest = folder_fixed + "/image-" + QString::number(i) + ".png";
    QFile::copy(img, dest);
    qDebug() << "$ [FILESYSTEM] Image" << img << "exported as" << dest;
  }
}

QList<QString> Filesystem::fetchBinaryList(const QString& path)
{
  QList<QString> ret;
  qDebug().noquote() << "[FILESYSTEM] Fetching binaries from" << path;

  QList<QString> path_list;
  QDir directory(path, {"*.bin"}, QDir::Name | QDir::IgnoreCase,
                 QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

  for(const QString& filename : directory.entryList())
    path_list.push_back(Config::Settings::get()->value<QString>("state/folder") + "/" + filename);

  if(path_list.empty()) {
    qDebug() << "[FILESYSTEM] Target catalogue does not contain binaries";
    return ret;
  }

  for(size_t i = 0; i < directory.entryList().size(); ++i)
  {
    if(not Processing::ImageProcessing::get()->exists(directory.entryList().at(i)))
    {
      qInfo().noquote().nospace() << "[FILESYSTEM] Found binary " << directory.entryList().at(i)
                                  << " at path " << path_list.at(i).left(15) << "...";
      QFile::copy(path_list.at(i), Config::Paths::lod(0) + "/" + directory.entryList().at(i));
      ret.push_back(directory.entryList().at(i));
    }
    else
      qDebug() << "[FILESYSTEM] Binary occurrence found, skipping...";
  }

  return ret;
}

