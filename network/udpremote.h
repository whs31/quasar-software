#ifndef UDPREMOTE_H
#define UDPREMOTE_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>

#include "remote.h"

class UDPRemote : public Remote
{
    Q_OBJECT
public:
   UDPRemote();
   ~UDPRemote();
   int Connect(QString addr);
   int Disconnect();
   int Send(QByteArray data);

private:
    quint16 port;
    QHostAddress host;
    QUdpSocket *socket;

private slots:
    void readyRead();

};

#endif // UDPREMOTE_H
