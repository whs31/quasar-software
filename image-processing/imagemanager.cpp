#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
    cacheDirectory = QCoreApplication::applicationDirPath()+QDir::separator()+"image-cache";
    QDir dir(cacheDirectory);
    if (!dir.exists()){
      dir.mkdir(cacheDirectory);
    }
    qInfo()<<"[FILEMANAGER] Working directory: "<<cacheDirectory;
}

bool ImageManager::CopyJPEG(const QString &path)
{
    QDir directory(path);
    QStringList fileList;
    directory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    directory.setNameFilters(QStringList("*.jpg"));
    QStringList entry_list = directory.entryList();
    for (QString entryString : entry_list)
    {
        fileList.append(entryString.prepend(path+"/"));
    }
    if(!fileList.empty())
    {
        for ( QString f : fileList ) {
            QFileInfo fileInfo(f);
            QString destinationFile = cacheDirectory + QDir::separator() + fileInfo.fileName();
            bool result = QFile::copy(f, destinationFile);
            result==true ? qDebug()<<"[FILEMANAGER] Copy success" : qWarning()<<"[FILEMANAGER] Copy failure";
        }
        return true;
    } return false;
}

