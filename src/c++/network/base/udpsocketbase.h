/*!
 *  \file udpsocketbase.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>

namespace Networking
{
  /*!
   * \brief Base class for handling UDP connections.
   * \extends QUdpSocket
   * \details Class provides useful extensions over
   * QUdpSocket methods, such as abstraction from
   * QHostAddress/port, and much more.
   * Socket provides in/out metrics in text format via
   * signal #socketMetrics().
   */
  class UDPSocketBase : public QUdpSocket
  {
    Q_OBJECT

    public:
      //! \brief Constructs new UDP socket with specified parent.
      explicit UDPSocketBase(QObject* parent = nullptr);
      ~UDPSocketBase() override;

      /*!
       * \brief Binds this socket to specified address.
       * \param address - address to connect (e.g. <tt>192.168.1.47:25565<tt>).
       * \return Operation result.
       * \note Can be invoked from QML via meta-object system.
       */
      Q_INVOKABLE virtual bool connect(const QString& address);

      /*!
       * \brief Returns socket to unconnected state.
       * \note Can be invoked from QML via meta-object system.
       */
      Q_INVOKABLE virtual void disconnect();

      //! \brief Sends given \c QByteArray to socket.
      virtual bool send(QByteArray data);

      //! \brief Returns current socket port.
      [[nodiscard]] virtual uint16_t port() const noexcept;

    signals:
      /*!
       * \brief Signal with received data.
       * \details Emitted when socket receives data via UDP.
       * Data is provided in raw format without any changes.
       */
      void received(QByteArray data);

      //! @brief Emitted when socket breaks connection.
      void socketDisconnected();

      /*!
       * \brief Signal with debug socket metrics.
       * \details Emitted when socket receives or sends data via UDP.
       * Data is provided in string format with direction and size.
       * \param data - stringified data.
       * \param size_bytes - size of data.
       * \param out - flow direction of data: \c true means data is
       * flowing from host to remote, \c false means data is flowing
       * from remote to host.
       */
      void socketMetrics(const QString& data, int size_bytes, bool out);

    private slots:
      virtual void readSocket();

    private:
      QHostAddress m_hostaddress;
      uint16_t m_port = 0;
  };
} // namespace Network;
