#include "imagemanager.h"

ImageManager *ImageManager::_instance = nullptr;
ImageManager::ImageManager(QObject *parent)
    : QObject{parent}
{  }

ImageManager *ImageManager::initialize(QObject *parent)
{
    if (_instance != NULL)
        return _instance;
    _instance = new ImageManager(parent);
    return _instance;
}

void ImageManager::newImage(QString filename, QByteArray data)
{
    TImage* image = new TImage(initialize());
    image->cachedJPEGfilename = filename;

    //save thread from disktools
    
    ImageProcess imageProcess;
    //imageProcess.decode(data, *image);
}
