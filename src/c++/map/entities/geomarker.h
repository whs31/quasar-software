#pragma once

#include <Abstract/INameable>
#include <Abstract/IColorable>
#include <QuasarSDK/Map/ScreenMapObject>

namespace Map
{
  class GeoMarker : public QuasarSDK::Map::ScreenMapObject,
                    public INameable,
                    public IColorable
  {
    public:
      GeoMarker();
      GeoMarker(const QGeoCoordinate& coord, const QString& name, const QColor& color = QColor("white"),
                QString icon_path = "qrc:/map/markers/default.png");

      [[nodiscard]] QString icon() const;
      void setIcon(const QString& new_icon);

    protected:
      QString m_icon;
  };
} // Map
