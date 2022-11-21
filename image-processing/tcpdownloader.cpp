#include "tcpdownloader.h"

TCPDownloader::TCPDownloader(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any, 9999)) { qCritical() << "[SERVER] Server could not start"; } else { qInfo()<<"[SERVER] Server started."; }
}

void TCPDownloader::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    socket->flush();

    socket->waitForBytesWritten(3000);
    socket->readAll(); //<---------------
    socket->close();
}
