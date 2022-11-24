#include "tcpdownloader.h"

TCPDownloader::TCPDownloader(QObject *parent, DowloaderMode mode) : QObject(parent), _mode(mode)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    if(!server->listen(QHostAddress::LocalHost, 10000))
    {
        qCritical() << "[SERVER] Server could not start";
    } else {
        qInfo()<<"[SERVER] Server started.";
    }
    manager = new ImageManager();
}

void TCPDownloader::clientConnected(void)
{
    if(SConfig::SAVEATEND) { _mode = 2; } else { _mode = 1; }
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TCPDownloader::serverRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPDownloader::clientDisconnected);
    datagram.clear();
    fnameCheck = false;
    success = false;
    splitIndex = 0;
    qInfo()<<"[SERVER] SAR connected and ready to send image";
}

void TCPDownloader::clientDisconnected(void)
{
    socket->close();
    (success) ? qInfo()<<"[SERVER] Image fully received from SAR" : qWarning()<<"[SERVER] Something went wrong in receiving SAR image";
    if(_mode == 2) { success = manager->saveRawData(imageData, filename); }
    emit receivingFinished();
}
void TCPDownloader::serverRead(void)
{

    while(socket->bytesAvailable()>0)
    {
        datagram.append(socket->readAll());
        if(datagram.contains('\n')&&!fnameCheck)
        {
            splitIndex = datagram.indexOf('\n');
            QByteArray fnamearr = datagram;
            fnamearr.truncate(splitIndex);
            filename = QString::fromUtf8(fnamearr);
            fnameCheck = true;
            qDebug()<<"[SERVER] Received filename: "<<filename;
        }
        else if(fnameCheck)
        {
            imageData = datagram;
            imageData.remove(0,splitIndex+1);
            //qWarning()<<splitIndex;
            if(_mode == 1) { success = manager->saveRawData(imageData, filename); }
        }
    }
}
