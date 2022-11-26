#ifndef TCPDOWNLOADER_H
#define TCPDOWNLOADER_H

#define TCP_TIMEOUT 5000

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QTimer>
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

    float progress();
    QByteArray imageData64;


signals:
    void receivingFinished();
    void progressChanged(float progress);

 public slots:
    void clientConnected(void);
    void serverRead(void);
    void clientDisconnected(void);
    void connectionTimeout(void);

private:
    QTcpServer* server;
    QTcpSocket* socket;
    QByteArray imageData;
    QTimer* timer;
    bool success = false;
    uint8_t splitIndex;
    ImageManager* manager;
    short int _mode;

    uint32_t fileSize;
    QString filename;

    void (TCPDownloader::*readFile)(QByteArray data);
    void readFileInfo(QByteArray data);
    void readFileBody(QByteArray data);
};

#endif // TCPDOWNLOADER_H
