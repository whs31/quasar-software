#include "routelogger.h"
#include "disk/cachemanager.h"

#include <QTextStream>

RouteLogger::RouteLogger(QObject *parent)
    : QObject{parent}
{}

void RouteLogger::newRoute(QString name)
{
    m_current_filename = CacheManager::getTcpDowloaderCache() + "/routetrack-" + name + ".txt";
    qDebug() << "[ROUTELOG] Created new route log in " << m_current_filename;

    route = new QFile(m_current_filename);
    route->open(QIODevice::WriteOnly);
    QTextStream stream(route);
    stream << "Route log start \n ============================================== \n";
    route->close();
}

void RouteLogger::addPoint(QGeoCoordinate point)
{
    route->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream stream(route);
    stream << "LAT: " << point.latitude()
           << " LON: " << point.longitude()
           << " ALT: " << point.altitude() << "\n";
    route->close();
}
