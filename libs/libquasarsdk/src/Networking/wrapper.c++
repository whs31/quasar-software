//
// Created by whs31 on 27.07.23.
//

#include "wrapper.h"
#include "crc16.h"

namespace QuasarSDK::Utils
{
  QByteArray wrapToExecdString(const QString& string, int* uid_counter) noexcept
  {
    QString ret;
    if(uid_counter != nullptr)
    {
      // prevents UID overflow
      if(*uid_counter >= 0xFFFF)
        *uid_counter = 0;

      ret = ":" + QStringLiteral("%1").arg(++*uid_counter, 4, 16, QLatin1Char('0')) + "|";
      QString hex_length = QString("%1").arg(string.length(), 2, 16, QLatin1Char('0'));
      ret.append(hex_length + "|" + string + "|");
      ret.append(QStringLiteral("%1").arg(Utils::crc16(Utils::str_data(ret), ret.length()),
                                              4, 16, QLatin1Char('0')));
    }
    else
    {
      ret = ":" + QStringLiteral("%1").arg(1, 4, 10, QLatin1Char('0')) + "|";
      QString hex_length = QString("%1").arg(string.length(), 2, 16, QLatin1Char('0'));
      ret.append(hex_length + "|" + string + "|");
      ret.append(QStringLiteral("%1").arg(Utils::crc16(Utils::str_data(ret), ret.length()),
                                              4, 16, QLatin1Char('0')));
    }
    return ret.toUtf8();
  }
} // QuasarSDK::Utils