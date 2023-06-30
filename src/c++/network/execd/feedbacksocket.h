#pragma once

#include "network/base/udpsocketbase.h"

namespace Networking
{
  class FeedbackSocket : public UDPSocketBase
  {
    Q_OBJECT

    public:
      explicit FeedbackSocket(QObject* parent = nullptr);

      void start(const QString& address);
      void stop();

    signals:
      void textReceived(QByteArray text);
      void diskSpaceReceived(long free, long total);

    private:
    private slots:
      void processResult(QByteArray data);
  };
} // namespace Network;
