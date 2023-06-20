#pragma once

#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>

//! @namespace Namespace network-related classes.
namespace Networking
{
    //! @class Class, which serves as base for all
    //!        UDP sockets.
    //! @extends QUdpSocket.
    class AbstractUDPSocket : public QUdpSocket
    {
        Q_OBJECT

        public:
            explicit AbstractUDPSocket(QObject* parent = nullptr);
            virtual ~AbstractUDPSocket();

            //! @brief   Connects to given IPv4 address and port.
            //! @param   address - IPv4 address with port.
            //! @example connect("192.168.1.151:25565);
            //! @details Can be invoked from QML.
            Q_INVOKABLE virtual bool connect(const QString& address);

            //! @brief   Disconnects from current session.
            //! @details Can be invoked from QML.
            Q_INVOKABLE virtual void disconnect();

            //! @brief Sends given QByteArray to socket.
            virtual bool send(QByteArray data);

            //! @brief Returns current socket port.
            virtual uint16_t port() const noexcept;

            signals:
                //! @brief Emits when socket receives data from other side.
                //! @param data - received QByteArray.
                void received(QByteArray data);

                //! @brief Emits when socket breaks connection.
                void socketDisconnected();

                //! @brief Emits when socket sends or receives data.
                //! @param data - stringified data, which passes through socket.
                //! @param size_bytes - size of data.
                //! @param out - flow direction of data.
                void socketMetrics(const QString& data, int size_bytes, bool out);

        private:
            private slots:
                virtual void readSocket();

        private:
            QHostAddress m_hostaddress;
            uint16_t m_port = 0;
    };
} // namespace Network;
