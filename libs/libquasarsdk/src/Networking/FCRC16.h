/**
 *  \file FCRC16.h
 *  \author Дмитрий Рязанцев
 *  \date 04.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <cstdint>

class QString;

namespace QuasarSDK::Utils
{
  uint16_t crc16(char* data, int size) noexcept;
  uint16_t crc16_ccitt(const char* data, int size) noexcept;
  char* str_data(const QString& str) noexcept;
} // QuasarSDK::Utils
