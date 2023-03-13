#include "routelogger.h"
#include "disk/cachemanager.h"

#include <QFile>
#include <QTextStream>

RouteLogger::RouteLogger(QObject *parent)
    : QObject{parent}
{}

void RouteLogger::newRoute(QString name)
{
    m_current_filename = CacheManager::getTcpDowloaderCache() + "/" + name + ".txt";
    QFile route(m_current_filename);
    if(route.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&route);
        stream << "Начало записи трека $$";
    }
}

void RouteLogger::addPoint(QGeoCoordinate point)
{
    QFile route(m_current_filename);
    if(route.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&route);
        stream << "LAT: " << point.latitude()
               << " LON: " << point.longitude()
               << " ALT: " << point.altitude();
    }
}
