#pragma once

#include "network/base/abstractudpsocket.h"
#include "network/netenums.h"

namespace Networking
{
  class ExecdArgumentList;
  class ExecdSocket : public UDPSocketBase
  {
    Q_OBJECT

    public:
      explicit ExecdSocket(QObject* parent = nullptr);

      void start(const QString& address);
      void stop();
      void executeCommand(const QString& command);
      void executeCommand(Enums::NetworkCommand command);
      ExecdArgumentList* list() const noexcept;

    signals:
      void ping();

    private:
      QString wrap(const QString& string);
      QByteArray finalize(const QString& string);

    private slots:
      void processResult(QByteArray data);

    private:
      ExecdArgumentList* args;
      uint16_t message_uid;
  };
}
