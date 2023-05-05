#pragma once

#include <Definitions>
#include <cstdint>

class QString;

//! @namespace Пространство имен для утилит и полезных алгоритмов.
namespace Utilities
{
    uint32_t ipAddressToHex(const QString& ip_address);
} // namespace Utilities;
