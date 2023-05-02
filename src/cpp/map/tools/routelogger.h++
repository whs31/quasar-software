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

        QString format = "gpx";

        public:
            QFile* current_file;

            explicit RouteLogger(QObject* parent = nullptr);

            void createLog(const QString& log_name = QString());
            void setFormat(const QString& format);
            void append(const QGeoCoordinate& point, float speed, int satellites);
            void commit();
    };
} // namespace Map

