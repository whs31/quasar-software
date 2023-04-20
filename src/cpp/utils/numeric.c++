#include "numeric.h++"
#include "utils.h++"
#include <cmath>
#include <QtPositioning/QGeoCoordinate>

Utilities::Numeric::Numeric(QObject *parent)
    : QObject{parent}
{

}

namespace Utilities {

float Numeric::degreesToKilometers(double degrees) noexcept(true)
{
    return (degrees * KILOMETERS_IN_DEGREE);
}

float Numeric::degreesToMeters(double degrees) noexcept(true)
{
    return (KILOMETERS_IN_DEGREE * 1'000);
}

double Numeric::metersToDegrees(float meters) noexcept(true)
{
    return (meters / (KILOMETERS_IN_DEGREE * 1'000));
}

float Numeric::mercatorZoomLevel(double latitude, float meters_per_px) noexcept(true)
{
    if(not meters_per_px)
        return Utilities::log(2, MAP_SCALE_RATIO * cos(latitude * M_PI / 180));
    return Utilities::log(2, MAP_SCALE_RATIO * cos(latitude * M_PI / 180) / meters_per_px);
}

double Numeric::zoomLevelToRatio(float zoom_level, double latitude) noexcept(true)
{
    return pow(2, INVERSE_MAP_SCALE_RATIO - zoom_level + Utilities::log(2, cos(M_PI * latitude / 180)));
}

float Numeric::degreesToRadians(float degrees) noexcept(true)
{
    return (degrees * M_PI / 180);
}

float Numeric::radiansToDegrees(float radians) noexcept(true)
{
    return (radians * 180 / M_PI);
}

QPointF Numeric::geoCoordToWebMercator(const QGeoCoordinate& point, quint8 zoom) noexcept(true)
{
    return QPointF((1.0 - asinh(tan(point.latitude() * M_PI / 180.0)) / M_PI) / 2.0 * (1 << zoom),
                   (point.longitude() + 180.0) / 360.0 * (1 << zoom));
}
} // namespace Utilities;
