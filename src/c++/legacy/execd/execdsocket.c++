#include "execdsocket.h"
#include <SDK/CRC16>
#include "config/paths.h"
#include "config/networkconfig.h"
#include "execdargumentlist.h"

namespace Networking
{

  ExecdSocket::ExecdSocket(QObject* parent)
    : UDPSocketBase{parent}, args(new ExecdArgumentList(this)), message_uid(0)
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
    auto com = wrap(command);
    this->send(com);
    qDebug().noquote() << "[EXECD] Sended string command";
    emit socketMetrics(com, com.length(), true);
  }

  void ExecdSocket::executeCommand(Enums::NetworkCommand command)
  {
    QByteArray com;

    switch(command)
    {
      case Enums::FormImage:
        com = wrap(NETCFG("EXECD_FORM_TELESCOPIC") + args->getFormArguments());
        break;
      case Enums::FocusImage:
        com = wrap(NETCFG("EXECD_FOCUS_TELESCOPIC") + args->getFocusArguments());
        break;
      case Enums::ReformImage:
        com = wrap(NETCFG("EXECD_FORM_TELESCOPIC") + args->getReformArguments());
        break;
      case Enums::RemoteStorageStatus:
        com = wrap(NETCFG("EXECD_STORAGE_FETCH"));
        break;
      case Enums::ClearRemoteStorage:
        com = wrap(NETCFG("EXECD_STORAGE_CLEAR") + " " + NETCFG("EXECD_STORAGE_FETCH"));
        break;
      case Enums::SimpleStrip:
        com = wrap(NETCFG("EXECD_FORM_STRIP_DEBUG") + args->getFormArguments());
        break;
      case Enums::StartStrip:
        com = wrap(NETCFG("EXECD_FORM_STRIP_START") + args->getFormArguments());
        break;
      case Enums::StopStrip:
        com = wrap(NETCFG("EXECD_FORM_STRIP_STOP") + args->getFormArguments());
        break;
      case Enums::Reboot:
      {
        com = wrap(NETCFG("EXECD_REBOOT") + args->getFormArguments());
        break;
      }
      case Enums::Poweroff:
      {
        com = wrap(NETCFG("EXECD_POWEROFF") + args->getFormArguments());
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

  QByteArray ExecdSocket::wrap(const QString& string)
  {
    // prevents UID overflow
    if(message_uid == 9999)
      message_uid = 0;

    QString command = ":" + QStringLiteral("%1").arg(++message_uid, 4, 10, QLatin1Char('0')) + "|";
    QString hex_length = QString("%1").arg(string.length(), 2, 16, QLatin1Char('0'));
    command.append(hex_length + "|" + string + "|");
    command.append(QStringLiteral("%1").arg(SDK::Crypto::crc16(SDK::Crypto::str_data(command),
                                                        command.length()),
                                            4, 16, QLatin1Char('0')));
    return command.toUtf8();
  }

  void ExecdSocket::processResult(QByteArray data)
  {
    QString raw = data.data();
    QString check_crc = raw;
    check_crc.chop(5);

    uint16_t crc16 = SDK::Crypto::crc16(SDK::Crypto::str_data(check_crc), check_crc.length());
    uint16_t receivedCrc16 = raw.split("|").last().toUInt(nullptr, 16);

    if(crc16 == receivedCrc16)
    {
      qDebug() << "[EXECD] Command executed successfully";
      emit ping();
    }
//    else
//      qWarning() << "[EXECD] CRC16 mismatch";
    emit socketMetrics(raw, data.size(), false);
  }

} // Networking
