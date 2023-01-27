#include "disktools.h"

DiskTools *DiskTools::_instance = nullptr;
DiskTools::DiskTools(QObject *parent)
    : QObject{parent}
{
}
DiskTools *DiskTools::get(QObject *parent)
{
    if (_instance != nullptr)
        return _instance;
    _instance = new DiskTools(parent);
    return _instance;
}

void DiskTools::fetchDirectory()
{
    QStringList initialFileList;
        QDir initialDirectory(SConfig::get()->getDefaultCatalogue());
        initialDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
        initialDirectory.setNameFilters(QStringList("*.jpg"));
        for (QString entryString : initialDirectory.entryList())
        {
            initialFileList.append(entryString.prepend(SConfig::get()->getDefaultCatalogue() + "/"));
        }
    if (!initialFileList.empty())
    {
        for (QString filename : initialFileList)
        {
            if(!ImageManager::checkForOccurence(filename))
            {
                ImageManager::newImage(filename, convertToRawData(filename));
            } else 
            {
                Debug::Log("?[DISK] Occurence found, skipping...");
            }
        }
    } else {
        Debug::Log("![DISK] Directory is empty, throwing warning window...");
        RuntimeData::get()->setStatusPopup("В выбранном каталоге " +
                                           SText::colorText("не найдены изображения!", ThemeManager::get()->getErrorLighter()));
        RuntimeData::get()->setStatusPopupTrigger(true);
    }
}

void DiskTools::clearCache(void)
{
    CacheManager::clearImageCache();
}

QByteArray DiskTools::convertToRawData(QString path)
{
    QFile imageFile(path);
    if(imageFile.open(QIODevice::ReadOnly))
    {
        QByteArray rawData = imageFile.readAll();
        return rawData;
    } else {
        Debug::Log("!!Error opening the image file for converting to raw bytes data");
        return QByteArray();
    }
}
