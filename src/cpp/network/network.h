#pragma once

#include <QtCore/QObject>
#include <LPVL/Global>
#include "netenums.h"
#include "telemetry/telemetry.h"
#include "execd/remotedata.h"

class QTimer;

namespace Network
{
    class TelemetrySocket;
    class ExecdSocket;
    class FeedbackSocket;
    class TCPSocket;
    class Pinger;

    class Network : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
        Q_PROPERTY(RemoteData* remoteData READ remoteData WRITE setRemoteData NOTIFY remoteDataChanged)
        Q_PROPERTY(float networkDelay READ networkDelay WRITE setNetworkDelay NOTIFY networkDelayChanged)
        Q_PROPERTY(float tcpProgress READ tcpProgress WRITE setTcpProgress NOTIFY tcpProgressChanged)
        Q_PROPERTY(int connected READ connected WRITE setConnected NOTIFY connectedChanged)
        Q_PROPERTY(int de10Status READ de10Status WRITE setDe10Status NOTIFY de10StatusChanged)
        Q_PROPERTY(int jetsonStatus READ jetsonStatus WRITE setJetsonStatus NOTIFY jetsonStatusChanged)
        Q_ENUM(PingStatus)
        LPVL_DECLARE_SINGLETON(Network);

        constexpr static float DISCONNECT_DELAY_THRESHOLD = 10.0f;
        constexpr static float SEMICONNECT_DELAY_THRESHOLD = 3.0f;
        constexpr static float PING_INTERVAL = 5.0f;

        public:
            enum ArgumentCategory
            {
                Form,
                Focus,
                Reform
            };

            enum NetworkCommand
            {
                FormImage,
                FocusImage,
                ReformImage,
                RemoteStorageStatus,
                ClearRemoteStorage,
                Ping
            };

            Q_ENUM(ArgumentCategory)
            Q_ENUM(NetworkCommand)

            TelemetrySocket* telemetrySocket;
            ExecdSocket* execdSocket;
            FeedbackSocket* feedbackSocket;
            TCPSocket* tcpSocket;

            Q_INVOKABLE void startTelemetrySocket(const QString& address, float frequency);
            Q_INVOKABLE void stopTelemetrySocket();

            Q_INVOKABLE void startExecdSocket(const QString& execd_address, const QString& feedback_address);
            Q_INVOKABLE void stopExecdSocket();
            Q_INVOKABLE void executeCommand(const Network::Network::NetworkCommand command) noexcept;
            Q_INVOKABLE QString argument(const QString& key, Network::Network::ArgumentCategory category = Form) const noexcept;
            Q_INVOKABLE void setArgument(const QString& key, const QVariant& value, Network::Network::ArgumentCategory category = Form) noexcept;

            Q_INVOKABLE void startTCPSocket(const QString& address);
            Q_INVOKABLE void stopTCPSocket();

            Telemetry* telemetry() const; void setTelemetry(Telemetry*);
            RemoteData* remoteData() const; void setRemoteData(RemoteData*);
            float networkDelay() const; void setNetworkDelay(float);
            int connected() const; void setConnected(int);
            float tcpProgress() const; void setTcpProgress(float);
            int de10Status() const; void setDe10Status(int);
            int jetsonStatus() const; void setJetsonStatus(int);

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
                void tcpProgressChanged();
                void de10StatusChanged();
                void jetsonStatusChanged();

            private:
            explicit Network(QObject* parent = nullptr);

        private:
            QTimer* m_network_delay_timer;

            Telemetry* m_telemetry;
            RemoteData* m_remoteData;

            Pinger* m_de10ping;
            Pinger* m_jetsonping;

            float m_networkDelay;
            int m_connected;
            float m_tcpProgress;
            int m_de10Status = (int)PingStatus::Idle;
            int m_jetsonStatus = (int)PingStatus::Idle;
    };
} // namespace Network;
