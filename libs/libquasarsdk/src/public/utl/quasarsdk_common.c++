#include "quasarsdk_common.h"

#include <limits>
#include <cmath>

namespace QuasarSDK::Utils
{
  /**
   * \brief Возвращает логарифм от числа по основанию.
   * \param base - основание логарифма.
   * \param value - число для взятия логарифма.
   * \return Логарифм от числа по основанию.
   */
  double log(double base, double value) noexcept { return (std::log(value) / std::log(base)); }

  /**
   * \brief Конвертирует значение в градусах в значение в радианах.
   * \param degrees - значение в градусах.
   * \return Значение в радианах.
   */
  double deg2rad(double degrees) noexcept { return degrees * (M_PI / 180); }

  /**
   * \brief Конвертирует значение в радианах в значение в градусах.
   * \param radians - значение в радианах.
   * \return Значение в градусах.
   */
  double rad2deg(double radians) noexcept { return radians * (180 / M_PI); }

  /**
   * \brief Возвращает *NaN*.
   * \return *NaN*.
   */
  double NaN() noexcept { return std::numeric_limits<double>::quiet_NaN(); }

  /**
   * \brief Проверяет, является ли число *NaN*.
   * \param other - число для проверки.
   * \return \c true, если число - *NaN*.
   */
  bool isNaN(double other) noexcept { return std::isnan(other); }
} // QuasarSDK::Utils