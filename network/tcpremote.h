#ifndef TCPREMOTE_H
#define TCPREMOTE_H

#include <QObject>
#include <QTcpSocket>

#include "remote.h"
#include "mainwindow.h"


class MainWindow;
class TCPRemote : public Remote
{
    Q_OBJECT
public:
    TCPRemote();
    ~TCPRemote();
    int Connect(QString addr);
    int Disconnect();
    int Send(QByteArray data);

private:
    QTcpSocket *socket;
    MainWindow *mainWindow;

private slots:
    void readSlot();
    void disconnectSlot();

};
#endif // TCPREMOTE_H
