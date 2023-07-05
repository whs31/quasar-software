/**
 *  \file tcpsocket.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;
class QTimer;

namespace Networking
{
  /**
   * \brief Class for receiving large files from SAR via TCP.
   * \details Class is used to receive images and .zip archives
   * from SAR using TCP protocol.
   *
   * This class automatically invokes function from #Filesystem
   * to scan TCP cache.
   *
   * Provides debug metrics.
   * \extends QObject
   */
  class TCPSocket : public QObject
  {
    Q_OBJECT

    constexpr static uint32_t TCP_TIMEOUT = 10'000; // @FIXME to ICFG

    public:
      /// \brief Constructs new TCPSocket with given parent.
      explicit TCPSocket(QObject* parent = nullptr);

      /**
        * \brief Starts socket on given address.
        * \details Binds socket to address. Address must be in
        * string format with IPv4 and port joined by colon (e.g.
        * <tt>192.168.1.47:9955<tt>.
        * \param address - string address to bind.
        */
      void startServer(const QString& address);

      /// \brief Stops socket.
      void stopServer();

      //! @brief Provides loading progress value.
      //! @details Range - 0 to 100.
      /**
       * \brief Provides current loading progress value.
       * \return Progress in range from 0 to 100.
       */
      float progress();

    signals:
      /// @brief Emitted when receiving of data is finished.
      void receivingFinished();

      /// @brief Emitted on loading progress change.
      void progressChanged(float progress);

      /// @brief Debug socket metrics.
      void socketMetrics(const QString& data, int size_bytes, bool out);

    private:
      void (TCPSocket::*readFile)(QByteArray data);
      void readFileInfo(QByteArray data);
      void readFileBody(QByteArray data);

    private slots:
      void clientConnected();
      void serverRead();
      void clientDisconnected();
      void connectionTimeout();

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
