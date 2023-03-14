#include "routelogger.h"
#include "disk/cachemanager.h"

#include <QDateTime>
#include <QTextStream>

RouteLogger::RouteLogger(QObject *parent)
    : QObject{parent}
{}

void RouteLogger::newRoute(QString name)
{
    m_current_filename = CacheManager::getTcpDowloaderCache() + "/routetrack-" + name + ".gpx";
    qDebug() << "[ROUTELOG] Created new route log in " << m_current_filename;

    route = new QFile(m_current_filename);
    route->open(QIODevice::WriteOnly);
    QTextStream stream(route);
    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?> \n" <<
              "<gpx version=\"1.1\"><metadata></metadata>\n\t<trk>\n\t\t<trkseg>\n";
    route->close();
}

void RouteLogger::addPoint(QGeoCoordinate point, float speed, int satellites)
{
    route->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream stream(route);
    stream << "\n\t\t\t<trkpt lat=\"" << QString::number(point.latitude(), 'f', 6) << "\" lon=\""
           << QString::number(point.longitude(), 'f', 6) << "\">\n"
           << "\t\t\t\t<ele>" << QString::number(point.altitude(), 'f', 6) << "</ele>\n"
           << "\t\t\t\t<time>" << QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ssZ") << "</time>\n"
           << "\t\t\t\t<speed>" << QString::number(speed, 'f', 6) << "</speed>\n"
           << "\t\t\t\t<direction>0</direction>\n\t\t\t\t<fix>3</fix>\n"
           << "\t\t\t\t<sats>" << QString::number(satellites) << "</sats>\n\t\t\t</trkpt>";
    route->close();
}

void RouteLogger::closeHandle()
{
    route->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream stream(route);
    stream << "\n\t\t</trkseg>\n\t</trk>\n</gpx>";
    route->close();
}
