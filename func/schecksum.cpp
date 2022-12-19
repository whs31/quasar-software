#include "schecksum.h"

SChecksum::SChecksum(QObject *parent)
    : QObject{parent}
{}

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
            else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

char* SChecksum::toCharPointer(QString string) { return string.toLocal8Bit().data(); }
