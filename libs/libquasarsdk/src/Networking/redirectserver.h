/**
 *  \file COutputRedirectServer.h
 *  \author Дмитрий Рязанцев
 *  \date 05.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include "IConnectable.h"

class QTcpServer;
class QTcpSocket;

namespace QuasarSDK
{
  class OutputRedirectServer : public QObject
                             , public IConnectable
  {
    Q_OBJECT

    public:
      explicit OutputRedirectServer(QObject* parent = nullptr);
      ~OutputRedirectServer() override;

      void start(const QString& address) final;
      void start(const QHostAddress& address) noexcept final;
      void start(const QHostAddress& address, uint16_t port) noexcept final;
      void stop() noexcept final;
      void push(const QByteArray& data) noexcept;

    private:
      Q_SLOT void clientConnected();

    private:
      QTcpServer* m_server;
      QTcpSocket* m_socket;
  };
} // QuasarSDK
