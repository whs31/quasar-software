#pragma once

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

      constexpr static int RECENT_ROUTE_SIZE = 1000;

    public:
      explicit Route(QObject* parent = nullptr);
      ~Route() override;

      Q_INVOKABLE void append(const QGeoCoordinate& coord, float speed = -1, int satellites = -1);
      Q_INVOKABLE void clear();

      [[nodiscard]] QVariantList fullRoute() const; void setFullRoute(const QVariantList&);
      [[nodiscard]] QVariantList recentRoute() const; void setRecentRoute(const QVariantList&);

    signals:
      void fullRouteChanged();
      void recentRouteChanged();

    private:
      QVariantList m_fullRoute;
      QVariantList m_recentRoute;

      RouteLogger* logger;
  };
} // namespace Map

