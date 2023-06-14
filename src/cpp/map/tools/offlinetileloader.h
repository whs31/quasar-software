#pragma once

#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <LPVL/Global>

class QGeoPolygon;
class QNetworkAccessManager;

namespace Map
{
    class OfflineTileLoader : public QObject
    {
        Q_OBJECT
        LPVL_DECLARE_SINGLETON(OfflineTileLoader)

        public:
            explicit OfflineTileLoader(QObject* parent = nullptr);

            void download(uint8_t zoom, uint32_t x, uint32_t y);
            void download(const QGeoPolygon& polygon, int maximum_zoom = 18);

            void setServerUrl(const QString& url);
            void setStoragePath(const QString& path);

            QByteArray tile(uint8_t zoom, uint32_t x, uint32_t y);

            signals:
                void progress(int percent);

        private:
            struct TileItem
            {
                TileItem(uint8_t zoom, uint32_t x, uint32_t y)
                    : zoom(zoom)
                    , x(x)
                    , y(y)
                {}

                uint8_t zoom;
                uint32_t x;
                uint32_t y;
            };

            QNetworkAccessManager* m_netaccs;
            uint64_t m_totalTiles;
            uint64_t m_loadedTiles;
            QQueue<TileItem> m_tilesQueue;
            uint8_t m_parallelLoadedCount;
            QString m_serverUrl;
            QString m_storagePath;

            void processDownload();
    };
} // Map5
