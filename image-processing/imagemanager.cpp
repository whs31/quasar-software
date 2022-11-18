#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
    cacheDirectory = QCoreApplication::applicationDirPath()+QDir::separator()+"image-cache";
    QDir dir(cacheDirectory);
    if (!dir.exists()){
      dir.mkdir(cacheDirectory);
    }
    PNGDirectory = QCoreApplication::applicationDirPath()+QDir::separator()+"png-cache";
    qInfo()<<"[FILEMANAGER] Working directory: "<<cacheDirectory<<", .png directory: "<<PNGDirectory;
    //на случай если ne захочется кешировать в отдельную папку
    //PNGDirectory = cacheDirectory;
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
            MakePNG(f);
        }
        return true;
    } return false;
}

bool ImageManager::MakePNG(QString jpeg)
{
    QFile file(jpeg);
    QString filename = file.fileName();
    filename.chop(3); filename.append("png");
    QPixmap pix(jpeg);
    pix.save(PNGDirectory+QDir::separator()+filename);
}


QString ImageManager::getCacheDirectory(void)                   { return cacheDirectory;                                              }
QString ImageManager::getPNGDirectory(void)                     { return PNGDirectory;                                                }
