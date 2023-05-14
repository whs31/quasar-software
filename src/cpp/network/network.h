#pragma once

#include "telemetry/telemetry.h"
#include "execd/remotedata.h"
#include <QtCore/QObject>
#include <ccl/ccl_global.h>

class QTimer;

namespace Network
{
    class TelemetrySocket;
    class ExecdSocket;
    class FeedbackSocket;
    class TCPSocket;

    class Network : public QObject
    {
        Q_OBJECT
        DEFINE_AS_SINGLETON(Network);
        PROPERTY_PTR(Telemetry*, telemetry, setTelemetry, m_telemetry)
        PROPERTY_PTR(RemoteData*, remoteData, setRemoteData, m_remoteData)
        PROPERTY(float, networkDelay, setNetworkDelay, m_networkDelay)
        PROPERTY_DEF(int, connected, setConnected, m_connected)

        constexpr static float DISCONNECT_DELAY_THRESHOLD = 10.0f;
        constexpr static float SEMICONNECT_DELAY_THRESHOLD = 3.0f;

        public:
            TelemetrySocket* telemetrySocket;
            ExecdSocket* execdSocket;
            FeedbackSocket* feedbackSocket;
            TCPSocket* tcpSocket;

            Q_INVOKABLE void startTelemetrySocket(const QString& address, float frequency);
            Q_INVOKABLE void stopTelemetrySocket();

            Q_INVOKABLE void startExecdSocket(const QString& execd_address, const QString& feedback_address);
            Q_INVOKABLE void stopExecdSocket();
            Q_INVOKABLE void executeCommand(const QString& command);

            Q_INVOKABLE void startTCPSocket(const QString& address);
            Q_INVOKABLE void stopTCPSocket();

            signals:
                void telemetryChanged();
                void remoteDataChanged();
                void networkDelayChanged();
                void connectedChanged();

                void telemetrySocketMetrics(const QString& data, int size_bytes);
                void execdSocketMetrics(const QString& data, int size_bytes);
                void feedbackSocketMetrics(const QString& data, int size_bytes);
                void lfsSocketMetrics(const QString& msg, int size_bytes);
                void stripSocketMetrics(const QString msg, int size_bytes);

        private:
            explicit Network(QObject* parent = nullptr);

        private:
            QTimer* m_network_delay_timer;

            Telemetry* m_telemetry;
            RemoteData* m_remoteData;

            float m_networkDelay = DISCONNECT_DELAY_THRESHOLD + .1f;
            int m_connected = 0;
    };
} // namespace Network;
