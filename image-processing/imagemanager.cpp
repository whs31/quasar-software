#include "imagemanager.h"

ImageManager *ImageManager::_instance = nullptr;
QVector<TImage*> ImageManager::imageList = {};
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

void ImageManager::newImage(QString filenamePath, QByteArray data)
{
    QStringList _cutFilename;
    _cutFilename = filenamePath.split("/");
    QString filename = _cutFilename.last();
    if (!checkVector(filename))
    {
        TImage *image = new TImage(initialize());
        image->index = imageList.length();
        image->cachedJPEGfilename = filenamePath;

        // save thread from disktools

        ImageProcess imageProcess;
        if(!imageProcess.decode(data, *image))
        {
            delete image;
            Debug::Log("!![IMGMANAGER] Image discarded due to decoding error");
            return;
        }
        imageProcess.assignUIStrings(*image, filename);
        image->image = imageProcess.dataToImage(data, ImageMode::GeometricAlphaMask, *image);
        image->base64 = imageProcess.imageToBase64(image->image);

        //append to vector when all functions which changing image is called 
        imageList.append(image);     
        LinkerQML::addModel(*image);
        //any logging only after it
    } else {
        Debug::Log("[IMGMANAGER] Image " + filenamePath + " already fetched, skipping");
    }
}

void ImageManager::removeImage(qint32 index)
{
    imageList.remove(index);
    Debug::Log("[IMGMANAGER] Image " + QString::number(index) + " removed from map. List now contains = " + QString::number(imageList.length()));
}

bool ImageManager::checkVector(QString filename)
{
    // check here
    return 0;
}