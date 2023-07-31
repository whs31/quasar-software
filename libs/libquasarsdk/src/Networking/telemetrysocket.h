/**
 *  \file CTelemetrySocket.h
 *  \author Дмитрий Рязанцев
 *  \date 05.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "baseudpsocket.h"
#include "telemetry.h"

class QTimer;

namespace QuasarSDK
{
  class TelemetrySocket : public BaseUDPSocket
  {
    Q_OBJECT

    public:
      explicit TelemetrySocket(QObject* parent = nullptr, Telemetry* output = nullptr);

      void start2way(const QString& address, const QString& recv_address) noexcept;
      void stop2way() noexcept;

      [[nodiscard]] float frequency() const; void setFrequency(float);
      [[nodiscard]] bool checkCRC() const; void setCheckCRC(bool);

    signals:
      void ping(); ///< Срабатывает, когда сокет получает телеметрию.

    private:
      Q_SLOT void process(QByteArray data);
      Q_SLOT void request();

    private:
      QTimer* m_updateTimer;
      QUdpSocket* m_requestSocket;
      float m_frequency;
      Telemetry* output;
      QString request_addr;
      uint16_t request_port;
      uint16_t recv_port;
      bool m_checkCRC;
  };
} // QuasarSDK
