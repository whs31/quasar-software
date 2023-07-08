#include "CAbstractMapItem.h"
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
} // QuasarSDK::Map