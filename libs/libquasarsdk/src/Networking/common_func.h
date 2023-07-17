/**
 *  \file FCommon.h
 *  \author Дмитрий Рязанцев
 *  \date 04.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

namespace QuasarSDK::Utils
{
  double log(double base, double value) noexcept;

  double deg2rad(double degrees) noexcept;
  double rad2deg(double radians) noexcept;

  double NaN() noexcept;
  bool isNaN(double other) noexcept;
} // QuasarSDK::Utils
