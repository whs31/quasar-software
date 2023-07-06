#pragma once

#include <QtCore/QString>

namespace Networking
{
  namespace utils
  {
    QString host_to_string(const QString& ip_addr, const QString& port);
    QString host_to_string(const QString& ip_addr, uint16_t port);
  } // utils
} // Network
