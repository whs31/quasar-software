#ifndef TCPDOWNLOADER_H
#define TCPDOWNLOADER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include "imagemanager.h"
#include "sconfig.h"

enum DowloaderMode : short int
{
    NoSave,
    SaveContinuous,
    SaveAtDisconnect
};

class TCPDownloader : public QObject
{
    Q_OBJECT
public:
    explicit TCPDownloader(QObject *parent = nullptr, DowloaderMode mode = SaveAtDisconnect);


signals:
    void receivingFinished();

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
    uint8_t splitIndex;
    ImageManager* manager;
    short int _mode;
};

#endif // TCPDOWNLOADER_H
