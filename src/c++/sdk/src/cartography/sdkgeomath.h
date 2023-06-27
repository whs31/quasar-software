#pragma once

#include <cstdint>

class QPointF;
class QGeoCoordinate;

namespace SDK::Cartography
{
  double mqi_zoom_level(double latitude_at, float meters_per_pixel = 1) noexcept;
  QPointF geocoordinate_to_webmercator(const QGeoCoordinate& coordinate, uint8_t zoom_level = 19) noexcept;
} // SDK::Cartography
