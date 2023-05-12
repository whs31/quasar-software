#pragma once

#include <Definitions>
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

            __exposed virtual bool connect(const QString& address);
            __exposed virtual void disconnect();

            virtual bool send(QByteArray data);
            virtual uint16_t port() { return m_port; }

            signals:
                __signal received(QByteArray data);
                __signal socketDisconnected();
                __signal socketMetrics(const QString& data, int size_bytes);

        private:
            private slots:
                virtual void readSocket();

        private:
            QHostAddress m_hostaddress;
            uint16_t m_port = 0;
    };
} // namespace Network;
