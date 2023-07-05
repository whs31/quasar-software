/**
 *  \file quasarsdk_outputredirectserver.h
 *  \author Дмитрий Рязанцев
 *  \date 05.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;

namespace QuasarSDK
{
  class OutputRedirectServer : public QObject
  {
    Q_OBJECT

    public:
      explicit OutputRedirectServer(QObject* parent = nullptr);
      ~OutputRedirectServer() override;

      void start(const QString& address) noexcept;
      void stop() noexcept;
      void push(const QByteArray& data) noexcept;

    private:
      Q_SLOT void clientConnected();

    private:
      QTcpServer* m_server;
      QTcpSocket* m_socket;
  };
} // QuasarSDK
