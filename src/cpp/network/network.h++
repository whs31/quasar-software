#pragma once

#include <definitions.h++>
#include "telemetry/telemetry.h++"
#include <QtCore/QObject>

class QTimer;

namespace Network
{
    class TelemetrySocket;
    class Network : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
        Q_PROPERTY(float networkDelay READ networkDelay WRITE setNetworkDelay NOTIFY networkDelayChanged)

        static Network* instance;
        QTimer* m_network_delay_timer;

        Telemetry* m_telemetry;
        float m_networkDelay;

        public:
            static Network* get(QObject* parent = nullptr);

            TelemetrySocket* telemetrySocket;

            __qml void startTelemetrySocket(float frequency);
            __qml void stopTelemetrySocket();

            Telemetry* telemetry() const;
            void setTelemetry(Telemetry* other);

            float networkDelay() const;
            void setNetworkDelay(float other);

            signals:
                __signal telemetryChanged();
                __signal networkDelayChanged();

        private:
            explicit Network(QObject *parent = nullptr);
    };
} // namespace Network;
