#include "tcpdownloader.h"

TCPDownloader::TCPDownloader(QObject *parent, DowloaderMode mode) : QObject(parent), _mode(mode)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    if(!server->listen(QHostAddress(SConfig::LOADERIP), SConfig::LOADERPORT.toUInt()))
    {

        qCritical() << "[SERVER] Server could not start";
    } else {
        qInfo()<<"[SERVER] Server started.";
    }
    manager = new ImageManager();
    timer = new QTimer();
    timer->setInterval(TCP_TIMEOUT);
    connect(timer, &QTimer::timeout, this, &TCPDownloader::connectionTimeout);
}

void TCPDownloader::clientConnected(void)
{
    if(SConfig::SAVEATEND) { _mode = 2; } else { _mode = 1; }
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TCPDownloader::serverRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPDownloader::clientDisconnected);
    imageData64.clear();
    imageData.clear();
    readFile = &TCPDownloader::readFileInfo;
    success = false;
    timer->start();
    splitIndex = 0;
    qInfo()<<"[SERVER] SAR connected and ready to send image";
}

void TCPDownloader::clientDisconnected(void)
{
    socket->close();
    timer->stop();
    (fileSize == imageData.size()) ? qInfo()<<"[SERVER] Image fully received from SAR" : qWarning()<<"[SERVER] Something went wrong in receiving SAR image";
    if(_mode == 2) { success = manager->saveRawData(imageData, filename); }
    emit receivingFinished();
}
void TCPDownloader::serverRead(void)
{
    (this->*readFile) (socket->readAll());
}

void TCPDownloader::readFileInfo(QByteArray data)
{
    readFile = &TCPDownloader::readFileBody;

    filename = QString(data);
    uint8_t i = data.indexOf('\0') + 1;
    memcpy(&fileSize, data.mid(i, sizeof(uint32_t)).data(), sizeof(uint32_t));
    i+=sizeof(uint32_t);

    qDebug() << "Name:" << filename;
    qDebug() << "fileSize:" << fileSize;

    data.remove(0, i);

    timer->stop();
    timer->start();
    (this->*readFile)(data);
}

void TCPDownloader::readFileBody(QByteArray data)
{
    timer->stop();
    timer->start();
    if(data.size()){
        imageData.append(data);
        imageData64.append(data.toBase64());
    }
    progress();
}

float TCPDownloader::progress(){
    float f = (float)imageData.size() / fileSize;
    emit progressChanged(f*100);
    return f;
}

void TCPDownloader::connectionTimeout(void){
    socket->close();
}
