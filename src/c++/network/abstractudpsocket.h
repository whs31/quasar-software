#pragma once

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

            Q_INVOKABLE virtual bool connect(const QString& address);
            Q_INVOKABLE virtual void disconnect();

            virtual bool send(QByteArray data);
            virtual uint16_t port() { return m_port; }

            signals:
                void received(QByteArray data);
                void socketDisconnected();
                void socketMetrics(const QString& data, int size_bytes, bool out);

        private:
            private slots:
                virtual void readSocket();

        private:
            QHostAddress m_hostaddress;
            uint16_t m_port = 0;
    };
} // namespace Network;
