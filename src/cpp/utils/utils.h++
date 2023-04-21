#pragma once

#include <cstdint>

class QString;

namespace Utilities
{
    uint16_t crc16(char* data, size_t size) noexcept(true);
    char* stringToCharPointer(const QString& string) noexcept(true);
    double log(double base, double exponent) noexcept(true);
} // namespace Network;

