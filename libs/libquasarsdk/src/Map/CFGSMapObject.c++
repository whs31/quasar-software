#include "CFGSMapObject.h"
#include <cmath>
#include "Networking/FCommon.h"

constexpr const double MAP_SCALE_RATIO = 156'543.03392;

namespace QuasarSDK::Map
{
  float FGSMapObject::zoomLevel() const { return calculate_mercator_zoom_level(coordinate().latitude(), ratio()); }

  float FGSMapObject::ratio() const { return m_ratio; }
  void FGSMapObject::setRatio(float r) { m_ratio = r; }

  float FGSMapObject::calculate_mercator_zoom_level(double lat, float meters_per_px) noexcept
  {
    if(meters_per_px == 0)
      return static_cast<float>(Utils::log(2, MAP_SCALE_RATIO * cos(lat * M_PI / 180)));
    return static_cast<float>(Utils::log(2, MAP_SCALE_RATIO * cos(lat * M_PI / 180) / meters_per_px));
  }
} // QuasarSDK::Map