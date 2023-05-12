#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtCore/QVariantList>

class QGeoCoordinate;

namespace Map
{
    class RouteLogger;

    class Route : public QObject
    {
        Q_OBJECT
        PROPERTY_DEF(QVariantList, fullRoute, setFullRoute, m_fullRoute)
        PROPERTY_DEF(QVariantList, recentRoute, setRecentRoute, m_recentRoute)

        constexpr __global int RECENT_ROUTE_SIZE = 1000;

        public:
            explicit Route(QObject* parent = nullptr);
            virtual ~Route();

            __exposed void append(const QGeoCoordinate& coord, float speed = -1, int satellites = -1);
            __exposed void clear();

            signals:
                __property_signal fullRouteChanged();
                __property_signal recentRouteChanged();

        private:
            QVariantList m_fullRoute;
            QVariantList m_recentRoute;

            RouteLogger* logger;
    };
} // namespace Map

