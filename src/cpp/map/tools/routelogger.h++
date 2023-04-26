#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

class QGeoCoordinate;
class QFile;

namespace Map
{
    class RouteLogger : public QObject
    {
        Q_OBJECT
        QFile* current_file;
        QString format = "gpx";

        public:
            explicit RouteLogger(QObject* parent = nullptr);

            void createLog(const QString& log_name);
            void setFormat(const QString& format);
            void append(const QGeoCoordinate& point, float speed, int satellites);
            void commit();
    };
} // namespace Map

