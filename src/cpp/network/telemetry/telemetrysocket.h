#pragma once

#include "network/abstractudpsocket.h"

class QTimer;

namespace Network
{
    class Telemetry;

    class TelemetrySocket : public AbstractUDPSocket
    {
        Q_OBJECT
        Q_PROPERTY(float frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)

        constexpr static uint32_t MARKER = 0x55bb55bb;
        constexpr static uint32_t RECV_MARKER_LITTLE = 0xaa55aa55;
        constexpr static uint32_t RECV_MARKER_BIG = 0x55aa55aa;
        constexpr static bool CRC_CHECK = false;

        public:
            TelemetrySocket(QObject* parent = nullptr, Telemetry* output = nullptr);

            void start(const QString& address);
            void stop();

            float frequency() const; void setFrequency(float);

            signals:
                void frequencyChanged();
                void ping();

        private:
            private slots:
                void processTelemetry(QByteArray data);
                void requestTelemetry();

        private:
            QTimer* m_updateTimer;
            float m_frequency = 0.2;
            Telemetry* output;
    };
} // namespace Network
