#ifndef ROUTELOGGER_H
#define ROUTELOGGER_H

#include <QObject>
#include <QGeoCoordinate>

class RouteLogger : public QObject
{
    Q_OBJECT
public:
    explicit RouteLogger(QObject *parent = nullptr);
    Q_INVOKABLE void newRoute(QString name = "unnamed route");
    Q_INVOKABLE void addPoint(QGeoCoordinate point);
    signals:

private:
    QString m_current_filename;

};

#endif // ROUTELOGGER_H
