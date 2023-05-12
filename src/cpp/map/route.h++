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
        Q_PROPERTY(QVariantList fullRoute READ fullRoute WRITE setFullRoute NOTIFY fullRouteChanged)
        Q_PROPERTY(QVariantList recentRoute READ recentRoute WRITE setRecentRoute NOTIFY recentRouteChanged)

        constexpr __global int RECENT_ROUTE_SIZE = 1000;

        public:
            explicit Route(QObject* parent = nullptr);
            virtual ~Route();

            __qml void append(const QGeoCoordinate& coord, float speed = -1, int satellites = -1);
            __qml void clear();

            __getter QVariantList fullRoute() const;
            __setter void setFullRoute(const QVariantList& other);

            __getter QVariantList recentRoute() const;
            __setter void setRecentRoute(const QVariantList& other);

            signals:
                __signal fullRouteChanged();
                __signal recentRouteChanged();

        private:
            QVariantList m_fullRoute;
            QVariantList m_recentRoute;

            RouteLogger* logger;
    };
} // namespace Map

