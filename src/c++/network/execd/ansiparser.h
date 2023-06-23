#pragma once
#include <QtCore/QString>

namespace Networking
{

  class ANSIParser
  {
    public:
      explicit ANSIParser(QByteArray source);

      [[nodiscard]] QString result() noexcept; // mb struct(string, int, int) for carriage movement \r, \e
  };

} // Networking
