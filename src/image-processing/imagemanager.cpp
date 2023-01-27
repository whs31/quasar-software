#include "imagemanager.h"

ImageManager *ImageManager::_instance = nullptr;
QVector<Image *> ImageManager::imageList = {};
ImageManager::ImageManager(QObject *parent)
    : QObject{parent}
{
}

ImageManager *ImageManager::get(QObject *parent)
{
    if (_instance != NULL)
        return _instance;
    _instance = new ImageManager(parent);
    return _instance;
}

// returns true if occurence is found within an image vector
bool ImageManager::checkForOccurence(QString filename)
{
    for (Image *i : imageList)
        if (i->cachedJPEGfilename == filename)
            return true;
    return false;
}

void ImageManager::newImage(QString filenamePath, QByteArray data)
{
    Image *image = new Image(get(), data, filenamePath, ImageMode::GeometricAlphaMask, 
    SConfig::get()->getAngleCorrection(), SConfig::get()->getGlobalRadians(),
    SConfig::get()->getThetaAzimuthCorrection(), SConfig::get()->getUseDriftAngle());
    image->index = imageList.length();

    if (!image->isValid())
    {
        delete image;
        Debug::Log("!![IMGMANAGER] Image discarded due to decoding or another error");
        return;
    }

    // save thread from disktools

    // append to vector when all functions which changing image is called
    imageList.append(image);
    RuntimeData::get()->setTotalImageCount(imageList.length());
    Debug::Log("[IMGMANAGER] Image displayed");
    LinkerQML::addModel(*image);
    LinkerQML::panImage();
    // any logging only after it
}

bool ImageManager::removeImage(qint32 index)
{
    QMessageBox box;
    box.setWindowTitle("Удаление РЛИ");
    box.setIcon(QMessageBox::Information);
    box.setText("Вы уверены, что хотите удалить выбранное изображение с карты?");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Yes); // maybe cancel(r)
    int ret = box.exec();                   // не ставить шорт, иначе будет выход за границы буфера (енумы qt имеют неадекватные значения)
    switch (ret)
    {
    case QMessageBox::Yes:
        imageList.remove(index);
        RuntimeData::get()->setTotalImageCount(imageList.length());
        Debug::Log("[IMGMANAGER] Image " + QString::number(index) + " removed from map. List now contains = " + QString::number(imageList.length()));
        return true;
        break;
    case QMessageBox::Cancel:
        return false;
        break;
    default:
        return false;
        break;
    }
}

void ImageManager::clearAll(void)
{
    imageList.clear();
    RuntimeData::get()->setTotalImageCount(imageList.length());
}
