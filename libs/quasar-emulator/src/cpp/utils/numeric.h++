#pragma once
#define __global static inline
#define __qml Q_INVOKABLE
#define __signal void

#include <QtCore/QObject>
#include <QtCore/QPointF>

class QGeoCoordinate;

namespace Utilities
{
    class Numeric : public QObject
    {
        Q_OBJECT

        constexpr __global double MAP_SCALE_RATIO = 156'543.03392;
        constexpr __global double KILOMETERS_IN_DEGREE = 111.111;
        constexpr __global double INVERSE_MAP_SCALE_RATIO = 28.8659;

        public:
            Numeric(QObject* parent = nullptr);

            __qml static float degreesToKilometers(double degrees) noexcept(true);
            __qml static float degreesToMeters(double degrees) noexcept(true);
            __qml static double metersToDegrees(float meters) noexcept(true);

            __qml static float mercatorZoomLevel(double latitude, float meters_per_px = 0) noexcept(true);
            __qml static double zoomLevelToRatio(float zoom_level, double latitude = 0) noexcept(true);

            __qml static float degreesToRadians(float degrees) noexcept(true);
            __qml static float radiansToDegrees(float radians) noexcept(true);

            __qml static QPointF geoCoordToWebMercator(const QGeoCoordinate& point, uint8_t zoom = 19) noexcept(true);
    };
} // namespace Utilities;
