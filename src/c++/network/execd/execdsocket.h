/**
 *  \file execdsocket.h
 *  \author Dmitry Ryazancev
 *  \date 30.06.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "network/base/udpsocketbase.h"
#include "network/netenums.h"

namespace Networking
{
  class ExecdArgumentList;

  /**
   * \brief Class for \c execd service interactions.
   * \details Provides useful interface for sending
   * commands to SAR and receiving execution result.
   * Internally uses #ExecdArgumentList for handling
   * state of \c execd service arguments.
   * Provides debug metrics.
   * \see ExecdArgumentList
   * \extends UDPSocketBase
   */
  class ExecdSocket : public UDPSocketBase
  {
    Q_OBJECT

    public:
      /// \brief Constructs new ExecdSocket with given parent.
      explicit ExecdSocket(QObject* parent = nullptr);

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

      /**
       * \brief Executes any command in \c execd service.
       * \details Tries to execute any string command in service.
       * If command is incorrect, function does nothing. Function
       * does not add any arguments to string command, expecting for
       * string to contain needed arguments.
       * \param command - string command to execute.
       */
      void executeCommand(const QString& command);

      /**
       * \brief Executes built-in command in \c execd service.
       * \details Tries to execute given command in service.
       * If command is incorrect, function does nothing. Function
       * automatically adds needed arguments, if type suggests so.
       * \param command - command to execute.
       * \see Enums::NetworkCommand
       */
      void executeCommand(Enums::NetworkCommand command);
      ExecdArgumentList* list() const noexcept;

    signals:
      /// \brief Emitted when socket receives any data from SAR.
      void ping();

    private:
      /**
       * \brief Wraps given string to \c execd format.
       * \details Prepends unique ID, hexadecimal length
       * and CRC16 to given string, separated by symbol \c |.
       * \param string - string to wrap.
       * \note This is private function.
       * \return UTF-8 data to send.
       */
      QByteArray wrap(const QString& string);

    private slots:
      void processResult(QByteArray data);

    private:
      ExecdArgumentList* args;
      uint16_t message_uid;
  };
}
