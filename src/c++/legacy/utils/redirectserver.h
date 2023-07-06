#pragma once

#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;

namespace Networking
{
  class RedirectServer : public QObject
  {
    Q_OBJECT

    public:
      explicit RedirectServer(QObject* parent = nullptr);
      ~RedirectServer() override;

      void start(const QString& address) noexcept;
      void stop() noexcept;
      void push(const QByteArray& data) noexcept;

    private slots:
      void clientConnected();

    private:
      QTcpServer* server;
      QTcpSocket* socket;
  };
} // Networking