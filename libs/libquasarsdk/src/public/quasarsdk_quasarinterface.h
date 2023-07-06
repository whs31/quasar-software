/**
 *  \file quasarsdk_quasarinterface.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <array>
#include <QtCore/QObject>
#include "quasarsdk_enums.h"
#include "navd2/quasarsdk_telemetry.h"
#include "execd/quasarsdk_remotedata.h"

class QTimer;

namespace QuasarSDK
{
  class TelemetrySocket;
  class ExecdSocket;
  class OutputSocket;
  class StripSocket;
  class TCPServer;
  class PingTester;
  class OutputRedirectServer;

  class QuasarAPI : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(Telemetry* telemetry READ telemetry CONSTANT)
    Q_PROPERTY(RemoteData* remote READ remote CONSTANT)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(float currentNetworkDelay READ currentNetworkDelay WRITE setCurrentNetworkDelay NOTIFY currentNetworkDelayChanged)

    public:
      static QuasarAPI* get();

      [[nodiscard]] Telemetry* telemetry() const;
      [[nodiscard]] RemoteData* remote() const;
      [[nodiscard]] bool isConnected() const; void setConnected(bool);
      [[nodiscard]] float currentNetworkDelay() const; void setCurrentNetworkDelay(float);

      [[nodiscard]] TelemetrySocket* telemetrySocket();
      [[nodiscard]] ExecdSocket* execdSocket();
      [[nodiscard]] OutputSocket* outputSocket();
      [[nodiscard]] TCPServer* tcpServer();
      [[nodiscard]] StripSocket* stripSocket();

      Q_INVOKABLE void start(const QString& telemetry_request_address,
                 const QString& telemetry_receive_address,
                 float telemetry_frequency,
                 const QString& execd_address,
                 const QString& feedback_address,
                 const QString& tcp_lfs_address,
                 const QString& udp_lfs_address) noexcept;

      Q_INVOKABLE void startPings() noexcept;

      Q_INVOKABLE void stop() noexcept;

      Q_INVOKABLE void execute(QuasarSDK::Enums::NetworkCommand command) noexcept;
      Q_INVOKABLE void execute(const QString& command) noexcept;

      Q_INVOKABLE [[nodiscard]] QString argument(const QString& key, QuasarSDK::Enums::ArgumentCategory category) noexcept;
      Q_INVOKABLE void setArgument(const QString& key, const QVariant& value, QuasarSDK::Enums::ArgumentCategory category) noexcept;

      Q_INVOKABLE static QString stringify(const QString& ip, const QString& port);

      void setRemoteAddressList(const std::array<QString, 2>& list) noexcept;
      void setPingAddressList(const std::array<QString, 5>& list) noexcept;
      void enableRedirect(const QString& address) noexcept;
      void disableRedirect() noexcept;

    signals:
      void connectedChanged();
      void currentNetworkDelayChanged();

      /**
       * \brief Срабатывает, когда сервер TCP-IP завершает приём данных.
       * \param data - данные, полученные сервером.
       */
      void tcpDataReceived(QByteArray data);

      /**
       * \brief Срабатывает, когда сокет UDP для полосовых РЛИ получает данные.
       * \param data - данные, полученные сокетом.
       */
      void udpDataReceived(QByteArray data);

      /**
        *  \brief Метрики сокета телеметрии.
        *  \details Предоставляет отладочную информацию
        *  о данных, проходящих через сокет в обоих направлениях.
        *  \param data - данные, приведенные к виду строки.
        *  \param size_bytes - размер данных в байтах.
        *  \param out - направление движения данных: \c true означает выходной поток, \c false - входной.
        */
      void telemetrySocketMetrics(const QString& data, int size_bytes, bool out);

      /**
        *  \brief Метрики сокета выполнения команд.
        *  \details Предоставляет отладочную информацию
        *  о данных, проходящих через сокет в обоих направлениях.
        *  \param data - данные, приведенные к виду строки.
        *  \param size_bytes - размер данных в байтах.
        *  \param out - направление движения данных: \c true означает выходной поток, \c false - входной.
        */
      void execdSocketMetrics(const QString& data, int size_bytes, bool out);

      /**
        *  \brief Метрики сервера TCP-IP.
        *  \details Предоставляет отладочную информацию
        *  о данных, проходящих через сокет в обоих направлениях.
        *  \param data - данные, приведенные к виду строки.
        *  \param size_bytes - размер данных в байтах.
        *  \param out - направление движения данных: \c true означает выходной поток, \c false - входной.
        */
      void lfsSocketMetrics(const QString& msg, int size_bytes, bool out);

      /**
        *  \brief Метрики сокета для приема больших данных.
        *  \details Предоставляет отладочную информацию
        *  о данных, проходящих через сокет в обоих направлениях.
        *  \param data - данные, приведенные к виду строки.
        *  \param size_bytes - размер данных в байтах.
        *  \param out - направление движения данных: \c true означает выходной поток, \c false - входной.
        */
      void stripSocketMetrics(const QString& msg, int size_bytes, bool out);

    private:
      explicit QuasarAPI(QObject* parent = nullptr);
      QuasarAPI(const QuasarAPI&);
      QuasarAPI& operator=(const QuasarAPI&);

      void processFeedback(QByteArray) noexcept;

      Q_SLOT void reset_delay();

    private:
      Telemetry* m_telemetry;
      RemoteData* m_remoteData;
      bool m_connected;
      float m_currentNetworkDelay;

      QTimer* m_networkDelayTimer;

      PingTester* m_de10PingTester;
      PingTester* m_jetson0PingTester;
      PingTester* m_navPingTester;
      PingTester* m_com1PingTester;
      PingTester* m_com2PingTester;

      OutputRedirectServer* m_redirectServer;

      TelemetrySocket* m_telemetrySocket;
      ExecdSocket* m_execdSocket;
      OutputSocket* m_outputSocket;
      TCPServer* m_tcpServer;
      StripSocket* m_stripSocket;

      std::array<QString, 2> m_remote_address_list;
      std::array<QString, 5> m_ping_address_list;
      bool m_redirect;
      QString m_redirectAddress;
  };
} // QuasarSDK
