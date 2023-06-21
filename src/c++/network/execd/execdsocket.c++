#include "execdsocket.h"
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <LPVL/Crypto>
#include "config/paths.h"
#include "execdargumentlist.h"

using namespace Networking;

ExecdSocket::ExecdSocket(QObject* parent)
    : AbstractUDPSocket{parent}
    , args(new ExecdArgumentList(this))
    , message_uid(0)
{
    QObject::connect(this, &ExecdSocket::received, this, &ExecdSocket::processResult, Qt::DirectConnection);
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
    auto com = finalize(wrap(command));
    this->send(com);
    qDebug().noquote() << "[EXECD] Sended string command";
    emit socketMetrics(com, com.length(), true);
}

void ExecdSocket::executeCommand(Enums::NetworkCommand command)
{
    QByteArray com;

    switch (command)
    {
        case Enums::FormImage:
            com = finalize(wrap(COMMAND_TELESCOPIC+ args->getFormArguments()));
            break;
        case Enums::FocusImage:
            com = finalize(wrap(COMMAND_FOCUS + args->getFocusArguments()));
            break;
        case Enums::ReformImage:
            com = finalize(wrap(COMMAND_TELESCOPIC + args->getReformArguments()));
            break;
        case Enums::RemoteStorageStatus:
            com = finalize(wrap(COMMAND_STORAGE_STATUS));
            break;
        case Enums::ClearRemoteStorage:
            com = finalize(wrap(COMMAND_CLEAR_STORAGE));
            break;
        case Enums::Reboot:
        {
            QFile str(Config::Paths::bash() + "/reboot.sh");
            if(str.open(QFile::ReadOnly))
            {
                QString content = str.readAll();
                com = finalize(wrap(content));
            }
            break;
        }
        case Enums::Poweroff:
        {
            QFile str(Config::Paths::bash() + "/poweroff.sh");
            if(str.open(QFile::ReadOnly))
            {
                QString content = str.readAll();
                com = finalize(wrap(content));
            }
            break;
        }
        default:
            qWarning() << "[EXECD] Incorrect command type";
            return;
    }

    this->send(com);

    qDebug().noquote() << "[EXECD] Sended built-in command";
    emit socketMetrics(com, com.length(), true);
}

ExecdArgumentList* ExecdSocket::list() const noexcept { return args; }

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

    if(crc16 == receivedCrc16) {
        qDebug() << "[EXECD] Command executed successfully";
        emit ping();
    }
    else
        qWarning() << "[EXECD] CRC16 mismatch";
}

