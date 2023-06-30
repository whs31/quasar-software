/**
 *  \file feedbacksocket.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "network/base/udpsocketbase.h"

namespace Networking
{
  /**
   * \brief Class for receiving feedback from SAR.
   * \details Class is used to receive \c stdout
   * and \c stderr output from SAR, redirected from
   * \c execd service.
   *
   * Output can contain VT100 escape sequences, which
   * needs to be parsed.
   *
   * Class automatically parse predefined string sequences
   * (e.g. free storage space status) and emits signal respectively.
   *
   * Provides debug metrics.
   * \extends UDPSocketBase
   */
  class FeedbackSocket : public UDPSocketBase
  {
    Q_OBJECT

    public:
      /// \brief Constructs new FeedbackSocket object with given parent.
      explicit FeedbackSocket(QObject* parent = nullptr);

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

    signals:
      /**
       * \brief Emitted when socket receives raw text.
       * \details Text is encoded in UTF-8 and can contain
       * ANSI VT100 escape sequences.
       * \param text - raw received data.
       */
      void textReceived(QByteArray text);

      /**
       * \brief Emitted when socket receives remote storage space status.
       * \param free - free bytes in storage.
       * \param total - total bytes in storage.
       */
      void diskSpaceReceived(long free, long total);

    private slots:
      void processResult(QByteArray data);
  };
} // namespace Network;
