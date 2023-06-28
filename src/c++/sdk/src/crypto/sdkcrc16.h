#pragma once

#include <cstdint>

class QString;

namespace SDK::Crypto
{
  uint16_t crc16(char* data, int size) noexcept;
  uint16_t crc16_ccitt(const char* data, int size) noexcept;
  uint16_t crc16_alt(const char *data, uint16_t size) noexcept;
  char* str_data(const QString& str) noexcept;
} // SDK::Crypto