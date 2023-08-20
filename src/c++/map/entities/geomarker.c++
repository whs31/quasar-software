#include "geomarker.h"
#include <utility>

namespace Map
{
  GeoMarker::GeoMarker()
    : QuasarSDK::Map::ScreenMapObject()
    , LPVL::INameable()
    , LPVL::IColorable()
    , m_icon("qrc:/map/markers/default.png")
  {}

  GeoMarker::GeoMarker(const QGeoCoordinate& coord, const QString& name, const QColor& color, QString icon_path)
    : QuasarSDK::Map::ScreenMapObject(coord)
    , LPVL::INameable(name)
    , LPVL::IColorable(color)
    , m_icon(std::move(icon_path))
  {}

  QString GeoMarker::icon() const { return m_icon; }
  void GeoMarker::setIcon(const QString& new_icon) { m_icon = new_icon; }
} // Map