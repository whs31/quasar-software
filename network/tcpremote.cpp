#include "tcpremote.h"
#include "ui_mainwindow.h"


TCPRemote::TCPRemote()
{
    socket = new QTcpSocket( this );
    mainWindow = MainWindow::getMainWinPtr();
    connect(socket,SIGNAL(readyRead()), this, SLOT(readSlot()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnectSlot()));
}

TCPRemote::~TCPRemote()
{
    socket->close();
    delete socket;
}

int TCPRemote::Connect(QString addr){

    QStringList l = addr.split(":");
    socket->connectToHost(l[0], l[1].toInt());

    if( socket->waitForConnected(3000) ) {
        return 0;
    }
    qDebug() << "Connection timeout";
    return -1;
}

int TCPRemote::Disconnect(){
    socket->close();
    emit this->disconnected();
    return 0;
}

int TCPRemote::Send(QByteArray data){
    int n = socket->write(data);
    socket->waitForBytesWritten();
    return n;
}

void TCPRemote::readSlot(){
    emit this->received(socket->readAll());
}

void TCPRemote::disconnectSlot(){
    emit this->disconnected();
}