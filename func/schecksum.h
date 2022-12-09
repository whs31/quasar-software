#ifndef SCHECKSUM_H
#define SCHECKSUM_H

#include <QObject>

class SChecksum : public QObject
{
    Q_OBJECT
public:
    explicit SChecksum(QObject *parent = nullptr);

    static uint32_t calculateChecksum(const void* data, size_t length, uint32_t previousCrc32 = 0);
    static uint16_t calculateCRC16(char* buffer, int length);

signals:

};

#endif // SCHECKSUM_H
