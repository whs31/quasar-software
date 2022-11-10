#ifndef UDPREMOTE_H
#define UDPREMOTE_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>

#include <QUdpSocket>

#include "remote.h"
#include "mainwindow.h"


class MainWindow;
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
    MainWindow *mainWindow;

    quint16 port;
    QHostAddress host;
    QUdpSocket *socket;

private slots:
    void readyRead();

};

#endif // UDPREMOTE_H
