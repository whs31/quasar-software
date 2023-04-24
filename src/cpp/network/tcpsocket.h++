#pragma once

#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;

namespace Network
{
    class TCPSocket : public QObject
    {
        Q_OBJECT


        public:
            explicit TCPSocket(QObject *parent = nullptr);

            signals:

    };
} // namespace Network;
