#include "tcpsocket.h++"
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

using namespace Network;

TCPSocket::TCPSocket(QObject *parent)
    : QObject{parent}
    , server(new QTcpServer(this))
    , timer(new QTimer(this))
{
    QObject::connect(server, &QTcpServer::newConnection, this, &TCPSocket::clientConnected);
    timer->setInterval(TCP_TIMEOUT);
    QObject::connect(timer, &QTimer::timeout, this, &TCPSocket::connectionTimeout);
}

void TCPSocket::startServer(const QString& address)
{
    if(not address.contains(":") or address.split(":").size() > 2)
    {
        qCritical().noquote() << "[TCP] Provided incorrect IP:" << address;
        return;
    }

    QString ip = address.split(":").first();
    uint16_t port = address.split(":").last().toUInt();
    if(not server->listen(QHostAddress(ip), port))
    {
        qCritical() << "[TCP] TCP-IP server has failed to start.";
        return;
    }

    qInfo() << "[TCP] TCP-IP server started.";
}

void TCPSocket::stopServer()
{
    server->close();
    qInfo() << "[TCP] TCP-IP server closed connection";
}

void TCPSocket::clientConnected()
{

}

void TCPSocket::serverRead()
{

}

void TCPSocket::clientDisconnected()
{

}

void TCPSocket::connectionTimeout()
{

}

void TCPSocket::readFileInfo(QByteArray data)
{

}

void TCPSocket::readFileBody(QByteArray data)
{

}

