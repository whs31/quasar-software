#include "utils.h++"
#include <QtCore/QString>
#include <cmath>

uint16_t Utilities::crc16(char* data, size_t size) noexcept(true)
{
    uint16_t crc = 0xFFFF;
    for(size_t i = 0; i < size; i++)
    {
        crc ^= (uint16_t)data[i];
        for(size_t j = 0; j < 8; j++)
        {
            if((crc & 0x0001))
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
                crc >>= 1;
        }
    }

    return crc;
}

char* Utilities::stringToCharPointer(const QString& string) noexcept(true)
{
    return string.toLocal8Bit().data();
}

double Utilities::log(double base, double exponent) noexcept(true)
{
    return (std::log(exponent) / std::log(base));
}
