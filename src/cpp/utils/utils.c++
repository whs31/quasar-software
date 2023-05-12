#include "utils.h++"
#include <QtCore/QString>
#include <cmath>

uint16_t Utilities::crc16(char* data, int size) noexcept
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

char* Utilities::stringToCharPointer(const QString& string) noexcept
{
    return string.toLocal8Bit().data();
}

double Utilities::log(double base, double value) noexcept
{
    return (std::log(value) / std::log(base));
}

uint16_t Utilities::crc16_ccitt(const char* data, int size)
{
    const unsigned char* udata = reinterpret_cast<const unsigned char*>(data);
    uint16_t crc = 0xFFFF;
    while(size--)
        crc = (crc << 8) ^ CRC16_TABLE[(crc >> 8) ^* data++];

    return crc;
}

int Utilities::randomInRange(int range_min, int range_max)
{
    return range_min + (std::rand() % (range_max - range_min + 1));
}
