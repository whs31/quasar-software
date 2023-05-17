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
        Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
        Q_PROPERTY(RemoteData* remoteData READ remoteData WRITE setRemoteData NOTIFY remoteDataChanged)
        Q_PROPERTY(float networkDelay READ networkDelay WRITE setNetworkDelay NOTIFY networkDelayChanged)
        Q_PROPERTY(int connected READ connected WRITE setConnected NOTIFY connectedChanged)
        DEFINE_AS_SINGLETON(Network);

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

            Telemetry* telemetry() const; void setTelemetry(Telemetry*);
            RemoteData* remoteData() const; void setRemoteData(RemoteData*);
            float networkDelay() const; void setNetworkDelay(float);
            int connected() const; void setConnected(int);

            signals:
                void telemetryChanged();
                void remoteDataChanged();
                void networkDelayChanged();
                void connectedChanged();

                void telemetrySocketMetrics(const QString& data, int size_bytes, bool out);
                void execdSocketMetrics(const QString& data, int size_bytes, bool out);
                void feedbackSocketMetrics(const QString& data, int size_bytes, bool out);
                void lfsSocketMetrics(const QString& msg, int size_bytes, bool out);
                void stripSocketMetrics(const QString msg, int size_bytes, bool out);

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
