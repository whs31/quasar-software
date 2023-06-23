#pragma once

#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>

namespace Networking
{
  //! @brief Class, which serves as base for all
  //!        UDP sockets.
  class AbstractUDPSocket : public QUdpSocket
  {
    Q_OBJECT

    public:
      explicit AbstractUDPSocket(QObject* parent = nullptr);
      ~AbstractUDPSocket() override;

      //! @brief   Connects to given IPv4 address and port.
      //! @param   address - IPv4 address with port.
      //! @note Can be invoked from QML.
      Q_INVOKABLE virtual bool connect(const QString& address);

      //! @brief   Disconnects from current session.
      //! @note Can be invoked from QML.
      Q_INVOKABLE virtual void disconnect();

      //! @brief Sends given QByteArray to socket.
      virtual bool send(QByteArray data);

      //! @brief Returns current socket port.
      [[nodiscard]] virtual uint16_t port() const noexcept;

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
