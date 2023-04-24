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
    connect(server, &QTcpServer::newConnection, this, &TCPSocket::clientConnected);
//    if(!server->listen(QHostAddress(SConfig::get()->getComputerIP()), SConfig::get()->getLoaderPort().toUInt()))
//    {
//        qCritical() << "[TCP] TCP-IP server has failed to start.";
//    } else {
//        qInfo() << "[TCP] TCP-IP server started.";
//    }
    timer->setInterval(TCP_TIMEOUT);
    connect(timer, &QTimer::timeout, this, &TCPSocket::connectionTimeout);

}

