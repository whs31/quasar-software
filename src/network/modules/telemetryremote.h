#ifndef TELEMETRYREMOTE_H
#define TELEMETRYREMOTE_H

#include <QObject>

class TelemetryRemote : public QObject
{
    Q_OBJECT
public:
    explicit TelemetryRemote(QObject *parent = nullptr);

signals:

};

#endif // TELEMETRYREMOTE_H
