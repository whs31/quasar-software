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
#include "wrapper.h"

#define FROM_JSON(key) Config::get()->value<QString>(key)

namespace QuasarSDK
{
  /**
   * \brief Создает новый объект ExecdSocket с указанным родителем.
   * \param compat_mode - режим совместимости со старой версией прошивки РЛС.
   * \param parent - родительский объект в дереве иерархии Qt.
   */
  ExecdSocket::ExecdSocket(bool compat_mode, QObject* parent)
      : BaseUDPSocket(parent)
      , m_compatibilityMode(compat_mode)
      , m_args(new ExecdArgumentParser(this))
      , m_message_uid(0)
      , m_strip_pid(-1)
  {
    this->setName("Execd");
    QObject::connect(this, &ExecdSocket::received, this, &ExecdSocket::process, Qt::DirectConnection);
  }

  /// \brief Включает или выключает режим совместимости со старой версией РЛС.
  void ExecdSocket::setCompatibility(bool o) { m_compatibilityMode = o; }

  /**
   * \brief Задает адреса для обратной связи сервиса \c fsend.
   * \details Порядок адресов следующий:
   *    - TCP-IP сервер (например, <tt>192.168.1.10:10000</tt>
   *    - UDP сокет для полосовых изображений (например, <tt>192.168.1.10:48455</tt>
   * \param list - массив из двух адресов.
   * \warning Функция должна быть вызвана перед вызовом метода start.
   */
  void ExecdSocket::setRemoteAddressList(const array<QString, 2>& list) noexcept { m_remote_address_list = list; }

  /**
    * \brief Выполняет произвольную команду в сервисе \c execd.
    * \details Если команда некорректна, функция ничего не сделает.
    * Функция не добавляет аргументы к команде автоматически: для
    * добавления аргументов необходимо указать их вручную.
    * \param command - строка для выполнения.
    * \note Эта функция может быть вызвана из QML через мета-объектную систему Qt.
    */
  void ExecdSocket::executeString(const QString& command) noexcept
  {
    auto com = Utils::wrapToExecdString(command, &m_message_uid);
    this->send(com);
    qDebug().noquote() << "[EXECD] Sent string command";
    emit metrics(com, com.length(), true);
  }

  /**
    * \brief Выполняет встроенную команду в сервисе \c execd.
    * \details Функция автоматически добавляет аргументы к команде,
    * если она требует их.
    * \param command - тип команды для выполнения.
    * \note Эта функция может быть вызвана из QML через мета-объектную систему Qt.
    * \see Enums::NetworkCommand
    */
  void ExecdSocket::execute(QuasarSDK::Enums::NetworkCommand command) noexcept
  {
    QByteArray com;

    switch(command)
    {
      case Enums::FormTelescopic:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Form);
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_FORM_TELESCOPIC") + m_args->formArgumentString(), &m_message_uid);
        break;
      case Enums::FocusImage:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Focus);
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_FOCUS_TELESCOPIC") + m_args->focusArgumentString(), &m_message_uid);
        break;
      case Enums::ReformImage:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Reform);
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_FORM_TELESCOPIC") + m_args->reformArgumentString(), &m_message_uid);
        break;
      case Enums::RemoteStorageStatus:
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_STORAGE_FETCH"), &m_message_uid);
        break;
      case Enums::ClearRemoteStorage:
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_STORAGE_CLEAR") + " " + FROM_JSON("EXECD_STORAGE_FETCH"), &m_message_uid);
        break;
      case Enums::StripStart:
      {
        this->setArgument("--remote", m_remote_address_list[0], Enums::Form);
        if(m_compatibilityMode)
          com = Utils::wrapToExecdString(FROM_JSON("EXECD_COMPAT_STRIP_START") + m_args->formArgumentString(), &m_message_uid);
        else
        {
          QString strip_comma = FROM_JSON("EXECD_FORM_STRIP_START") + m_args->formArgumentString();
          com = Utils::wrapToExecdString(condition(FROM_JSON("EXECD_SPECIAL_PID_OF") + "(strip_shot)",
                               FROM_JSON("EXECD_SPECIAL_PASS"), strip_comma), &m_message_uid);
          m_strip_pid = m_message_uid;
        }
        break;
      }
      case Enums::StripStop:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Form);
        if(m_compatibilityMode)
        {
          com = Utils::wrapToExecdString(FROM_JSON("EXECD_COMPAT_STRIP_STOP") + m_args->formArgumentString(), &m_message_uid);
          break;
        }
        else
        {
          signalToProcess(m_strip_pid, Enums::SigINT);
          return;
        }
      case Enums::StreamStart:
      {
        this->setArgument("--remote", m_remote_address_list[1], Enums::Form);
        if(m_compatibilityMode)
          return;
        QString stream_comma = FROM_JSON("EXECD_FORM_STREAM_START") + m_args->formArgumentString();
        com = Utils::wrapToExecdString(condition(FROM_JSON("EXECD_SPECIAL_PID_OF") + "(strip)",
                             FROM_JSON("EXECD_SPECIAL_PASS"), stream_comma), &m_message_uid);
        m_strip_pid = m_message_uid;
        break;
      }
      case Enums::StreamStop:
        this->setArgument("--remote", m_remote_address_list[1], Enums::Form);
        if(m_compatibilityMode)
          return;
        signalToProcess(m_strip_pid, Enums::SigINT);
        return;
      case Enums::Reboot:
      {
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_REBOOT"), &m_message_uid);
        break;
      }
      case Enums::PowerOff:
      {
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_POWEROFF"), &m_message_uid);
        break;
      }
      default:
        qWarning() << "[EXECD] Incorrect command type";
        return;
    }

    this->send(com);

    qDebug().noquote() << "[EXECD] Sent built-in command";
    emit metrics(com, com.length(), true);
  }

  ExecdArgumentParser* ExecdSocket::parser() const { return m_args; }

  /**
    * \brief Возвращает аргумент из списка сервиса \b execd.
    * \details Функция возвращает константный аргумент по заданному ключу
    * и категории аргументов.
    * \param key - ключ (например, <tt>"--x0"</tt>).
    * \param category - категория аргумента (см. QuasarSDK::Enums::ArgumentCategory).
    * \note Может быть вызвана из QML через мета-объектную систему.
    * \see setArgument
    */
  QString ExecdSocket::argument(const QString& key, QuasarSDK::Enums::ArgumentCategory category) noexcept
  {
    switch (category)
    {
      case Enums::Form: return parser()->formArgumentList[key].value;
      case Enums::Focus: return parser()->focusArgumentList[key].value;
      case Enums::Reform: return parser()->reformArgumentList[key].value;
      default: return "Argument Category Error";
    }
  }

  /**
    * \brief Устанавливает аргумент из списка сервиса \b execd.
    * \details Функция устанавливает выбранный аргумент в приватный список
    * аргументов сервиса \b execd и выбранную категорию. Значение аргумента
    * будет автоматически приведено к корректному виду (\c int, \c float, \c string).
    * \param key - ключ (например, <tt>"--x0"</tt>).
    * \param value - новое значение аргумента.
    * \param category - категория аргумента (см. QuasarSDK::Enums::ArgumentCategory).
    * \note Может быть вызвана из QML через мета-объектную систему.
    * \see argument
    */
  void ExecdSocket::setArgument(const QString& key, const QVariant& value,
                              QuasarSDK::Enums::ArgumentCategory category) noexcept
  {
    switch (category)
    {
      case Enums::Form: parser()->formArgumentList[key].set(value); break;
      case Enums::Focus: parser()->focusArgumentList[key].set(value); break;
      case Enums::Reform: parser()->reformArgumentList[key].set(value); break;
      default: qCritical() << "[EXECD] Invalid category for argument provided"; break;
    }
  }

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
   * \brief Принудительно завершает выбранный процесс.
   * \param pid - PID процесса.
   * \note Эта функция может быть вызвана из QML через мета-объектную систему Qt.
   */
  void ExecdSocket::kill(int pid)
  {
    QByteArray com = Utils::wrapToExecdString(FROM_JSON("EXECD_SPECIAL_KILL") + "(" + QString::number(pid) + ")", &m_message_uid);
    this->send(com);

    qDebug().noquote() << "[EXECD] Killed" << pid;
    emit metrics(com, com.length(), true);
  }

  /**
   * \brief Подает сигнал (https://ru.wikipedia.org/wiki/Сигнал_(Unix) процессу.
   * \param pid - PID процесса.
   * \param signal - сигнал (см. Enums::UnixSignal).
   * \note Эта функция может быть вызвана из QML через мета-объектную систему Qt.
   */
  void ExecdSocket::signalToProcess(int pid, Enums::UnixSignal signal)
  {
    QByteArray com = Utils::wrapToExecdString(FROM_JSON("EXECD_SPECIAL_SIGNAL") + "(" + QString::number(static_cast<int>(signal)) + ", " + QString::number(pid) + ")",
                                              &m_message_uid);
    this->send(com);

    qDebug().noquote() << "[EXECD] Sent signal" << signal << "to process" << pid;
    emit metrics(com, com.length(), true);
  }

  /**
   * \brief Возвращает список процессов в динамической очереди.
   * \note Эта функция может быть вызвана из QML через мета-объектную систему Qt.
   */
  void ExecdSocket::showQueue()
  {
    QByteArray com = Utils::wrapToExecdString(FROM_JSON("EXECD_SPECIAL_QUEUE_SHOW"), &m_message_uid);
    this->send(com);

    qDebug().noquote() << "[EXECD] Asked for queue";
    emit metrics(com, com.length(), true);
  }

  /**
   * \brief Очищает динамическую очередь.
   * \note Эта функция может быть вызвана из QML через мета-объектную систему Qt.
   */
  void ExecdSocket::clearQueue()
  {
    QByteArray com = Utils::wrapToExecdString(FROM_JSON("EXECD_SPECIAL_QUEUE_CLEAR"), &m_message_uid);
    this->send(com);

    qDebug().noquote() << "[EXECD] Cleared queue";
    emit metrics(com, com.length(), true);
  }

  /**
   * \brief Удаляет последнюю команду из динамической очереди.
   * \note Эта функция может быть вызвана из QML через мета-объектную систему Qt.
   */
  void ExecdSocket::popQueue()
  {
    QByteArray com = Utils::wrapToExecdString(FROM_JSON("EXECD_SPECIAL_QUEUE_POP"), &m_message_uid);
    this->send(com);

    qDebug().noquote() << "[EXECD] Removed last command from queue";
    emit metrics(com, com.length(), true);
  }

  /**
   * \brief Запускает выбранную команду на удаленном хосте.
   * \param command - команда для запуска.
   * \param host - хост (например, <tt>user@192.168.1.48</tt>.
   * \param password - пароль. Для подключения без пароля оставьте строку пустой.
   */
  void ExecdSocket::ssh(const QString& command, const QString& host, const QString& password)
  {
    QByteArray com = Utils::wrapToExecdString(FROM_JSON("EXECD_SPECIAL_SSH") + "(" + command + ", " + host + ", " + (password.isNull() ? ""
        : password), &m_message_uid);
    this->send(com);

    qDebug().noquote() << "[EXECD] Executed command on" << host;
    emit metrics(com, com.length(), true);
  }

  /**
   * \brief Оборачивает команды в условие.
   * \param condition - условие для выполнения.
   * \param pass - команда, выполняемая в случае успеха.
   * \param fail - команда, выполняемая в случае неудачи.
   * \return Обернутая команда.
   * \warning Это приватная функция.
   */
  QString ExecdSocket::condition(const QString& condition, const QString& pass, const QString& fail) noexcept
  {
    return condition + " ? " + pass + " : " + fail;
  }

  QString ExecdSocket::prepareCommand(QuasarSDK::Enums::NetworkCommand command) noexcept
  {
    QByteArray com;

    switch(command)
    {
      case Enums::FormTelescopic:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Form);
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_FORM_TELESCOPIC") + m_args->formArgumentString(), &m_message_uid);
        break;
      case Enums::FocusImage:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Focus);
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_FOCUS_TELESCOPIC") + m_args->focusArgumentString(), &m_message_uid);
        break;
      case Enums::ReformImage:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Reform);
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_FORM_TELESCOPIC") + m_args->reformArgumentString(), &m_message_uid);
        break;
      case Enums::RemoteStorageStatus:
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_STORAGE_FETCH"), &m_message_uid);
        break;
      case Enums::ClearRemoteStorage:
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_STORAGE_CLEAR") + " " + FROM_JSON("EXECD_STORAGE_FETCH"), &m_message_uid);
        break;
      case Enums::StripStart:
      {
        this->setArgument("--remote", m_remote_address_list[0], Enums::Form);
        if(m_compatibilityMode)
          com = Utils::wrapToExecdString(FROM_JSON("EXECD_COMPAT_STRIP_START") + m_args->formArgumentString(), &m_message_uid);
        else
        {
          QString strip_comma = FROM_JSON("EXECD_FORM_STRIP_START") + m_args->formArgumentString();
          com = Utils::wrapToExecdString(condition(FROM_JSON("EXECD_SPECIAL_PID_OF") + "(strip_shot)",
                                                   FROM_JSON("EXECD_SPECIAL_PASS"), strip_comma), &m_message_uid);
          m_strip_pid = m_message_uid;
        }
        break;
      }
      case Enums::StripStop:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Form);
        if(m_compatibilityMode)
        {
          com = Utils::wrapToExecdString(FROM_JSON("EXECD_COMPAT_STRIP_STOP") + m_args->formArgumentString(), &m_message_uid);
          break;
        }
        else
          return {};
      case Enums::StreamStart:
      {
        this->setArgument("--remote", m_remote_address_list[1], Enums::Form);
        if(m_compatibilityMode)
          return {};
        QString stream_comma = FROM_JSON("EXECD_FORM_STREAM_START") + m_args->formArgumentString();
        com = Utils::wrapToExecdString(condition(FROM_JSON("EXECD_SPECIAL_PID_OF") + "(strip)",
                                                 FROM_JSON("EXECD_SPECIAL_PASS"), stream_comma), &m_message_uid);
        m_strip_pid = m_message_uid;
        break;
      }
      case Enums::StreamStop:
        this->setArgument("--remote", m_remote_address_list[1], Enums::Form);
        if(m_compatibilityMode)
          return {};
        return {};
      case Enums::Reboot:
      {
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_REBOOT"), &m_message_uid);
        break;
      }
      case Enums::PowerOff:
      {
        com = Utils::wrapToExecdString(FROM_JSON("EXECD_POWEROFF"), &m_message_uid);
        break;
      }
      default:
        qWarning() << "[EXECD] Incorrect command type";
        return {};
    }

    return {com};

    qDebug().noquote() << "[EXECD] Prepared built-in command";
  }
} // QuasarSDK
