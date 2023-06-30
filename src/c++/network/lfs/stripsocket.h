/**
 *  \file stripsocket.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "network/base/udpsocketbase.h"

namespace Networking
{
  /**
   * \brief Class for receiving large files from SAR via UDP.
   * \details Class is used to receive images (mainly strip)
   * from SAR using UDP protocol.
   *
   * This class automatically invokes #Processing::ImageProcessing::processChunk()
   * function on every received packet of data.
   *
   * Provides debug metrics.
   * \extends UDPSocketBase
   */
  class StripSocket : public UDPSocketBase
  {
    Q_OBJECT

    public:
      /// \brief Constructs new StripSocket with given parent.
      explicit StripSocket(QObject* parent = nullptr);

      /**
        * \brief Starts socket on given address.
        * \details Binds socket to address. Address must be in
        * string format with IPv4 and port joined by colon (e.g.
        * <tt>192.168.1.47:9955<tt>.
        * \param address - string address to bind.
        */
      void start(const QString& address);

      /// \brief Stops socket.
      void stop();

    private slots:
      void processResult(const QByteArray& data);
  };
} // namespace Network;
