#pragma once

#include <QtCore/QObject>
#include <LPVL/Global>
#include "netenums.h"
#include "telemetry/telemetry.h"
#include "execd/remotedata.h"

class QTimer;

//! @namespace Namespace network-related classes.
namespace Networking
{
    class TelemetrySocket;
    class ExecdSocket;
    class FeedbackSocket;
    class TCPSocket;
    class Pinger;

    //! @class Class-factory for common network
    //!        operations.
    class Network : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
        Q_PROPERTY(RemoteData* remoteData READ remoteData WRITE setRemoteData NOTIFY remoteDataChanged)
        Q_PROPERTY(float networkDelay READ networkDelay WRITE setNetworkDelay NOTIFY networkDelayChanged)
        Q_PROPERTY(float tcpProgress READ tcpProgress WRITE setTcpProgress NOTIFY tcpProgressChanged)
        Q_PROPERTY(int connected READ connected WRITE setConnected NOTIFY connectedChanged)

        constexpr static float DISCONNECT_DELAY_THRESHOLD = 10.0f;
        constexpr static float SEMICONNECT_DELAY_THRESHOLD = 3.0f;
        constexpr static float PING_INTERVAL = 5.0f;

        public:
            //! @brief Returns singleton instance of class.
            static Network* get();

            TelemetrySocket* telemetrySocket;
            ExecdSocket* execdSocket;
            FeedbackSocket* feedbackSocket;
            TCPSocket* tcpSocket;

            Q_INVOKABLE void startTelemetrySocket(const QString& request_address, const QString& recv_address, float frequency);
            Q_INVOKABLE void stopTelemetrySocket();

            Q_INVOKABLE void startExecdSocket(const QString& execd_address, const QString& feedback_address);
            Q_INVOKABLE void stopExecdSocket();
            Q_INVOKABLE void executeCommand(const Networking::Enums::NetworkCommand command) noexcept;
            Q_INVOKABLE void executeString(const QString& string) noexcept;
            Q_INVOKABLE QString argument(const QString& key, Networking::Enums::ArgumentCategory category = Enums::Form) const noexcept;
            Q_INVOKABLE void setArgument(const QString& key, const QVariant& value, Networking::Enums::ArgumentCategory category = Enums::Form) noexcept;

            Q_INVOKABLE void startTCPSocket(const QString& address);
            Q_INVOKABLE void stopTCPSocket();

            [[nodiscard]] Telemetry* telemetry() const; void setTelemetry(Telemetry*);
            [[nodiscard]] RemoteData* remoteData() const; void setRemoteData(RemoteData*);
            [[nodiscard]] float networkDelay() const; void setNetworkDelay(float);
            [[nodiscard]] int connected() const; void setConnected(int);
            [[nodiscard]] float tcpProgress() const; void setTcpProgress(float);

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

        private:
            explicit Network(QObject* parent = nullptr);
            Network(const Network &);
            Network &operator=(const Network &);

        private:
            QTimer* m_network_delay_timer;

            Telemetry* m_telemetry;
            RemoteData* m_remoteData;

            Pinger* m_de10ping;
            Pinger* m_jetsonping;
            Pinger* m_navping;
            Pinger* m_utl1ping;
            Pinger* m_utl2ping;

            float m_networkDelay;
            int m_connected;
            float m_tcpProgress;
    };
} // namespace Network;
