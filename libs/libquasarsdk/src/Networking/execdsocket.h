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
      explicit ExecdSocket(bool compat_mode, QObject* parent = nullptr);
      void setCompatibility(bool);

      void execute(const QString& command) noexcept;
      void execute(Enums::NetworkCommand command) noexcept;

      void kill(int pid);
      void signalToProcess(int pid, Enums::UnixSignal signal);
      //void feedback
      void showQueue();
      void clearQueue();
      void popQueue();
      void ssh(const QString& command, const QString& host, const QString& password = QString());
      void isOccupied(int pid);

      [[nodiscard]] ExecdArgumentParser* parser() const;

    signals:
      void ping(); ///< Срабатывает, когда сокет получает ответ.

    private:
      Q_SLOT void process(QByteArray data);
      QByteArray wrap(const QString& string) noexcept;
      QString condition(const QString& condition, const QString& pass, const QString& fail) noexcept;

    private:
      ExecdArgumentParser* m_args;
      int m_message_uid;
      int m_strip_pid;
      bool m_compatibilityMode;
  };
} // QuasarSDK
