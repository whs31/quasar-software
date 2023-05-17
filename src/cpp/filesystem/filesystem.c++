#include "filesystem.h"
#include "config/config.h"
#include "config/paths.h"
#include "processing/imageprocessing.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDebug>

using namespace OS;

bool Filesystem::fetchImageDirectory()
{
    qDebug().noquote() << "[FILESYSTEM] Fetching images from" << CONFIG(storedCatalogue);
    this->fetchBinary();

    QStringList initial_file_list;
    QDir initial_directory(CONFIG(storedCatalogue), {"*.jpg"}, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    for (const QString& str : initial_directory.entryList())
        initial_file_list.append(CONFIG(storedCatalogue) + "/" + str);

    if(initial_file_list.empty())
    {
        qWarning() << "[FILESYSTEM] Target catalogue is empty, throwing warning window...";
        return false;
    }

    for(int i = 0; i < initial_directory.entryList().size(); ++i) {
        if(not Processing::ImageProcessing::get()->exists(initial_directory.entryList().at(i)))
        {
            qInfo().noquote().nospace() << "[FILESYSTEM] Found image " << initial_directory.entryList().at(i) << " at path " << initial_file_list.at(i).left(15) << "...";

            QFile::copy(initial_file_list.at(i), Config::Paths::imageCache() + "/lod0/" + initial_directory.entryList().at(i));
            emit imageCached(initial_directory.entryList().at(i));
        }
        else
            qDebug() << "[FILESYSTEM] Occurence found, skipping...";
    }
    return true;
}

Filesystem::Filesystem(QObject* parent)
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

void Filesystem::fetchBinary()
{
    qDebug().noquote() << "[FILESYSTEM] Fetching binaries from" << CONFIG(storedCatalogue);

    QStringList initial_file_list;
    QDir initial_directory(CONFIG(storedCatalogue), {"*.bin"}, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    for (const QString& str : initial_directory.entryList())
        initial_file_list.append(CONFIG(storedCatalogue) + "/" + str);

    if(initial_file_list.empty())
    {
        qDebug() << "[FILESYSTEM] Target catalogue does not contain binaries";
        return;
    }

    for(int i = 0; i < initial_directory.entryList().size(); ++i) {
        if(not Processing::ImageProcessing::get()->exists(initial_directory.entryList().at(i)))
        {
            qInfo().noquote().nospace() << "[FILESYSTEM] Found binary " << initial_directory.entryList().at(i) << " at path " << initial_file_list.at(i).left(15) << "...";

            QFile::copy(initial_file_list.at(i), Config::Paths::imageCache() + "/lod0/" + initial_directory.entryList().at(i));
            emit binaryCached(initial_directory.entryList().at(i));
        }
        else
            qDebug() << "[FILESYSTEM] Binary occurence found, skipping...";
    }
}

