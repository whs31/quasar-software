/**
 *  \file quasarsdk_quasarinterface.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

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

  class QuasarInterface : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(Telemetry* telemetry READ telemetry CONSTANT)
    Q_PROPERTY(RemoteData* remote READ remote CONSTANT)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(float currentNetworkDelay READ currentNetworkDelay WRITE setCurrentNetworkDelay NOTIFY currentNetworkDelayChanged)

    public:
      [[nodiscard]] Telemetry* telemetry() const;
      [[nodiscard]] RemoteData* remote() const;
      [[nodiscard]] bool isConnected() const; void setConnected(bool);
      [[nodiscard]] float currentNetworkDelay() const; void setCurrentNetworkDelay(float);

      TelemetrySocket* telemetrySocket();
      ExecdSocket* execdSocket();
      OutputSocket* outputSocket();
      TCPServer* tcpServer();
      StripSocket* stripSocket();

    signals:
      void connectedChanged();
      void currentNetworkDelayChanged();

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
  };
} // QuasarSDK
