#pragma once

#include <LPVL/Abstract/INameable>
#include <LPVL/Abstract/IColorable>
#include <QuasarSDK/Map/ScreenMapObject>

namespace Map
{
  class GeoMarker : public QuasarSDK::Map::ScreenMapObject,
                    public LPVL::INameable,
                    public LPVL::IColorable
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
