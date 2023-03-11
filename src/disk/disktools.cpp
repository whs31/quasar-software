#include "disktools.h"
#include "theme/include/theme.hpp"
#include "func/stext.h"

#include <QDebug>

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
                qDebug() << "[DISK] Occurence found, skipping...";
            }
        }
    } else {
        qWarning() << "[DISK] Directory is empty, throwing warning window...";

        RuntimeData::get()->statusPopupSet("В выбранном каталоге " +
                                           SText::colorText("не найдены изображения!", Theme::get()->color("red")));
        RuntimeData::get()->statusPopupTriggerSet(true);
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
        qInfo() << "[DISK] Error opening the image file for converting to raw bytes data";

        return QByteArray();
    }
}
