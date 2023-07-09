#include "CMapImage.h"

namespace QuasarSDK::Map
{
  MapImage::MapImage()
    : FGSMapObject()
    , m_azimuth(0)
    , m_offset(QPointF(0, 0))
    , m_rectSize(QSizeF(0, 0))
  {}

  MapImage::MapImage(const QGeoCoordinate& coord, const QPointF& offset, const QSizeF& rect,
                     float angle, float dx_ratio, const QPointF& origin_point)
    : FGSMapObject(coord, dx_ratio, origin_point)
    , m_azimuth(angle)
    , m_offset(offset)
    , m_rectSize(rect)
  {}

  float MapImage::azimuth() const { return m_azimuth; }
  void MapImage::setAzimuth(float deg) { m_azimuth = deg; }

  QPointF MapImage::offset() const { return m_offset; }
  void MapImage::setOffset(const QPointF& point) { m_offset = point; }

  QSizeF MapImage::rectSize() const { return m_rectSize; }
  void MapImage::setRectSize(const QSizeF& size) { m_rectSize = size; }
} // QuasarSDK::Map