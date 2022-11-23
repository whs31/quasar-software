#include "tcpdownloader.h"

TCPDownloader::TCPDownloader(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    if(!server->listen(QHostAddress::LocalHost, 10000))
    {
        qCritical() << "[SERVER] Server could not start";
    } else {
        qInfo()<<"[SERVER] Server started.";
    }
}

void TCPDownloader::clientConnected(void)
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TCPDownloader::serverRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPDownloader::clientDisconnected);
}

void TCPDownloader::clientDisconnected(void)
{
    uint8_t i = datagram.indexOf('\n');
    QByteArray fnamearr = datagram;

    fnamearr.truncate(i);
    QString qfilename = QString::fromLocal8Bit(QByteArray::fromRawData(fnamearr, sizeof(fnamearr)));
    qCritical()<<i<<"     "<<qfilename; //30       "Z�V�5:� ���� �"

    socket->close();
}

void TCPDownloader::serverRead(void)
{
    while(socket->bytesAvailable()>0)
    {
        datagram.append(socket->readAll());
    }
}
