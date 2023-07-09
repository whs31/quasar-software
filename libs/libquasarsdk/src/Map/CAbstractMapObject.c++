#include "CAbstractMapObject.h"
#include <algorithm>

namespace QuasarSDK::Map
{
  QGeoCoordinate AbstractMapItem::coordinate() const { return m_coordinate; }
  void AbstractMapItem::setCoordinate(const QGeoCoordinate& coord) { m_coordinate = coord; }
  void AbstractMapItem::setCoordinate(double latitude, double longitude) { m_coordinate = QGeoCoordinate(latitude, longitude); }

  QPointF AbstractMapItem::origin() const { return m_origin; }
  void AbstractMapItem::setOrigin(const QPointF& point) { m_origin = point; }
  void AbstractMapItem::setOrigin(float x, float y) { m_origin = QPointF(x, y); }

  float AbstractMapItem::opacity() const { return m_opacity; }
  void AbstractMapItem::setOpacity(float val) { m_opacity = std::clamp<float>(val, 0, 1); }

  bool AbstractMapItem::isVisible() const { return m_visible; }
  void AbstractMapItem::setVisible(bool state) { m_visible = state; }

  AbstractMapItem::AbstractMapItem()
    : m_coordinate(QGeoCoordinate(0, 0))
    , m_origin(QPointF(0, 0))
    , m_opacity(1)
    , m_visible(true)
    , m_zoomLevel(0)
  {}

  AbstractMapItem::AbstractMapItem(const QGeoCoordinate& coord, const QPointF& origin_point, float opacity_value,
                                   bool visibility)
    : m_coordinate(coord)
    , m_origin(origin_point)
    , m_opacity(opacity_value)
    , m_visible(visibility)
    , m_zoomLevel(0)
  {}
} // QuasarSDK::Map