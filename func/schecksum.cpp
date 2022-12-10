#include "schecksum.h"

SChecksum::SChecksum(QObject *parent)
    : QObject{parent}
{

}

uint32_t SChecksum::calculateChecksum(const void* data, size_t length, uint32_t previousCrc32)
{
    const uint32_t Polynomial = 0xEDB88320;
    uint32_t crc = ~previousCrc32;
    unsigned char* current = (unsigned char*) data;
    while (length--)
    {
        crc ^= *current++;
        for (unsigned int j = 0; j < 8; j++)
            crc = (crc >> 1) ^ (-int(crc & 1) & Polynomial);
    }
    return ~crc;
}

uint16_t SChecksum::calculateCRC16(char* buffer, int length)
{
    uint16_t crc = 0xFFFF;
    for (int pos = 0; pos < length; pos++) {
        crc ^= (uint16_t)buffer[pos];
        for (int i = 0; i < 8; i++) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else{
                crc >>= 1;
            }
        }
    }
    return crc;
}

char* SChecksum::toCharPointer(QString string)
{
    QByteArray localarray = string.toLocal8Bit();
    char* localdata = localarray.data();
    return localdata;
}
