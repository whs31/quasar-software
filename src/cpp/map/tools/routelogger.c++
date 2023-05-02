#include "routelogger.h++"
#include "config/paths.h++"
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#include <QtCore/QTextStream>
#include <QtPositioning/QGeoCoordinate>

using namespace Map;

RouteLogger::RouteLogger(QObject* parent)
    : QObject{parent}
{
    QDir route_logs_dir(Config::Paths::logs() + "/route");
    if(not route_logs_dir.exists())
        route_logs_dir.mkpath(Config::Paths::logs() + "/route");
}

void RouteLogger::createLog(const QString& log_name)
{
    QString name = log_name;
    if(log_name.isEmpty())
        name = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");

    QString filename = Config::Paths::logs() + "/route/routetrack-" + name + "." + format;

    qDebug().noquote() << "[ROUTELOG] Created new route log as" << filename;

//    if(current_file)
//        delete current_file;

    current_file = new QFile(filename);
    current_file->open(QIODevice::WriteOnly);
    QTextStream stream(current_file);
    stream <<   "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>        \n" <<
                "   <gpx version=\"1.1\"><metadata></metadata>      \n" <<
                        "\t<trk>                                    \n" <<
                            "\t\t<trkseg>                           \n";
    current_file->close();
}

void RouteLogger::setFormat(const QString& format)
{
    this->format = format;
}

void RouteLogger::append(const QGeoCoordinate& point, float speed, int satellites)
{
    if(not current_file)
        return;
    current_file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream stream(current_file);
    stream << "\n\t\t\t<trkpt lat=\"" << QString::number(point.latitude(), 'f', 6) << "\" lon=\""
           << QString::number(point.longitude(), 'f', 6) << "\">\n"
           << "\t\t\t\t<ele>" << QString::number(point.altitude(), 'f', 6) << "</ele>\n"
           << "\t\t\t\t<time>" << QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ssZ") << "</time>\n"
           << "\t\t\t\t<speed>" << QString::number(speed, 'f', 6) << "</speed>\n"
           << "\t\t\t\t<direction>0</direction>\n\t\t\t\t<fix>3</fix>\n"
           << "\t\t\t\t<sats>" << QString::number(satellites) << "</sats>\n\t\t\t</trkpt>";
    current_file->close();
}

void RouteLogger::commit()
{
    current_file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream stream(current_file);
    stream << "\n\t\t</trkseg>\n" <<
              "\t</trk>\n"        <<
              "</gpx>";
    current_file->close();
}

