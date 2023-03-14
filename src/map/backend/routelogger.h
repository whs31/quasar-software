#ifndef ROUTELOGGER_H
#define ROUTELOGGER_H

#include <QObject>
#include <QGeoCoordinate>
#include <QFile>

class RouteLogger : public QObject
{
    Q_OBJECT
public:
    explicit RouteLogger(QObject *parent = nullptr);
    Q_INVOKABLE void newRoute(QString name = "unnamed route");
    Q_INVOKABLE void addPoint(QGeoCoordinate point, float speed, int satellites);
    Q_INVOKABLE void closeHandle();
    signals:

private:
    QString m_current_filename;
    QFile* route;

};

#endif // ROUTELOGGER_H
