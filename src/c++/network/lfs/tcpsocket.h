#pragma once

#include <QtCore/QObject>

class QTcpServer;
class QTcpSocket;
class QTimer;

namespace Networking
{
  //! @brief TCP-IP LFS data socket.
  class TCPSocket : public QObject
  {
    Q_OBJECT

      constexpr static uint32_t TCP_TIMEOUT = 10'000; // @FIXME to ICFG

    public:
      //! @brief Constructs a new TCPSocket object with
      //!        given parent.
      explicit TCPSocket(QObject* parent = nullptr);

      //! @brief Starts TCP-IP server at given
      //!        IPv4 address and port.
      void startServer(const QString& address);

      //! @brief Stops currently working TCP-IP server.
      void stopServer();

      //! @brief Provides loading progress value.
      //! @details Range - 0 to 100.
      float progress();

    signals:
      //! @brief Emitted when receiving of data is finished.
      void receivingFinished();

      //! @brief Emitted on loading progress change.
      void progressChanged(float progress);

      //! @brief Debug socket metrics.
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
