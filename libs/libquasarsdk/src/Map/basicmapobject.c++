#include "basicmapobject.h"
#include <algorithm>

namespace QuasarSDK::Map
{
  QGeoCoordinate BasicMapObject::coordinate() const { return m_coordinate; }
  void BasicMapObject::setCoordinate(const QGeoCoordinate& coord) { m_coordinate = coord; }
  void BasicMapObject::setCoordinate(double latitude, double longitude) { m_coordinate = QGeoCoordinate(latitude, longitude); }

  QPointF BasicMapObject::origin() const { return m_origin; }
  void BasicMapObject::setOrigin(const QPointF& point) { m_origin = point; }
  void BasicMapObject::setOrigin(float x, float y) { m_origin = QPointF(x, y); }

  float BasicMapObject::opacity() const { return m_opacity; }
  void BasicMapObject::setOpacity(float val) { m_opacity = std::clamp<float>(val, 0, 1); }

  bool BasicMapObject::isVisible() const { return m_visible; }
  void BasicMapObject::setVisible(bool state) { m_visible = state; }

  BasicMapObject::BasicMapObject()
    : m_coordinate(QGeoCoordinate(0, 0))
    , m_origin(QPointF(0, 0))
    , m_opacity(1)
    , m_visible(true)
    , m_zoomLevel(0)
  {}

  BasicMapObject::BasicMapObject(const QGeoCoordinate& coord, const QPointF& origin_point, float opacity_value,
                                 bool visibility)
    : m_coordinate(coord)
    , m_origin(origin_point)
    , m_opacity(opacity_value)
    , m_visible(visibility)
    , m_zoomLevel(0)
  {}
} // QuasarSDK::Map