#include "CAbstractMapObject.h"
#include <algorithm>

namespace QuasarSDK::Map
{
  QGeoCoordinate AbstractMapObject::coordinate() const { return m_coordinate; }
  void AbstractMapObject::setCoordinate(const QGeoCoordinate& coord) { m_coordinate = coord; }
  void AbstractMapObject::setCoordinate(double latitude, double longitude) { m_coordinate = QGeoCoordinate(latitude, longitude); }

  QPointF AbstractMapObject::origin() const { return m_origin; }
  void AbstractMapObject::setOrigin(const QPointF& point) { m_origin = point; }
  void AbstractMapObject::setOrigin(float x, float y) { m_origin = QPointF(x, y); }

  float AbstractMapObject::opacity() const { return m_opacity; }
  void AbstractMapObject::setOpacity(float val) { m_opacity = std::clamp<float>(val, 0, 1); }

  bool AbstractMapObject::isVisible() const { return m_visible; }
  void AbstractMapObject::setVisible(bool state) { m_visible = state; }

  AbstractMapObject::AbstractMapObject()
    : m_coordinate(QGeoCoordinate(0, 0))
    , m_origin(QPointF(0, 0))
    , m_opacity(1)
    , m_visible(true)
    , m_zoomLevel(0)
  {}

  AbstractMapObject::AbstractMapObject(const QGeoCoordinate& coord, const QPointF& origin_point, float opacity_value,
                                       bool visibility)
    : m_coordinate(coord)
    , m_origin(origin_point)
    , m_opacity(opacity_value)
    , m_visible(visibility)
    , m_zoomLevel(0)
  {}
} // QuasarSDK::Map