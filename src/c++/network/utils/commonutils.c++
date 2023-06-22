#include "commonutils.h"

QString Networking::utils::host_to_string(const QString& ip_addr, const QString& port)
{
    return QString(ip_addr + ":" + port);
}

QString Networking::utils::host_to_string(const QString& ip_addr, uint16_t port)
{
    return QString(ip_addr + ":" + QString::number(port));
}
