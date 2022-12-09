#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
}

QStringList ImageManager::GetDiff(QStringList existingFileList)
{
    QDir pngDirectory(CacheManager::getPngCache());
    QStringList pngFileList;
    QStringList diff;
    pngDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    pngDirectory.setNameFilters(QStringList("*.png"));
    for (QString entryString : pngDirectory.entryList())
    {
        pngFileList.append(entryString);
    }
    for (int i = 0; i<pngFileList.length(); i++)
    {
        pngFileList[i].chop(4);
    }
    Debug::Log("[FILEMANAGER] Found "+QString::number(pngFileList.length())+" files in cache");
    for(QString str : existingFileList)
    {
        if(!pngFileList.contains(str))
        {
            diff.append(str);
        }
    }
    return diff;
}

QStringList ImageManager::GetInitialList(const QString &path, QStringList diff)
{
    QDir initialDirectory(path);
    QStringList initialFileList;
    initialDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    initialDirectory.setNameFilters(QStringList("*.jpg"));
    for (QString entryString : initialDirectory.entryList())
    {
        initialFileList.append(entryString.prepend(path+"/"));
    }
    if(!initialFileList.empty())
    {
        for ( QString initialFile : initialFileList )
        {
            QFileInfo fileInfo(initialFile);
            if(!diff.empty()&&diffConvert(diff, ImageFormat::JPEG).contains(fileInfo.fileName()))
            {
                MakePNG(initialFile);
            }
        }
        return initialFileList;
    }
    return {}; //.empty() = true
}

QStringList ImageManager::GetPartialList(const QString &path, QStringList diff)
{
    QDir initialDirectory(path);
    QStringList initialFileList;
    QStringList partialFileList;
    initialDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    initialDirectory.setNameFilters(QStringList("*.jpg"));
    for (QString entryString : initialDirectory.entryList())
    {
        initialFileList.append(entryString.prepend(path+"/"));
    }
    if(!initialFileList.empty())
    {
        for ( QString initialFile : initialFileList )
        {
            QFileInfo fileInfo(initialFile);
            if(!diff.empty()&&diffConvert(diff, ImageFormat::JPEG).contains(fileInfo.fileName()))
            {
                partialFileList.append(initialFile);
                MakePNG(initialFile);
            }
        }
        return partialFileList;
    }
    return {}; //.empty() = true
}

bool ImageManager::saveRawData(QByteArray data, QString filename)
{
    data.reserve(sizeof(data));

    QString path = CacheManager::getTcpDowloaderCache();
    path.append("/");
    path.append(filename);
    QDir::toNativeSeparators(path);
    QSaveFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.commit();
    return true;
}

QStringList ImageManager::diffConvert(QStringList diff, ImageFormat format)
{
    switch (format) {
    case 0:
        for(int i = 0; i<diff.length(); i++)
        {
            diff[i].chop(4);
        }
        break;
    case 1:
        for(int i = 0; i<diff.length(); i++)
        {
            diff[i].append(".jpg");
        }
        break;
    case 2:
        for(int i = 0; i<diff.length(); i++)
        {
            diff[i].append(".png");
        }
        break;
    default:
        break;
    } return diff;
}

QString ImageManager::MakePNG(QString jpeg)
{
    Debug::Log("[FILEMANAGER] Making png file out of "+jpeg);
    QFile file(jpeg);
    QFileInfo f(file);
    QString filename = f.fileName();
    filename.chop(3); filename.append("png");
    QImage pixMap(jpeg);
    pixMap = AlphaMask::enableAlphaSupport(pixMap);
    QString finalFile = CacheManager::getPngCache()+'/'+filename;
    QDir::toNativeSeparators(finalFile);
    pixMap.save(finalFile);
    return finalFile;
}







