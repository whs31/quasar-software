#include "filesystem.h++"
#include "config/config.h++"
#include "config/paths.h++"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDebug>

using namespace OS;

DECLARE_SINGLETON_IMPL(Filesystem)

bool Filesystem::fetchImageDirectory()
{
    qDebug().noquote() << "[FILESYSTEM] Fetching images from" << CONFIG(storedCatalogue);

    QStringList initial_file_list;
    QDir initial_directory(CONFIG(storedCatalogue), {"*.jpg"}, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    for (const QString& str : initial_directory.entryList())
        initial_file_list.append(CONFIG(storedCatalogue) + "/" + str);

    if(initial_file_list.empty())
    {
        qWarning() << "[FILESYSTEM] Target catalogue is empty, throwing warning window...";
        return false;
    }

    for (int i = 0; i < initial_directory.entryList().size(); ++i) {
        if(not checkOcurrence(Config::Paths::imageCache() + "/lod0", initial_directory.entryList().at(i)))
        {
            qInfo().noquote().nospace() << "[FILESYSTEM] Found image " << initial_directory.entryList().at(i) << " at path " << initial_file_list.at(i).left(15) << "...";
            // IMPL HERE
            return true;
        }
        else
            qDebug() << "[FILESYSTEM] Occurence found, skipping...";
    }
}

Filesystem::Filesystem(QObject *parent)
    : QObject{parent}
{

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

