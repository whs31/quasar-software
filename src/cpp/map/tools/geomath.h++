#pragma once
#include <QtCore/QPair>
#include <QtPositioning/QGeoCoordinate>

namespace Map
{
    namespace math
    {
        QPair<qreal, qreal> geoCoordToWebMercator(QGeoCoordinate _point, quint8 _zoom = 19);
    } // namespace math;
} // namespace Map;

