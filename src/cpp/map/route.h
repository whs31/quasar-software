#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariantList>
#include <ccl/ccl_global.h>

class QGeoCoordinate;

namespace Map
{
    class RouteLogger;

    class Route : public QObject
    {
        Q_OBJECT
        PROPERTY_DEF(QVariantList, fullRoute, setFullRoute, m_fullRoute)
        PROPERTY_DEF(QVariantList, recentRoute, setRecentRoute, m_recentRoute)

        constexpr static int RECENT_ROUTE_SIZE = 1000;

        public:
            explicit Route(QObject* parent = nullptr);
            virtual ~Route();

            Q_INVOKABLE void append(const QGeoCoordinate& coord, float speed = -1, int satellites = -1);
            Q_INVOKABLE void clear();

            signals:
                void fullRouteChanged();
                void recentRouteChanged();

        private:
            QVariantList m_fullRoute;
            QVariantList m_recentRoute;

            RouteLogger* logger;
    };
} // namespace Map

