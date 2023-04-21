#pragma once

#include <definitions.h++>
#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>

namespace Network
{
    class AbstractUDPSocket : public QUdpSocket
    {
        Q_OBJECT

        public:
            explicit AbstractUDPSocket(QObject *parent = nullptr);
            virtual ~AbstractUDPSocket();

            __qml virtual bool connect(const QString& address);
            __qml virtual void disconnect();
            virtual bool send(QByteArray data);
            virtual uint16_t port() { return m_port; }

            signals:
                __signal received(QByteArray data);
                __signal socketDisconnected();

        private:
            QHostAddress m_hostaddress;
            uint16_t m_port = 0;

            private slots:
                virtual void readSocket();

    };
} // namespace Network;
