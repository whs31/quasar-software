#pragma once

#include <definitions.h++>
#include "network/abstractudpsocket.h++"

class QTimer;

namespace Network
{
    class Telemetry;

    class TelemetrySocket : public AbstractUDPSocket
    {
        Q_OBJECT
        Q_PROPERTY(float frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)

        constexpr __global uint32_t MARKER = 0x55bb55bb;
        constexpr __global uint32_t RECV_MARKER_LITTLE = 0xaa55aa55;
        constexpr __global uint32_t RECV_MARKER_BIG = 0x55aa55aa;
        constexpr __global bool CRC_CHECK = false;

        QTimer* m_updateTimer;
        float m_frequency = 0.2;
        Telemetry* output;


        public:
            TelemetrySocket(QObject* parent = nullptr, Telemetry* output = nullptr);

            void start(const QString& address);
            void stop();

            float frequency() const;
            void setFrequency(float other);

            signals:
                __signal frequencyChanged();
                __signal ping();

        private:
            private slots:
                void processTelemetry(QByteArray data);
                void requestTelemetry();
    };
} // namespace Network
