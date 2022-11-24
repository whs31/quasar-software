#ifndef TCPDOWNLOADER_H
#define TCPDOWNLOADER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class TCPDownloader : public QObject
{
    Q_OBJECT
public:
    explicit TCPDownloader(QObject *parent = nullptr);


signals:

public slots:
    void clientConnected(void);
    void serverRead(void);
    void clientDisconnected(void);

private:
    QTcpServer* server;
    QTcpSocket* socket;
    QByteArray datagram;
};

#endif // TCPDOWNLOADER_H
