#pragma once

#include <definitions.h++>
#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>
#include "network/telemetry/telemetrydatagram.h++"

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

        struct LocalData
        {
            double latitude = 60;
            double longitude = 30;
            float altitude = 100;
            float velocity = 50;
            float velocity_vertical = 1;
            float pitch = 90;
            float roll = 0;
            float yaw;
            float course = yaw;
            uint64_t time = 0;
        } local_data;

        public:
            TelemetrySocketEmulator(QObject* parent = nullptr);
            virtual ~TelemetrySocketEmulator();

            void startTelemetryServer(const QString& address = "127.0.0.1:9955");
            void stop();

        private:
            private slots:
                void read();
                void sendTelemetry();
                Network::TelemetryDatagram generateTelemetry();
    };
} // namespace Debug;
