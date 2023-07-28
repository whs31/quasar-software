/**
 *  \file CExecdSocket.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <array>
#include "baseudpsocket.h"
#include "network_enums.h"

using std::array;

namespace QuasarSDK
{
  class ExecdArgumentParser;
  class ExecdSocket : public BaseUDPSocket
  {
    Q_OBJECT

    public:
      explicit ExecdSocket(bool compat_mode, QObject* parent = nullptr);
      void setRemoteAddressList(const array<QString, 2>& list) noexcept;
      void setCompatibility(bool);

      [[nodiscard]] ExecdArgumentParser* parser() const;
      Q_INVOKABLE [[nodiscard]] QString argument(const QString& key, QuasarSDK::Enums::ArgumentCategory category) noexcept;
      Q_INVOKABLE void setArgument(const QString& key, const QVariant& value, QuasarSDK::Enums::ArgumentCategory category) noexcept;

      Q_INVOKABLE void executeString(const QString& command) noexcept;
      Q_INVOKABLE void execute(QuasarSDK::Enums::NetworkCommand command) noexcept;
      Q_INVOKABLE QString prepareCommand(QuasarSDK::Enums::NetworkCommand command) noexcept;

      Q_INVOKABLE void kill(int pid);
      Q_INVOKABLE void signalToProcess(int pid, Enums::UnixSignal signal);
      //void feedback
      Q_INVOKABLE void showQueue();
      Q_INVOKABLE void clearQueue();
      Q_INVOKABLE void popQueue();
      void ssh(const QString& command, const QString& host, const QString& password = QString());
      void isOccupied(int pid);

    signals:
      void ping(); ///< Срабатывает, когда сокет получает ответ.

    private:
      Q_SLOT void process(QByteArray data);
      QString condition(const QString& condition, const QString& pass, const QString& fail) noexcept;

    private:
      ExecdArgumentParser* m_args;
      int m_message_uid;
      int m_strip_pid;
      array<QString, 2> m_remote_address_list;
      bool m_compatibilityMode;
  };
} // QuasarSDK

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::ExecdSocket*)