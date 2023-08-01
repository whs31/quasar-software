//
// Created by whs31 on 30.07.23.
//

#pragma once

#include "baseudpsocket.h"
#include "remotedata.h"

class QTimer;

namespace QuasarSDK
{
  class StatusSocket : public BaseUDPSocket
  {
    Q_OBJECT
    constexpr static int FREQUENCY = 1'000;

    public:
      explicit StatusSocket(QObject* parent = nullptr, RemoteData* remote_data_pointer = nullptr);
      Q_INVOKABLE void setRequestAddress(const QString& addr);
      Q_INVOKABLE void start(const QString& address) override;
      Q_INVOKABLE void stop() noexcept override;

    private:
      Q_SLOT void process(QByteArray data) noexcept;
      Q_SLOT void request();

    private:
      QTimer* m_updateTimer;
      QUdpSocket* m_requestSocket;
      RemoteData* m_output;
      QString m_request_addr;
      uint16_t m_request_port;
      uint16_t m_recv_port;
  };
} // QuasarSDK

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::StatusSocket*)