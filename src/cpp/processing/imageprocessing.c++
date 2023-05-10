#include "imageprocessing.h++"
#include "map/imagemodel.h++"
#include "config/paths.h++"

#include <QtCore/QDebug>
#include <QtCore/QFile>

using namespace Processing;

DECLARE_SINGLETON_IMPL(ImageProcessing)

ImageProcessing::ImageProcessing(QObject* parent)
    : QObject{parent}
    , m_model(new Map::ImageModel(this))
{

}

void ImageProcessing::asyncProcess(const QString& filename)
{
    Map::Image image;

    image.filename = filename;
    image.path.first = Config::Paths::imageCache() + "/lod0/" + filename;
    QByteArray data = fileToByteArray(image.path.first);

}

QByteArray ImageProcessing::fileToByteArray(const QString& path)
{
    QFile file(path);
    if(not file.open(QIODevice::ReadOnly))
    {
        qCritical().noquote() << "[PROCESSING] Error opening file |" << path << "| for converting to raw bytes data";
        return QByteArray();
    }

    return file.readAll();
}

Map::ImageModel* ImageProcessing::model() const
{
    return this->m_model;
}

void ImageProcessing::processImage(const QString& filename)
{
    qDebug() << "[PROCESSING] Received image to process" << filename;

    this->processImage(filename);
}

