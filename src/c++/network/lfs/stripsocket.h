#pragma once

#include "network/base/udpsocketbase.h"

namespace Networking
{
  class StripSocket : public UDPSocketBase
  {
    Q_OBJECT

    public:
      explicit StripSocket(QObject* parent = nullptr);

      void start(const QString& address);
      void stop();

    private slots:
      void processResult(const QByteArray& data);
  };
} // namespace Network;
