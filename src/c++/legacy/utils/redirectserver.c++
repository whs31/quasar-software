#include "redirectserver.h"
#include <QtCore/QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

namespace Networking
{

  RedirectServer::RedirectServer(QObject* parent)
    : QObject(parent)
    , server(new QTcpServer(this))
    , socket(nullptr)
  {
    connect(server, &QTcpServer::newConnection, this, &RedirectServer::clientConnected);
  }

  RedirectServer::~RedirectServer()
  {
    if(socket)
      delete socket;
    server->close();
  }

  void RedirectServer::start(const QString& address) noexcept
  {
    if(not address.contains(":") or address.split(":").size() > 2)
    {
      qCritical().noquote() << "[TCP] Provided incorrect IP:" << address;
      return;
    }

    QString ip = address.split(":").first();
    uint16_t port = address.split(":").last().toUInt();

    if(server->listen(QHostAddress(ip), port))
      qDebug() << "[REDIRECT] Server started successfully at" << address;
    else
      qCritical() << "[REDIRECT] Server failed to start";
  }

  void RedirectServer::stop() noexcept
  {
    server->close();
  }

  void RedirectServer::push(const QByteArray& data) noexcept
  {
    if(socket == nullptr)
      return;
    socket->write(data);
    socket->flush();
    socket->waitForBytesWritten();
  }

  void RedirectServer::clientConnected()
  {
    if(socket != nullptr)
      delete socket;
    socket = server->nextPendingConnection();
  }

} // Networking