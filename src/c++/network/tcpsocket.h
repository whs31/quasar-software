#pragma once

#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;
class QTimer;

namespace Networking
{
    class TCPSocket : public QObject
    {
        Q_OBJECT

        constexpr static uint32_t TCP_TIMEOUT = 10'000;

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
                void receivingFinished();
                void progressChanged(float progress);
                void socketMetrics(const QString& data, int size_bytes, bool out);

        private:
            void (TCPSocket::*readFile)(QByteArray data);
            void readFileInfo(QByteArray data);
            void readFileBody(QByteArray data);

        private:
            QTcpServer* server;
            QTcpSocket* socket;
            QTimer* timer;
            QByteArray imageData;

            bool success = false;
            uint8_t splitIndex = 0;
            uint32_t fileSize = 0;
            QString filename;
    };
} // namespace Network;
