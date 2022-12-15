#include "imagemanager.h"

ImageManager *ImageManager::_instance = nullptr;
ImageManager::ImageManager(QObject *parent)
    : QObject{parent}
{
}

ImageManager *ImageManager::initialize(QObject *parent)
{
    if (_instance != NULL)
        return _instance;
    _instance = new ImageManager(parent);
    return _instance;
}

void ImageManager::newImage(QString filename, QByteArray data)
{
    if (!checkVector(filename))
    {
        TImage *image = new TImage(initialize());
        image->cachedJPEGfilename = filename;

        // save thread from disktools

        ImageProcess imageProcess;
        imageProcess.decode(data, *image);
        qCritical() << image->meta.angle;
    } else {
        Debug::Log("[IMGMANAGER] Image " + filename + " already fetched, skipping");
    }
}

bool ImageManager::checkVector(QString filename)
{
    // check here
    return 0;
}