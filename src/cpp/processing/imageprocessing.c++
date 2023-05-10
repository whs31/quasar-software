#include "imageprocessing.h++"
#include "map/imagemodel.h++"

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

