#include "filesystem.h"
#include "config/config.h"
#include "config/paths.h"
#include "processing/imageprocessing.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDebug>

using namespace OS;

Filesystem::Filesystem(QObject* parent)
    : QObject{parent} { }

bool Filesystem::fetchImageDirectory()
{
    qDebug().noquote() << "[FILESYSTEM] Fetching images from" << CONFIG(storedCatalogue);
    QList<QString> pass = this->fetchBinaryList();

    QList<QString> path_list;
    QDir directory(CONFIG(storedCatalogue), {"*.jpg"}, QDir::Name | QDir::IgnoreCase,
                   QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    for (const QString& filename : directory.entryList())
        path_list.push_back(CONFIG(storedCatalogue) + "/" + filename);

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
            QFile::copy(path_list.at(i), Config::Paths::imageCache() + "/lod0/" + directory.entryList().at(i));
            pass.push_back(directory.entryList().at(i));
        }
        else
            qDebug() << "[FILESYSTEM] Occurence found, skipping...";
    }

    emit imageListCached(pass);
    return true;
}

bool Filesystem::checkOcurrence(QString target_folder, QString filename)
{
    QStringList initial_file_list;
    QDir initial_directory(target_folder, {"*.jpg"}, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    for(const QString& str : initial_directory.entryList())
        if(str == filename)
            return true;
    return false;
}

QList<QString> Filesystem::fetchBinaryList()
{
    QList<QString> ret;
    qDebug().noquote() << "[FILESYSTEM] Fetching binaries from" << CONFIG(storedCatalogue);

    QList<QString> path_list;
    QDir directory(CONFIG(storedCatalogue), {"*.bin"}, QDir::Name | QDir::IgnoreCase,
                   QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    for(const QString& filename : directory.entryList())
        path_list.push_back(CONFIG(storedCatalogue) + "/" + filename);

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
            QFile::copy(path_list.at(i), Config::Paths::imageCache() + "/lod0/" + directory.entryList().at(i));
            ret.push_back(directory.entryList().at(i));
        }
        else
            qDebug() << "[FILESYSTEM] Binary occurence found, skipping...";
    }

    return ret;
}

