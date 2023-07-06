/**
 *  \file quasarsdk_execdsocket.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "private/quasarsdk_baseudpsocket.h"
#include "public/quasarsdk_enums.h"

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

      [[nodiscard]] ExecdArgumentParser* parser() const;

    signals:
      void ping(); ///< Срабатывает, когда сокет получает ответ.

    private:
      Q_SLOT void process(QByteArray data);
      QByteArray wrap(const QString& string) noexcept;

    private:
      ExecdArgumentParser* m_args;
      int m_message_uid;
  };
} // QuasarSDK
