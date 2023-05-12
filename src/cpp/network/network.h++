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
        DEFINE_AS_SINGLETON(Network);
        PROPERTY_PTR(Telemetry*, telemetry, setTelemetry, m_telemetry)
        PROPERTY_PTR(RemoteData*, remoteData, setRemoteData, m_remoteData)
        PROPERTY(float, networkDelay, setNetworkDelay, m_networkDelay)
        PROPERTY_DEF(int, connected, setConnected, m_connected)

        constexpr __global float DISCONNECT_DELAY_THRESHOLD = 10.0f;
        constexpr __global float SEMICONNECT_DELAY_THRESHOLD = 3.0f;

        public:
            TelemetrySocket* telemetrySocket;
            ExecdSocket* execdSocket;
            FeedbackSocket* feedbackSocket;
            TCPSocket* tcpSocket;

            __exposed void startTelemetrySocket(const QString& address, float frequency);
            __exposed void stopTelemetrySocket();

            __exposed void startExecdSocket(const QString& execd_address, const QString& feedback_address);
            __exposed void stopExecdSocket();
            __exposed void executeCommand(const QString& command);

            __exposed void startTCPSocket(const QString& address);
            __exposed void stopTCPSocket();

            signals:
                __property_signal telemetryChanged();
                __property_signal remoteDataChanged();
                __property_signal networkDelayChanged();
                __signal connectedChanged();

                __signal telemetrySocketMetrics(const QString& data, int size_bytes);
                __signal execdSocketMetrics(const QString& data, int size_bytes);
                __signal feedbackSocketMetrics(const QString& data, int size_bytes);
                __signal lfsSocketMetrics(const QString& msg, int size_bytes);
                __signal stripSocketMetrics(const QString msg, int size_bytes);

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
