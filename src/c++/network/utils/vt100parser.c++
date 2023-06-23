#include "vt100parser.h"
#include <QtCore/QRegExp>

Networking::utils::vt100_result_t Networking::utils::parse_vt100_string(const QString& string)
{
  vt100_result_t ret;
  ret.result = string;

  return ret;
}
