#ifndef SCHECKSUM_H
#define SCHECKSUM_H

#include <QObject>

class SChecksum : public QObject
{
    Q_OBJECT
public:
    explicit SChecksum(QObject *parent = nullptr);

    static uint16_t calculateCRC16(char* buffer, int length);
    static char* toCharPointer(QString string);

signals:

};

#endif // SCHECKSUM_H
