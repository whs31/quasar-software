#pragma once

namespace SDK
{
  double log(double base, double value) noexcept;

  double deg2rad(double degrees) noexcept;
  double rad2deg(double radians) noexcept;

  double NaN() noexcept;
  bool isNaN(double other) noexcept;
} // SDK