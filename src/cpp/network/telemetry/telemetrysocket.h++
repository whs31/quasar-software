#pragma once

#include <QtNetwork/QUdpSocket>

class TelemetrySocket : public QUdpSocket
{
    Q_OBJECT

    public:
        TelemetrySocket();
};
