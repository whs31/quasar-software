#include "route.h"
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtPositioning/QGeoCoordinate>
#include "tools/routelogger.h"

namespace Map
{

  Route::Route(QObject* parent)
    : QObject{parent}, logger(new RouteLogger(this))
  {}

  Route::~Route() { logger->commit(); }

  void Route::append(const QGeoCoordinate& coord, float speed, int satellites)
  {
    static bool created_log = false;
    if(m_fullRoute.empty() and not created_log)
    {
      logger->createLog();
      created_log = true;
    }

    if(logger->current_file)
      logger->append(coord, speed, satellites);

    if(coord.latitude() == 0 or coord.longitude() == 0)
      return;

    m_fullRoute.push_back(QVariant::fromValue(coord));
    emit fullRouteChanged();

    if(m_recentRoute.size() >= RECENT_ROUTE_SIZE)
      m_recentRoute.pop_front();
    m_recentRoute.push_back(QVariant::fromValue(coord));
    emit recentRouteChanged();
  }

  void Route::clear()
  {
    if(fullRoute().empty())
    {
      qWarning() << "[ROUTE] Tried to clear empty track";
      return;
    }

    setFullRoute(QVariantList());
    setRecentRoute(QVariantList());
    logger->commit();
  }

  QVariantList Route::fullRoute() const { return m_fullRoute; }
  void Route::setFullRoute(const QVariantList& other)
  {
    if(m_fullRoute == other)
      return;
    m_fullRoute = other;
    emit fullRouteChanged();
  }

  QVariantList Route::recentRoute() const { return m_recentRoute; }
  void Route::setRecentRoute(const QVariantList& other)
  {
    if(m_recentRoute == other)
      return;
    m_recentRoute = other;
    emit recentRouteChanged();
  }

} // Map