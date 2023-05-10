#include "imageprocessing.h++"
#include "map/imagemodel.h++"

#include <QtCore/QDebug>

using namespace Processing;

DECLARE_SINGLETON_IMPL(ImageProcessing)

ImageProcessing::ImageProcessing(QObject* parent)
    : QObject{parent}
    , m_model(new Map::ImageModel(this))
{

}

Map::ImageModel* ImageProcessing::model() const
{
    return this->m_model;
}

void ImageProcessing::processImage(const QString& filename)
{
    qDebug() << "[PROCESSING] Received image to process" << filename;
}

