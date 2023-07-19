/**
 * \ingroup sdk_network
 * \class QuasarSDK::ExecdSocket CExecdSocket.h <QuasarSDK/Networking/CExecdSocket.h>
 * \brief Сокет для отправки команд на РЛС.
 * \details Класс предоставляет функции для выполнения
 * команд на стороне РЛС (как встроенных в программу, так и
 * произвольных строковых команд). Поддерживает автоматический
 * поиск и добавление аргументов для команд, которые требуют этого.
 * Обрабатывает ответы РЛС (статус выполнения команды).
 * Предоставляет отладочные метрики.
 *
 * Документацию по сервису \c execd можно прочитать здесь: \ref EXECD_DOCUMENTATION
 */

#include "execdsocket.h"
#include "network_config.h"
#include "execdparser.h"
#include "crc16.h"

namespace QuasarSDK
{
  /// \brief Создает новый объект ExecdSocket с указанным родителем.
  ExecdSocket::ExecdSocket(QObject* parent)
      : BaseUDPSocket(parent)
      , m_args(new ExecdArgumentParser(this))
      , m_message_uid(0)
      , m_strip_pid(-1)
  {
    this->setName("Execd");
    QObject::connect(this, &ExecdSocket::received, this, &ExecdSocket::process, Qt::DirectConnection);
  }

  /**
    * \brief Выполняет произвольную команду в сервисе \c execd.
    * \details Если команда некорректна, функция ничего не сделает.
    * Функция не добавляет аргументы к команде автоматически: для
    * добавления аргументов необходимо указать их вручную.
    * \param command - строка для выполнения.
    */
  void ExecdSocket::execute(const QString& command) noexcept
  {
    auto com = wrap(command);
    this->send(com);
    qDebug().noquote() << "[EXECD] Sended string command";
    emit metrics(com, com.length(), true);
  }

  /**
    * \brief Выполняет встроенную команду в сервисе \c execd.
    * \details Функция автоматически добавляет аргументы к команде,
    * если она требует их.
    * \param command - тип команды для выполнения.
    * \see Enums::NetworkCommand
    */
  void ExecdSocket::execute(Enums::NetworkCommand command) noexcept
  {
    QByteArray com;

    switch(command)
    {
      case Enums::FormImage:
        com = wrap(Config::get()->value<QString>("EXECD_FORM_TELESCOPIC") + m_args->formArgumentString());
        break;
      case Enums::FocusImage:
        com = wrap(Config::get()->value<QString>("EXECD_FOCUS_TELESCOPIC") + m_args->focusArgumentString());
        break;
      case Enums::ReformImage:
        com = wrap(Config::get()->value<QString>("EXECD_FORM_TELESCOPIC") + m_args->reformArgumentString());
        break;
      case Enums::RemoteStorageStatus:
        com = wrap(Config::get()->value<QString>("EXECD_STORAGE_FETCH"));
        break;
      case Enums::ClearRemoteStorage:
        com = wrap(Config::get()->value<QString>("EXECD_STORAGE_CLEAR") + " " + Config::get()->value<QString>("EXECD_STORAGE_FETCH"));
        break;
      case Enums::SimpleStrip:
        com = wrap(Config::get()->value<QString>("EXECD_FORM_STRIP_DEBUG") + m_args->formArgumentString());
        break;
      case Enums::StartStrip:
        com = wrap(Config::get()->value<QString>("EXECD_FORM_STRIP_START") + m_args->formArgumentString());
        m_strip_pid = m_message_uid;
        break;
      case Enums::StopStrip:
        signalToProcess(m_strip_pid, Enums::SigINT);
        return;
      case Enums::Reboot:
      {
        com = wrap(Config::get()->value<QString>("EXECD_REBOOT"));
        break;
      }
      case Enums::PowerOff:
      {
        com = wrap(Config::get()->value<QString>("EXECD_POWEROFF"));
        break;
      }
      default:
        qWarning() << "[EXECD] Incorrect command type";
        return;
    }

    this->send(com);

    qDebug().noquote() << "[EXECD] Sended built-in command";
    emit metrics(com, com.length(), true);
  }

  ExecdArgumentParser* ExecdSocket::parser() const { return m_args; }

  void ExecdSocket::process(QByteArray data)
  {
    QString raw = data.data();
    QString check_crc = raw;
    check_crc.chop(5);

    uint16_t crc16 = Utils::crc16(Utils::str_data(check_crc), check_crc.length());
    uint16_t receivedCrc16 = raw.split("|").last().toUInt(nullptr, 16);

    if(crc16 == receivedCrc16)
    {
      qDebug() << "[EXECD] Command executed successfully";
      emit ping();
    }
//    else
//      qWarning() << "[EXECD] CRC16 mismatch";
    emit metrics(raw, data.size(), false);
  }

  /**
    * \brief Оборачивает строку в формат \c execd.
    * \details Добавляет уникальный ID, длину строки в
    * шестнадцатеричном формате и контрольную сумму CRC16
    * к указанной строке, разделяя это символом \c |.
    * \param string - строка для оборачивания.
    * \note Это приватная функция.
    * \return UTF-8 данные для отправки в сокет.
    */
  QByteArray ExecdSocket::wrap(const QString& string) noexcept
  {
    // prevents UID overflow
    if(m_message_uid >= 9999)
      m_message_uid = 0;

    QString command = ":" + QStringLiteral("%1").arg(++m_message_uid, 4, 10, QLatin1Char('0')) + "|";
    QString hex_length = QString("%1").arg(string.length(), 2, 16, QLatin1Char('0'));
    command.append(hex_length + "|" + string + "|");
    command.append(QStringLiteral("%1").arg(Utils::crc16(Utils::str_data(command), command.length()),
                                            4, 16, QLatin1Char('0')));
    return command.toUtf8();
  }

  void ExecdSocket::signalToProcess(int pid, Enums::UnixSignal signal)
  {
    QByteArray com;
    com = wrap("#sig(" + QString::number(static_cast<int>(signal)) + ", " + QString::number(pid) + ")");
    this->send(com);

    qDebug().noquote() << "[EXECD] Sended signal" << signal << "to process" << pid;
    emit metrics(com, com.length(), true);
  }
} // QuasarSDK