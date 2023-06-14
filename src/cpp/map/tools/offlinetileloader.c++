#include "offlinetileloader.h"
#include <cmath>
#include <stdexcept>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
//#include <QtCore/QtMath>
#include <QtCore/QDebug>
#include <QtGui/QPolygonF>
#include <QtNetwork/QNetworkReply>
#include <QtPositioning/QGeoPolygon>
#include <QtPositioning/QGeoRectangle>
#include "config/paths.h"

namespace Map
{

constexpr static const uint8_t MAX_ALLOWED_PARALLEL = 4;

uint32_t longitudeToTileX(double longitude, uint8_t zoom)
{
    return (longitude + 180.0) / 360.0 * (1 << zoom);
}

uint32_t latitudeToTileY(double latitude, uint8_t zoom)
{
    return (1.0 - asinh(tan(latitude * M_PI / 180.0)) / M_PI) / 2.0 * (1 << zoom);
}

double tileXToLongitude(uint32_t x, uint8_t zoom)
{
    return x / qreal(1 << zoom) * 360.0 - 180;
}

double tileYToLatitude(uint32_t y, uint8_t zoom)
{
    double n = M_PI *(1 - 2.0 * y / double(1 << zoom));
    return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

OfflineTileLoader::OfflineTileLoader(QObject* parent)
    : QObject{parent}
    , m_netaccs(new QNetworkAccessManager(this))
    , m_totalTiles(0)
    , m_loadedTiles(0)
    , m_parallelLoadedCount(0)
    , m_serverUrl("https://mt.google.com/vt/lyrs=y&hl=ru&z=%1&x=%2&y=%3")
    , m_storagePath(Config::Paths::offlineTiles())
{
    connect(m_netaccs, &QNetworkAccessManager::finished, [this](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError)
        {
            QDir tilePath(m_storagePath + reply->property("filePath").toString());
            if(not tilePath.exists())
                tilePath.mkpath(".");

            QFile tileFile(tilePath.filePath(reply->property("fileName").toString()));
            tileFile.open(QIODevice::WriteOnly);
            tileFile.write(reply->readAll());
            tileFile.close();
        }

        reply->deleteLater();
        m_parallelLoadedCount--;
        m_loadedTiles++;

        emit progress(m_loadedTiles * 100 / m_totalTiles);

        if(m_tilesQueue.size())
            this->processDownload();

        if(m_totalTiles == m_loadedTiles)
        {
            m_totalTiles = 0;
            m_loadedTiles = 0;
        }
    });

}

void OfflineTileLoader::download(uint8_t zoom, uint32_t x, uint32_t y)
{
    m_tilesQueue.enqueue(TileItem(zoom, x, y));
    m_totalTiles++;

    if(m_parallelLoadedCount < MAX_ALLOWED_PARALLEL)
        this->processDownload();
}

void OfflineTileLoader::download(const QGeoPolygon& polygon, int maximum_zoom)
{
    if(maximum_zoom > 20 or maximum_zoom < 0)
        throw std::invalid_argument("Maximum zoom must be in range [0 - 20]");

    QGeoRectangle rectangle = polygon.boundingGeoRectangle();
    double minLatitude = rectangle.bottomLeft().latitude();
    double maxLatitude = rectangle.topRight().latitude();
    double minLongitude = rectangle.bottomLeft().longitude();
    double maxLongitude = rectangle.topRight().longitude();

    if(minLongitude > maxLongitude)
    {
        minLongitude = rectangle.topRight().longitude();
        maxLongitude = rectangle.bottomLeft().longitude();
    }

    QPolygonF polygon2;
    for(size_t index = 0; index < polygon.size(); index++)
    {
        QGeoCoordinate point = polygon.coordinateAt(index);
        polygon2.append(QPointF(point.longitude(), point.latitude()));
    }

    for(uint8_t zoom = 0; zoom <= maximum_zoom; zoom++)
    {
        uint32_t minX = longitudeToTileX(minLongitude, zoom);
        uint32_t maxX = longitudeToTileX(maxLongitude, zoom);
        uint32_t minY = latitudeToTileY(maxLatitude, zoom);
        uint32_t maxY = latitudeToTileY(minLatitude, zoom);

        for(uint32_t x = minX; x <= maxX; x++)
        {
            for(uint32_t y = minY; y <= maxY; y++)
            {
                double x0 = tileXToLongitude(x, zoom);
                double y0 = tileYToLatitude(y, zoom);
                double x1 = tileXToLongitude(x + 1, zoom);
                double y1 = tileYToLatitude(y + 1, zoom);

                if(polygon2.intersects(QPolygonF(QRectF(QPointF(x0, y0), QPointF(x1, y1)))))
                    this->download(zoom, x, y);
            }
        }
    }
}

void OfflineTileLoader::setServerUrl(const QString& url) { m_serverUrl = url; }
void OfflineTileLoader::setStoragePath(const QString& path) { m_storagePath = path; }

QByteArray OfflineTileLoader::tile(uint8_t zoom, uint32_t x, uint32_t y)
{
    QByteArray ret;
    QFile tileFile(m_storagePath + QString("/%1/%2/%3").arg(zoom).arg(x).arg(y));
    if(tileFile.exists())
    {
        tileFile.open(QIODevice::ReadOnly);
        ret = tileFile.readAll();
        tileFile.close();
    }

    return ret;
}

void OfflineTileLoader::processDownload()
{
    TileItem tileItem = m_tilesQueue.dequeue();
    QNetworkReply* reply = m_netaccs->get(QNetworkRequest(m_serverUrl.arg(tileItem.zoom).arg(tileItem.x).arg(tileItem.y)));
    reply->setProperty("filePath", QString("/%1/%2").arg(tileItem.zoom).arg(tileItem.x));
    reply->setProperty("fileName", QString("%1").arg(tileItem.y));

    m_parallelLoadedCount++;
}

} // Map
