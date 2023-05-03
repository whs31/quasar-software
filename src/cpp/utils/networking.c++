#include "networking.h++"
#include <QtCore/QString>
#include <QtCore/QDebug>

using namespace Utilities;

uint32_t ipAddressToHex(const QString& ip_address)
{
    if(not ip_address.contains(".")) {
        qWarning() << "[UTILITIES] Error in converting ip address to uint32_t: no dot symbol detected";
        return 0x0;
    }

    if(ip_address.split('.').size() != 4) {
        qWarning() << "[UTILITIES] Error in converting ip address to uint32_t: address cannot be split into 4 separate bytes";
        return 0x0;
    }

    uint8_t ch1 = ip_address.split('.').at(0).toUInt();
    uint8_t ch2 = ip_address.split('.').at(1).toUInt();
    uint8_t ch3 = ip_address.split('.').at(2).toUInt();
    uint8_t ch4 = ip_address.split('.').at(3).toUInt();

    uint32_t ret = ch4 | (ch3 << 8) | (ch2 << 16) | (ch1 << 24);
    #ifdef QT_DEBUG
        qDebug().noquote() << "[UTILITIES] Converted" << ip_address << "to" << Qt::hex << ret << Qt::dec;
    #endif
    return ret;
}
