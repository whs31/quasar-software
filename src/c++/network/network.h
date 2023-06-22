#pragma once

#include <QtCore/QObject>
#include <LPVL/Global>
#include "netenums.h"
#include "telemetry/telemetry.h"
#include "execd/remotedata.h"

class QTimer;

//! @namespace Namespace for network-related classes.
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

        //! @defgroup Properties
        //! @{
        //! @property Holds pointer to telemetry storage.
        Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
        //! @property Holds pointer to remote data storage.
        Q_PROPERTY(RemoteData* remoteData READ remoteData WRITE setRemoteData NOTIFY remoteDataChanged)
        //! @property Network delay in seconds from last received packet.
        Q_PROPERTY(float networkDelay READ networkDelay WRITE setNetworkDelay NOTIFY networkDelayChanged)
        //! @property TCP-IP package loading progress value.
        Q_PROPERTY(float tcpProgress READ tcpProgress WRITE setTcpProgress NOTIFY tcpProgressChanged)
        //! @property Connection state. 2 means fully connected, 0 means fully unconnected.
        Q_PROPERTY(int connected READ connected WRITE setConnected NOTIFY connectedChanged)
        //! @}

        //! @var Constant threshold for connection indicator.
        //!      Connection status will be changed to unconnected if
        //!      network delay will exceed threshold.
        constexpr static float DISCONNECT_DELAY_THRESHOLD = 10.0f;

        //! @var Constant threshold for connection problems indicator.
        constexpr static float SEMICONNECT_DELAY_THRESHOLD = 3.0f;

        //! @var How often (in seconds) ping command will be executed.
        constexpr static float PING_INTERVAL = 5.0f;

        public:
            //! @brief Returns singleton instance of class.
            static Network* get();

            TelemetrySocket* telemetrySocket;       //! @var Pointer to telemetry socket instance.
            ExecdSocket* execdSocket;               //! @var Pointer to execd socket instance.
            FeedbackSocket* feedbackSocket;         //! @var Pointer to feedback socket instance.
            TCPSocket* tcpSocket;                   //! @var Pointer to tcp-ip socket instance.

            Q_INVOKABLE void begin(const QString& telemetry_request_addr, const QString& telemetry_recv_addr,
                                   float telemetry_frequency,
                                   const QString& execd_addr, const QString& feedback_addr,
                                   const QString& tcp_lfs_addr, const QString& udp_lfs_addr) noexcept;

            Q_INVOKABLE void stop() noexcept;

            //! @brief   Executes built-in execd command.
            //! @details If command relies on argument list (e.g. focus, telescopic, strip),
            //!          arguments will be automatically calculated from ExecdArgumentList.
            //!          More info in documentation for ExecdArgumentList and functions
            //!          setArgument(...), argument(...).
            //! @details Can be invoked from QML.
            //! @example executeCommand(Networking::Enums::FormImage);
            Q_INVOKABLE void executeCommand(const Networking::Enums::NetworkCommand command) noexcept;

            //! @brief   Wraps and tries to execute any custom string command.
            //! @details Can be invoked from QML.
            //! @example executeCommand("$clear_storage()");
            Q_INVOKABLE void executeString(const QString& string) noexcept;

            //! @brief   Returns argument from ArgumentList instance.
            //! @param   key - argument key (e.g. "--x0").
            //! @param   category - category of argument (Form, Focus, Reform).
            //! @returns QString argument.
            //! @details Can be invoked from QML.
            //! @example argument("--e0", Networking::Enums::Form);
            Q_INVOKABLE QString argument(const QString& key, Networking::Enums::ArgumentCategory category = Enums::Form) const noexcept;

            //! @brief   Sets argument in ArgumentList instance.
            //! @param   key - argument key (e.g. "--x0".
            //! @param   value - QVariant-value. Will be automatically casted
            //!          to QString internally.
            //! @param   category - category of argument, same as argument(...) function.
            //! @details Can be invoked from QML.
            //! @example setArgument("-v", QVariant::fromValue(159.0f), Networking::Enums::Focus);
            Q_INVOKABLE void setArgument(const QString& key, const QVariant& value, Networking::Enums::ArgumentCategory category = Enums::Form) noexcept;

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
                void tcpProgressChanged();

                //! @group Metrics
                //! @details Provides stringified data, packet size and direction.
                void telemetrySocketMetrics(const QString& data, int size_bytes, bool out); //! @ingroup Metrics
                void execdSocketMetrics(const QString& data, int size_bytes, bool out);     //! @ingroup Metrics
                void feedbackSocketMetrics(const QString& data, int size_bytes, bool out);  //! @ingroup Metrics
                void lfsSocketMetrics(const QString& msg, int size_bytes, bool out);        //! @ingroup Metrics
                void stripSocketMetrics(const QString msg, int size_bytes, bool out);       //! @ingroup Metrics

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
