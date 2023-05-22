#include "lpvlmath.h"

#include <QtCore/QDebug>
#include <limits>
#include <cmath>

namespace LPVL
{

__attribute__((constructor)) static void describe() { qInfo() << "LPVL version 220523dev loaded."; }

double log(double base, double value) noexcept { return (std::log(value) / std::log(base)); }
double deg2rad(double degrees) noexcept { return degrees * (M_PI / 180); }
double rad2deg(double radians) noexcept { return radians * (180 / M_PI); }

double NaN() noexcept { return std::numeric_limits<double>::quiet_NaN(); }
bool isNaN(double other) noexcept { return std::isnan(other); }

} // LPVL
