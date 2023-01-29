#include "execdremote.h"

ExecdRemote::ExecdRemote(QObject *parent)
    : QObject{parent}
{
    udpRemote = new UDPRemote();
    QObject::connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(receiveResponse(QByteArray)));
    ArgumentList::get(this);
}

ExecdRemote::~ExecdRemote()
{
    udpRemote->Disconnect();
    delete udpRemote;
}

size_t ExecdRemote::getMessageID(void)
{
    return messageID;
}

void ExecdRemote::connect(QString ip, quint16 port)
{
    disconnect();
    udpRemote->Connect(ip + ":" + QString::number(port));
    Debug::Log("[EXECD REMOTE] Listening to SAR on " + ip + ":" + QString::number(port));
}

void ExecdRemote::disconnect(void)
{
    udpRemote->Disconnect();
    Debug::Log("[EXECD REMOTE] Disconnecting...");
}

void ExecdRemote::receiveResponse(QByteArray data)
{
    QString rawString = data.data();
    QString checkCrc = rawString;
    checkCrc.chop(5);

    QStringList response = rawString.split("|");
    int strlen = response[1].toInt(nullptr, 10);
    response[2].remove(0, 1);

    //crc16
    uint16_t crc16 = SChecksum::calculateCRC16(SChecksum::toCharPointer(checkCrc), checkCrc.length());
    uint16_t receivedCrc16 = response[3].toUInt(nullptr, 16);
    int checksumCheckResult = (crc16 == receivedCrc16) ? 1 : 0;

    if (!response.empty())
    {
        QString crcResultString = (checksumCheckResult == 1) ? "success" : "failure";
        if(checksumCheckResult == 1)
        {
            RuntimeData::get()->setFormStatus("Получен ответ от РЛС");
            Debug::Log("[EXECD REMOTE] Command received, response: " + response[0] + ", hexlen " 
                    + QString::number(strlen) + ", code" + response[2] 
                    + " with checksum check " + crcResultString);
        }
        else 
        {
            Debug::Log("[EXECD REMOTE] Something with wrong checksum is received!");
        }
    }
}

void ExecdRemote::executeClearCommand() { sendCommand(ExecdCommand::ClearStorage); }
void ExecdRemote::executeFormCommand() { sendCommand(ExecdCommand::FormImage); } // спросить у вовы как это нормально сделать через коннекты))))))
void ExecdRemote::sendCommand(ExecdCommand command)
{
    switch (command)
    {
    case ExecdCommand::ClearStorage:
    {
        Debug::Log("?[EXECD REMOTE] Clearing SAR storage");
        QByteArray request = makeCommand(CACHE_CLEAR_COMMAND).toUtf8();
        udpRemote->Send(request);
        Debug::Log("[EXECD REMOTE] Sended to SAR: " + request);
        break;
    }
    case ExecdCommand::StorageStatus:
    {
        Debug::Log("[EXECD REMOTE] Asking for disk storage status");
        QByteArray request = makeCommand(STORAGE_STATUS_COMMAND).toUtf8();
        udpRemote->Send(request);
        Debug::Log("[EXECD REMOTE] Sended to SAR: " + request);
        break;
    }
    case ExecdCommand::FormImage:
    {
        Debug::Log("[EXECD REMOTE] Sending form command");
        QByteArray request = makeCommand(FORM_MARKER + ArgumentList::get()->makeFormArguments()).toUtf8();
        udpRemote->Send(request);
        Debug::Log("[EXECD REMOTE] Sended to SAR: " + request);
        break;
    }

    default:
        break;
    }
}

QString ExecdRemote::makeCommand(QString string)
{
    QString fullCommand = ":" + QStringLiteral("%1").arg(++messageID, 4, 10, QLatin1Char('0')) + "|";
    QString hexlen = QString("%1").arg(string.length(), 2, 16, QLatin1Char('0'));
    fullCommand.append(hexlen + "|" + string + "|");
    fullCommand.append(QStringLiteral("%1").arg(SChecksum::calculateCRC16(SChecksum::toCharPointer(fullCommand), fullCommand.length()), 4, 16, QLatin1Char('0')));
    if(SConfig::get()->getUseOldExecdEndline())
        fullCommand.append("\n");
    return fullCommand;
}
