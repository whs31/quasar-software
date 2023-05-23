#include "execdsocket.h"
#include <QtCore/QDebug>
#include <LPVL/Crypto>

using namespace Network;

ExecdSocket::ExecdSocket(QObject* parent)
    : AbstractUDPSocket{parent}
{
    QObject::connect(this, &ExecdSocket::received, this, &ExecdSocket::processResult);
}

void ExecdSocket::start(const QString& address)
{
    this->connect(address);
    qDebug() << "[EXECD] Started socket";
}

void ExecdSocket::stop()
{
    this->disconnect();
    qDebug() << "[EXECD] Socket shutted down";
}

void ExecdSocket::executeCommand(const QString& command)
{
    if(this->state() == QAbstractSocket::UnconnectedState)
    {
        qWarning() << "[EXECD] Cannot execute command in unconnected state";
        return;
    }

    QByteArray wrapped = finalize(wrap(command));
    this->send(wrapped);
    qDebug().noquote() << "[EXECD] Sended command" << command; // << "as" << wrapped; @no longer needed because of imgui socket console
}

void ExecdSocket::executeCommand(Command command)
{

}

QString ExecdSocket::wrap(const QString& string)
{
    // prevents UID overflow
    if(message_uid == 9999)
        message_uid = 0;

    QString command = ":" + QStringLiteral("%1").arg(++message_uid, 4, 10, QLatin1Char('0')) + "|";
    QString hexlen = QString("%1").arg(string.length(), 2, 16, QLatin1Char('0'));
    command.append(hexlen + "|" + string + "|");
    command.append(QStringLiteral("%1").arg(LPVL::crc16(LPVL::str_data(command),
                                                             command.length()),
                                            4, 16, QLatin1Char('0')));
    return command;
}

QByteArray ExecdSocket::finalize(const QString& string)
{
    return string.toUtf8();
}

void ExecdSocket::processResult(QByteArray data)
{
    QString raw = data.data();
    QString check_crc = raw;
    check_crc.chop(5);

    //crc16
    uint16_t crc16 = LPVL::crc16(LPVL::str_data(check_crc), check_crc.length());
    uint16_t receivedCrc16 = raw.split("|").last().toUInt(nullptr, 16);

    if(crc16 == receivedCrc16)
        qDebug() << "[EXECD] Command executed successfully";
    else
        qWarning() << "[EXECD] Failed to execute command due to crc16 mismatch";

    if(receivedCrc16 != 0)
        emit ping();
}

