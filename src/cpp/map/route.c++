#include "route.h++"
#include "tools/routelogger.h++"
#include <QtCore/QFile>
#include <QtPositioning/QGeoCoordinate>

using namespace Map;

Route::Route(QObject* parent)
    : QObject{parent}
    , logger(new RouteLogger(this))
{

}

Route::~Route()
{
    logger->commit();
}

void Route::append(const QGeoCoordinate& coord, float speed, int satellites)
{
    static bool created_log = false;
    if(m_fullRoute.empty() and not created_log) {
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
    setFullRoute(QVariantList());
    setRecentRoute(QVariantList());
    logger->commit();
}
