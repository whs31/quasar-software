#pragma once

#include "network/abstractudpsocket.h++"

class QTimer;

namespace Network
{
    class Telemetry;

    class TelemetrySocket : public AbstractUDPSocket
    {
        Q_OBJECT
        Q_PROPERTY(float frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)

        constexpr static const char* REQUEST_KEY = "$JSON";

        QTimer* m_updateTimer;
        float m_frequency = 0.2;
        Telemetry* m_output;


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
