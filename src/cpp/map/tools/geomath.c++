#include "geomath.h++"
#include <cmath>

namespace Map
{
    namespace math
    {
        QPair<qreal, qreal> geoCoordToWebMercator(QGeoCoordinate _point, quint8 _zoom)
        {
            return{(1.0 - asinh(tan(_point.latitude() * M_PI / 180.0)) / M_PI) / 2.0 * (1 << _zoom),
                    (_point.longitude() + 180.0) / 360.0 * (1 << _zoom)};
        }
    } // namespace math;
} // namespace Map;
