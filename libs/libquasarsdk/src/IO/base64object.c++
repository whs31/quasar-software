#include "base64object.h"
#include <utility>

namespace QuasarSDK::IO
{
  Base64Object::Base64Object()
    : m_data(QByteArray())
    , m_base64data(QByteArray())
  {}

  Base64Object::Base64Object(QByteArray data_array)
    : m_data(std::move(data_array))
    , m_base64data(toBase64(m_data))
  {}

  QString Base64Object::toBase64(const QByteArray& data_array) noexcept { return QString::fromLatin1(data_array.toBase64().data()); }

  QString Base64Object::base64() const { return m_base64data; }
  void Base64Object::setData(const QByteArray& non_b64_array) noexcept { m_base64data = toBase64(non_b64_array); }
} // QuasarSDK::IO