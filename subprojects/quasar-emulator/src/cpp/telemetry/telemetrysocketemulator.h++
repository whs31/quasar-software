#pragma once
#define __global static inline
#define __qml Q_INVOKABLE
#define __signal void


#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>
#include "telemetrydatagram.h++"
#include "telemetryemulator.h++"

class QUdpSocket;
class QTimer;

namespace Debug
{
    class TelemetrySocketEmulator : public QObject
    {
        Q_OBJECT

        constexpr __global uint32_t MARKER = 0x55BB55BB;

        QUdpSocket* socket;
        QTimer* timer;
        QTimer* stopTimer;
        QHostAddress m_hostaddress;
        uint16_t m_port;
        TelemetryEmulator* emulator;

        public:
            TelemetrySocketEmulator(TelemetryEmulator* emulator, QObject* parent = nullptr);
            virtual ~TelemetrySocketEmulator();

            __qml void startTelemetryServer(const QString& address = "127.0.0.1:9955");
            __qml void stop();

        private:
            private slots:
                void read();
                void sendTelemetry();
                TelemetryDatagram generateTelemetry();
    };
} // namespace Debug;
