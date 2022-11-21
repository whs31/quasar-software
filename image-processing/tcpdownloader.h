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
    void newConnection();

private:
    QTcpServer* server;
};

#endif // TCPDOWNLOADER_H
