#ifndef TELEMETRYREMOTE_H
#define TELEMETRYREMOTE_H

#include <QObject>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "network/udpremote.h"
#include "misc/debug.h"
#include "map/linkerqml.h"

#include "data/datatelemetry.h"
#include "config/runtimedata.h"

class TelemetryRemote : public QObject
{
    Q_OBJECT
public:
    explicit TelemetryRemote(QObject *parent = nullptr);
    ~TelemetryRemote();

    const qreal TIMEOUT_TIME = 5000; //ms
    const QString REQUEST_TELEMETRY_MARKER = "$JSON";

    void connect(QString ip, quint16 port, qreal frequency);
    void disconnect(void);

signals:
    void timeout();

private:
    UDPRemote *udpRemote = nullptr;
    QTimer* updateTimer = nullptr;
    QTimer* timeoutTimer = nullptr;

    void parseTelemetry(QString data);

    double m_differenceCheck = 0;
    short m_satteliteDifferenceCheck = 0;
    double m_parsedDifferenceCheck = 0;

private slots:
    void receiveTelemetry(QByteArray data);
    void askForTelemetry(void);
    void timeoutSlot(void);
};

#endif // TELEMETRYREMOTE_H
