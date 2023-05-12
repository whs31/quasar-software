#pragma once

#include <Definitions>
#include "telemetry/telemetry.h++"
#include "execd/remotedata.h++"
#include <QtCore/QObject>

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
        DECLARE_SINGLETON(Network);

        Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
        Q_PROPERTY(RemoteData* remoteData READ remoteData WRITE setRemoteData NOTIFY remoteDataChanged)
        Q_PROPERTY(float networkDelay READ networkDelay WRITE setNetworkDelay NOTIFY networkDelayChanged)
        Q_PROPERTY(int connected READ connected WRITE setConnected NOTIFY connectedChanged)

        constexpr __global float DISCONNECT_DELAY_THRESHOLD = 10.0f;
        constexpr __global float SEMICONNECT_DELAY_THRESHOLD = 3.0f;

        public:
            TelemetrySocket* telemetrySocket;
            ExecdSocket* execdSocket;
            FeedbackSocket* feedbackSocket;
            TCPSocket* tcpSocket;

            __qml void startTelemetrySocket(const QString& address, float frequency);
            __qml void stopTelemetrySocket();

            __qml void startExecdSocket(const QString& execd_address, const QString& feedback_address);
            __qml void stopExecdSocket();
            __qml void executeCommand(const QString& command);

            __qml void startTCPSocket(const QString& address);
            __qml void stopTCPSocket();

            __getter Telemetry* telemetry() const;
            __setter void setTelemetry(Telemetry* other);

            __getter RemoteData* remoteData() const;
            __setter void setRemoteData(RemoteData* other);

            __getter float networkDelay() const;
            __setter void setNetworkDelay(float other);

            __getter int connected() const;
            __setter void setConnected(int other);

            signals:
                __signal telemetryChanged();
                __signal remoteDataChanged();
                __signal networkDelayChanged();
                __signal connectedChanged();

                __signal __profile telemetrySocketMetrics(const QString& data, int size_bytes);
                __signal __profile execdSocketMetrics(const QString& data, int size_bytes);
                __signal __profile feedbackSocketMetrics(const QString& data, int size_bytes);
                __signal __profile lfsSocketMetrics(const QString& msg, int size_bytes);
                __signal __profile stripSocketMetrics(const QString msg, int size_bytes);

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