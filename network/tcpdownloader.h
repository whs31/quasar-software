#ifndef TCPDOWNLOADER_H
#define TCPDOWNLOADER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include "imagemanager.h"


#include <QPixmap>
#include <QCoreApplication>

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

    QString filename;
    QByteArray imageData;
    bool fnameCheck = false;
    bool success = false;
    ImageManager* manager;
};

#endif // TCPDOWNLOADER_H
