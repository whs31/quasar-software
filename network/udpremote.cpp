#include "udpremote.h"
#include "ui_mainwindow.h"

UDPRemote::UDPRemote()
{
    mainWindow = MainWindow::getMainWinPtr();
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

UDPRemote::~UDPRemote()
{
    socket->close();
    delete socket;
}

int UDPRemote::Connect(QString addr){
    QStringList l = addr.split(":");
    host.setAddress(l[0]);
    port = l[1].toInt();
    qDebug() << "Binding:" << host << port;
    return socket->bind(host,port);
}

int UDPRemote::Disconnect(){
    socket->close();
    host.clear();
    return 0;
}

int UDPRemote::Send(QByteArray data){
    if(!host.isNull()){
        return socket->writeDatagram(data, host, port);
    }
    return -1;
}

void UDPRemote::readyRead(){

    //qDebug() << "Read";

    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(Buffer.data(), (qint64) Buffer.size(), &host, &port);

    emit this->received(Buffer);
}
