#pragma once

#include "network/base/abstractudpsocket.h"

namespace Networking
{
  class StripSocket : public UDPSocketBase
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
      void saveResult(const QString& path, const QByteArray& data) noexcept;

    private slots:
      void processResult(QByteArray data);

    private:
      uint32_t m_currentindex;
      QByteArray m_storeddata;
      bool m_stripstatus;
  };
} // namespace Network;
