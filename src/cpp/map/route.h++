#pragma once

#include <definitions.h++>
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

        QVariantList m_fullRoute;
        QVariantList m_recentRoute;

        RouteLogger* logger;

        public:
            explicit Route(QObject* parent = nullptr);
            virtual ~Route();

            __qml void append(const QGeoCoordinate& coord, float speed = -1, int satellites = -1);
            __qml void clear();


            QVariantList fullRoute() const;
            void setFullRoute(const QVariantList& other);

            QVariantList recentRoute() const;
            void setRecentRoute(const QVariantList& other);

        signals:
            __signal fullRouteChanged();
            __signal recentRouteChanged();
    };
} // namespace Map

