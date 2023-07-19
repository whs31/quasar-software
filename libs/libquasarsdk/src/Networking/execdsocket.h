/**
 *  \file CExecdSocket.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "baseudpsocket.h"
#include "network_enums.h"

namespace QuasarSDK
{
  class ExecdArgumentParser;
  class ExecdSocket : public BaseUDPSocket
  {
    Q_OBJECT

    public:
      explicit ExecdSocket(QObject* parent = nullptr);

      void execute(const QString& command) noexcept;
      void execute(Enums::NetworkCommand command) noexcept;
      void signalToProcess(int pid, Enums::UnixSignal signal);

      [[nodiscard]] ExecdArgumentParser* parser() const;

    signals:
      void ping(); ///< Срабатывает, когда сокет получает ответ.

    private:
      Q_SLOT void process(QByteArray data);
      QByteArray wrap(const QString& string) noexcept;

    private:
      ExecdArgumentParser* m_args;
      int m_message_uid;
      int m_strip_pid;
  };
} // QuasarSDK
