#include "execdsocket.h++"
#include "utils/utils.h++"
#include <QtCore/QDebug>

using namespace Network;

ExecdSocket::ExecdSocket(QObject* parent)
    : AbstractUDPSocket{parent}
{
    QObject::connect(this, &ExecdSocket::received, this, &ExecdSocket::processResult);
}

void ExecdSocket::start(const QString &address)
{
    this->connect(address);
    qDebug() << "[EXECD] Started socket";
}

void ExecdSocket::stop()
{
    this->disconnect();
    qDebug() << "[EXECD] Socket shutted down";
}

void ExecdSocket::processResult(QByteArray data)
{
    QString rawString = data.data();
    QString checkCrc = rawString;
    checkCrc.chop(5);

    //crc16
    uint16_t crc16 = Utilities::crc16(Utilities::stringToCharPointer(checkCrc), checkCrc.length());
    uint16_t receivedCrc16 = rawString.split("|").last().toUInt(nullptr, 16);

    if(crc16 == receivedCrc16)
        qDebug() << "[EXECD] Command executed successfully";
    else
        qWarning() << "[EXECD] Failed to execute command due to crc16 mismatch";
}

