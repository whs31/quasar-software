#pragma once

#include "network/base/abstractudpsocket.h"

namespace Networking
{
  class StripSocket : public AbstractUDPSocket
  {
    Q_OBJECT

    public:
      explicit StripSocket(QObject* parent = nullptr);

      void start(const QString& address);
      void stop();

      void setStripStatus(bool status) noexcept;

    signals:
      void textReceived(QByteArray text);
      void diskSpaceReceived(long free, long total);

    private:
    private slots:
      void processResult(QByteArray data);

    private:
      bool m_stripstatus;
  };
} // namespace Network;
