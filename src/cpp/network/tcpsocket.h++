#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;
class QTimer;

namespace Network
{
    class TCPSocket : public QObject
    {
        Q_OBJECT

        constexpr __global uint32_t TCP_TIMEOUT = 10'000;

        QTcpServer* server;
        QTcpSocket* socket;
        QTimer* timer;
        QByteArray imageData;

        bool success = false;
        uint8_t splitIndex = 0;
        uint32_t fileSize = 0;
        QString filename;

        public:
            explicit TCPSocket(QObject* parent = nullptr);

            void startServer(const QString& address);
            void stopServer();

            float progress();
            QByteArray imageData64;

            public slots:
                void clientConnected(void);
                void serverRead(void);
                void clientDisconnected(void);
                void connectionTimeout(void);

            signals:
                __signal receivingFinished();
                __signal progressChanged(float progress);

        private:
            void (TCPSocket::*readFile)(QByteArray data);
            void readFileInfo(QByteArray data);
            void readFileBody(QByteArray data);

    };
} // namespace Network;
