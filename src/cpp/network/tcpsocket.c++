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

float TCPSocket::progress()
{
    float percent = (float)imageData.size() / fileSize;
    emit progressChanged(percent * 100);
    return percent;
}

void TCPSocket::clientConnected()
{
    qInfo() << "[TCP] SAR connected";

    socket = server->nextPendingConnection();
    if(not socket) {
        qCritical() << "[TCP] NextPendingConnection returned nullptr. Aborting connection.";
        return;
    }
    connect(socket, &QTcpSocket::readyRead, this, &TCPSocket::serverRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPSocket::clientDisconnected);
    imageData64.clear();
    imageData.clear();
    readFile = &TCPSocket::readFileInfo;
    success = false;
    timer->start();
    splitIndex = 0;

    qInfo() << "[TCP] SAR ready to send image";

}

void TCPSocket::serverRead()
{
    (this->*readFile)(socket->readAll());
}

void TCPSocket::clientDisconnected()
{
    socket->close();
    timer->stop();

    (fileSize == imageData.size()) ? qInfo() << "[TCP] Package fully received from SAR"
                                   : qWarning() << "[TCP] Something went wrong in receiving SAR image";

    if(not filename.contains(".zip"))
    {
        /// @todo process image here
        //ImageManager::newImage(CacheManager::getTcpDowloaderCache() + "/" + filename, imageData);
    }
    emit receivingFinished();
}

void TCPSocket::connectionTimeout()
{
    socket->close();
}

void TCPSocket::readFileInfo(QByteArray data)
{
    readFile = &TCPSocket::readFileBody;

    uint8_t i = data.indexOf('\n') + 1; // maybe + 1;
    filename = data.left(i - 1).data();
    memcpy(&fileSize, data.mid(i, sizeof(uint32_t)).data(), sizeof(uint32_t));

    i += sizeof(uint32_t);

    qDebug().noquote() << "[TCP] LFS filename:" << filename;
    qDebug().noquote() << "[TCP] LFS size:" << QString::number(fileSize / 1024) << "kB";

    data.remove(0, i);

    timer->stop();
    timer->start();
    (this->*readFile)(data);

}

void TCPSocket::readFileBody(QByteArray data)
{
    timer->stop();
    timer->start();
    if(data.size())
        imageData.append(data);
    this->progress();
}

