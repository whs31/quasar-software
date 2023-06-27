#include "sdkgeomath.h"
#include <cmath>
#include <QtCore/QPointF>
#include <QtPositioning/QGeoCoordinate>

constexpr const double MAP_SCALE_RATIO = 156'543.03392;

double logf(double base, double value) noexcept { return (std::log(value) / std::log(base)); } // todo replace it with lpvl analogue

namespace SDK::Cartography
{
  double mqi_zoom_level(double latitude_at, float meters_per_pixel) noexcept
  {
    if(not meters_per_pixel)
      return logf(2, MAP_SCALE_RATIO * cos(latitude_at * M_PI / 180));
    return logf(2, MAP_SCALE_RATIO * cos(latitude_at * M_PI / 180) / meters_per_pixel);
  }

  QPointF geocoordinate_to_webmercator(const QGeoCoordinate& coordinate, uint8_t zoom_level) noexcept
  {
    return QPointF((1.0 - asinh(tan(coordinate.latitude() * M_PI / 180.0)) / M_PI) / 2.0 * (1 << zoom_level),
                   (coordinate.longitude() + 180.0) / 360.0 * (1 << zoom_level));
  }
} // SDK::Cartography