#pragma once

#include <QtCore/QObject>
#include <QtCore/QtGlobal>
#include <QtCore/QtMath>
#include <QtPositioning/QGeoPath>

namespace Map
{
    class Orthodrom
    {
        double A1;
        double A2;

        QGeoCoordinate _coord1;
        QGeoCoordinate _coord2;

        QVariantList orthodromPath;

        public:
            Orthodrom(const QGeoCoordinate &coord1, const QGeoCoordinate &coord2);
            explicit Orthodrom();

            void setCoord1(const QGeoCoordinate &coord1);
            void setCoord2(const QGeoCoordinate &coord2);
            QVariantList getPoints();
            qreal getLatitude(qreal longitude);

        private:
            void setPoints(quint16 spacing);
            qreal getDistance();
    };
} // namespace Map;

