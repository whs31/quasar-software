#include "tcpdownloader.h"


/*
 *  1. Сделать enum для режима работы загрузчика (сохранение прогрессивного рли в процессе получения данных, либо сохранение по итогу)
 *  2. Добавить в конфиг бул на 2 режима работы программы (чтение с директории, чтение с загрузчика)
 *  3. Режим работы загрузчика тоже в конфиг
*/

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
    manager = new ImageManager();
}

void TCPDownloader::clientConnected(void)
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TCPDownloader::serverRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPDownloader::clientDisconnected);
    datagram.clear();
    fnameCheck = false;
    success = false;
    qInfo()<<"[SERVER] SAR connected and ready to send image";
}

void TCPDownloader::clientDisconnected(void)
{
    socket->close();
    (success) ? qDebug()<<"[SERVER] Image fully received from SAR" : qCritical()<<"[SERVER] Image was not received from SAR (saving or receiving error!)";
}

void TCPDownloader::serverRead(void)
{
    QPixmap image;
    while(socket->bytesAvailable()>0)
    {
        datagram.append(socket->readAll());
        uint8_t i = 0;
        if(datagram.contains('\n'))
        {
            i = datagram.indexOf('\n');
            imageData = datagram;
            imageData.remove(0,i+1);
        }
        if(datagram.contains('\n')&&!fnameCheck)
        {
            QByteArray fnamearr = datagram;
            fnamearr.truncate(i);
            filename = QString::fromUtf8(fnamearr);
            fnameCheck = true;
            qDebug()<<"[SERVER] Received filename: "<<filename;
        }
        else if(fnameCheck)
        {
            success = manager->saveRawData(imageData, filename);
        }
    }
}
