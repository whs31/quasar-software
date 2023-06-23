#pragma once

#include <QtCore/QObject>
#include <QtCore/QQueue>

class QGeoPolygon;
class QNetworkAccessManager;

namespace Map
{
  class OfflineTileLoader : public QObject
  {
    Q_OBJECT

    public:
      static OfflineTileLoader* get();

      void download(uint8_t zoom, uint32_t x, uint32_t y);
      void download(const QGeoPolygon& polygon, int maximum_zoom = 18);
      Q_INVOKABLE void download(const QVariantList& list, int maximum_zoom = 18);
      Q_INVOKABLE int estimateTileCount(const QVariantList& list, int maximum_zoom = 18) noexcept;

      void setServerUrl(const QString& url);
      void setStoragePath(const QString& path);

      QByteArray tile(uint8_t zoom, uint32_t x, uint32_t y);

    signals:
      void progress(int percent);

    private:
      explicit OfflineTileLoader(QObject* parent = nullptr);
      OfflineTileLoader(const OfflineTileLoader&);
      OfflineTileLoader& operator=(const OfflineTileLoader&);

      void processDownload();

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
  };
} // Map5
