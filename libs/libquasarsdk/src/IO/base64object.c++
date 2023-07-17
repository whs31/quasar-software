#include "base64object.h"
#include <utility>

namespace QuasarSDK::IO
{
  Base64Object::Base64Object()
    : data(QByteArray())
  {}

  Base64Object::Base64Object(QByteArray data_array)
    : data(std::move(data_array))
  {}

  QString Base64Object::toBase64() const noexcept { return toBase64(data); }
  QString Base64Object::toBase64(const QByteArray& data_array) noexcept { return QString::fromLatin1(data_array.toBase64().data()); }
} // QuasarSDK::IO