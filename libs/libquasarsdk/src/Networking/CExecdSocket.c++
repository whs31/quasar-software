/**
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
  *
  * \todo Обработчик ответов РЛС - в разработке.
  */

#include "CExecdSocket.h"
#include "CConfig.h"
#include "CExecdArgumentParser.h"
#include "FCRC16.h"

namespace QuasarSDK
{
  /// \brief Создает новый объект ExecdSocket с указанным родителем.
  ExecdSocket::ExecdSocket(QObject* parent)
      : BaseUDPSocket(parent)
      , m_args(new ExecdArgumentParser(this))
      , m_message_uid(0)
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
        break;
      case Enums::StopStrip:
        com = wrap(Config::get()->value<QString>("EXECD_FORM_STRIP_STOP") + m_args->formArgumentString());
        break;
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
} // QuasarSDK

/**
  * \page EXECD_DOCUMENTATION Документация по сервису execd
  * \tableofcontents
  * Сервис выполняет роль планировщика задач.
  * Обеспечивает следующий функционал:
  *     - принимает команды от удаленных клиентов с последующим их исполнением
  *     - позволяет отслеживать и изменять статус выполнения команд
  *     - строит очереди на выполнение команд
  *
  * \section EXECD_DOCUMENTATION_LEGEND Принятые выражения
  *     - <tt>XX</tt> - значение поля не рассматривается в контексте
  *     - <tt>CMD</tt> - условное обозначение любой команды, задаваемой пользователем
  *     - <tt>SPEC_CMD</tt> - условное обозначение любой специальной команды, задаваемой пользователем (см. п. \ref EXECD_DOCUMENTATION_SPECIAL_COMMANDS)
  *     - <tt>arg</tt> - условное обозначение любого аргумента, передаваемого команде CMD или SPEC_CMD
  *
  * \section EXECD_DOCUMENTATION_FORMING Формирование запроса
  * Пример команды запроса сервису:
  * \code {.py}
  * :0001|09|$FORM(3)|da0f
  * \endcode
  *     - *:* - символ начала сообщения
  *     - *0001* - id сообщения (hex)
  *     - *09* - полный размер команды, не считая специальные поля и символы (hex)
  *     - *$* - ключ формат команды
  *     - *FORM* - команда
  *     - *(3)* - аргументы
  *     - *da0f* - контрольная сумма CRC16 (hex)
  *
  * Ключи формата команд:
  *     - *&* - выполнение shell команды - <tt>:0001|08|&ls(-la)|0daa</tt>
  *     - *$* - выполнение программы из каталога scripts - <tt>:0001|09|$FORM(3)|da0f</tt>
  *     - *#* - специальная команда (см. пункт \ref EXECD_DOCUMENTATION_SPECIAL_COMMANDS)
  *
  * Правила формирования команды:
  *     - поле "команда" - должно содержать полное название команды, учитывая регистр.
  *     - поле "аргументы" - записывается внутри круглых скобок "(" и ")".
  *
  * Аргументы могут перечисляться через пробел или запятую:
  *     - <tt>:XXXX|XX|$CMD(arg1, arg2)|XXXX</tt>
  *     - <tt>:XXXX|XX|$CMD(arg1 arg2)|XXXX</tt>
  *
  * Если аргументам присваивается значение, то допускаются следующие варианты записи:
  *     - <tt>:XXXX|XX|$CMD(arg1=1, arg2=2)|XXXX</tt>
  *     - <tt>:XXXX|XX|$CMD(arg1 1, arg2 2)|XXXX</tt>
  *     - <tt>:XXXX|XX|$CMD(arg1 1 arg2 2)|XXXX</tt>
  *
  * Допускается передавать сразу несколько команд:
  * \code {.py}
    :XXXX|XX|$CMD1(1, 2) $CMD2(1, 2) $CMD3(1, 2)|XXXX
  * \endcode
  * В таком случае команды будет создана статическая очередь и все переданные команды будут выполнены последовательно.
  * По завершению выполнения статической очереди формируется ответ, который содержит коды завершения каждой команды:
  * \code {.py}
  * :XXXX|XX|$=0000 $=0022 E=0002|XXXX
                ^      ^      ^ код завершения $CMD3
                |      | код завершения $CMD2
                | код завершения $CMD1
  * \endcode
  *
  *
  * \section EXECD_DOCUMENTATION_SPECIAL_COMMANDS Специальные команды
  * Для формирования специальной команды используется знак-префикс "#":
  * \code {.py}
    :XXXX|XX|#SPEC_CMD(arg)|XXXX
  * \endcode
  *
  * Список специальных команд:
  *     - <tt>kill(YYYY)</tt> - принудительно завершить процесс с индексом <tt>YYYY</tt>
  *     - <tt>:XXXX|XX|#kill(YYYY)|XXXX</tt>
  *     - <tt>YYYY</tt> (hex) - id сообщения процесса
  *     - <tt>sig(ZZ,YYYY)</tt> - подать сигнал №ZZ (https://ru.wikipedia.org/wiki/Сигнал_(Unix)) процессу id = YYYY (hex)
  *     - <tt>:XXXX|XX|#sig(ZZ,YYYY)|XXXX</tt>
  *     - <tt>ZZ</tt> (dec) - номер сигнала
  *     - <tt>YYYY</tt> (hex) - id сообщения процесса
  *     - <tt>feedback(ZZZ,YYY)</tt> - установить тип соединения и адрес канала для обратной связи stdout, stderr последующей команды в статической очереди.
  *         - <tt>:XXXX|XX|#feedback(ZZZ,YYY) $CMD1(1, 2)|XXXX</tt>
  *             - <tt>ZZZ</tt> - тип соединения (TCP, UDP)
  *             - <tt>YYY</tt> - адрес канала обратной связи (<tt>192.168.1.2:9945</tt>)
  *             - <tt>$CMD1(1, 2)</tt> - команда, поток которой будет перенаправлен
  *     - <tt>queue()</tt> - вернуть список процессов, поставленных в динамическую очередь
  *         - <tt>:XXXX|XX|#queue()|XXXX</tt>
  *     - <tt>queue(clear)</tt> - очистить динамическую очередь
  *         - <tt>:XXXX|XX|#queue(clear)|XXXX</tt>
  *     - <tt>queue(pop)</tt> - удалить последнюю команду из динамической очереди
  *         - <tt>:XXXX|XX|#queue(pop)|XXXX</tt>
  *     - <tt>ssh('YYYY')</tt> - запуск команды YYYY на удаленном хосте через ssh (значения хоста и пароля - по-умолчанию, см. п. \ref EXECD_DOCUMENTATION_SETTINGS)
  *         - <tt>:XXXX|XX|#ssh('YYYY')|XXXX</tt>
  *             - YYYY - команда для удаленного хоста, наример 'uname -a'
  *     - <tt>ssh('YYYY', ZZZZ)</tt> - запуск команды YYYY на удаленном хосте ZZZZ через ssh (значение пароля - по-умолчанию, см. п. \ref EXECD_DOCUMENTATION_SETTINGS)
  *         - <tt>:XXXX|XX|#ssh('YYYY', ZZZZ)|XXXX</tt>
  *             - ZZZZ - имя удаленного хоста, например <tt>user@192.168.1.48</tt>
  *     - <tt>ssh('YYYY', ZZZZ, WWWW)</tt> - запуск команды YYYY на удаленном хосте ZZZZ через ssh (значение пароля - WWWW)
  *         - <tt>:XXXX|XX|#ssh('YYYY', ZZZZ, WWWW)|XXXX</tt>
  *             - WWWW - пароль удаленного хоста, например, 123
  *     - <tt>occupied(YY)</tt> - проверка id процесса на занятость
  *         - <tt>:XXXX|XX|#occupied(YY)|XXXX</tt>
  *             - YY - id процесса, занятость которого необходимо проверить. Допускается передавать id в десятичном или шестнадцатеричном виде.
  *         - Пример допустимых видов записи:
  *             - <tt>:XXXX|XX|#occupied(1)|XXXX</tt>
  *             - <tt>:XXXX|XX|#occupied(01)|XXXX</tt>
  *             - <tt>:XXXX|XX|#occupied(0x01)|XXXX</tt>
  *
  * Возвращаемые значения:
  * \code {.py}
    - `:XXXX|XX|$=0000|XXXX` - id свободен
    - `:XXXX|XX|$=0001|XXXX` - id занят
  * \endcode
  *
  * \section EXECD_DOCUMENTATION_DYNAMIC_QUEUES Создание динамических очередей
  * Для создания динамической очереди достаточно отправить запрос с уже "занятым"<sup>1</sup> ID сообщения:
  * \code {.py}
    :0001|XX|$CMD1(arg1)|XXXX
    :0001|XX|$CMD2(arg1, arg2, arg3)|XXXX
  * \endcode
  *
  * Таким образом $CMD1 немедленно начнет выполнение, а $CMD2 - сразу после $CMD1. По мере необходимости можно пополнять
  * очередь во время ее выполнения:
  * \code {.py}
    :0001|XX|$CMD3(arg1)|XXXX
    :0001|XX|$CMD4(arg1, arg2)|XXXX
    :0001|XX|$CMD5(arg1)|XXXX
    ...
  * \endcode
  * В отличии от статической очереди, ответ формируется всякий раз, когда завершается выполнение очередной команды.
  *
  * <sup>1</sup> *Примечание - id "освобождается" сразу же после выполнения команды или завершения очереди.*
  *
  * \section EXECD_DOCUMENTATION_RESPONSE Ответ сервиса
  * Сервис формирует ответ с результатом выполнения команды:
  * \code {.py}
    :XXXX|XX|$=0000|XXXX
  * \endcode
  *
  * Например:
  * \code {.py}
    :0001|06|$=0000|6f24
  * \endcode
  *     - <tt>:</tt> - символ начала сообщения
  *     - <tt>0001</tt> - id сообщения (hex)
  *     - <tt>06</tt> - полный размер ответа, не считая специальные поля и символы (hex)
  *     - <tt>$</tt> - ключ формата команды
  *     - <tt>=0000</tt> - код завершения программы
  *     - <tt>6f24</tt> - контрольная сумма CRC16 (hex)
  *
  * Ключ формата команды ответа соответствует ключу формата запроса, однако формат ответа содержит дополнительный ключ - "E"
  * Ключ "E" возникает в случае системной ошибки, например, запрашиваемая команда отсутствует:
  * \code {.py}
    :0001|06|E=0002|0976
  * \endcode
  *
  * \section EXECD_DOCUMENTATION_CHECKSUM Контрольная сумма
  * Проверка контрольной суммы может быть отключена (см. п. \ref EXECD_DOCUMENTATION_SETTINGS).
  * Пример реализации подсчета контрольной суммы представлены в
  *     - utils/crc16.c - С/С++
  *     - utils/cli.py - Python
  *     - src/misc.rs - Rust
  *     - FCRC16.h - в этой библиотеке (C/C++)
  *
  * \section EXECD_DOCUMENTATION_SETTINGS Настройки
  * Настройки хранятся в конфигурационном файле config.ini и имеет следующие поля:
  *     - <tt>main/remote_address</tt> - ip адрес сервиса. Например, <tt>192.168.1.47:21030</tt>.
  *     - <tt>main/remote_type</tt> - тип соединения сервиса. Возможны следующие значения:
  *         - <tt>udp</tt>
  *         - <tt>tcp</tt>
  *         - <tt>com</tt> (в разработке)
  *         - <tt>tlg</tt> (в разработке)
  *     - <tt>main/log_level</tt> - уровень сообщений, которые будут выводиться в терминал. Возможны следующие значения:
  *         - <tt>info</tt>
  *         - <tt>warn</tt>
  *         - <tt>error</tt>
  *     - <tt>main/crc_check</tt> - флаг проверки контрольной суммы. Возможны следующие значения <tt>true</tt>, <tt>false</tt>
  *     - <tt>main/feedback_address</tt> - ip адрес сервера, на который будет перенаправлен вывод исполняемой программы. Например, <tt>192.168.1.1:10000</tt>.
  *     - <tt>main/feedback_type</tt> - тип соединения сервера, на который будет перенаправлен вывод исполняемой программы. Возможны следующие значения:
  *         - <tt>udp</tt>
  *         - <tt>tcp</tt>
  *         - <tt>com</tt> (в разработке)
  *         - <tt>tlg</tt> (в разработке)
  *     - <tt>ssh/host</tt> - адрес хоста по-умолчанию, к которому обращается сервис посредством ssh с целью исполнения на нем программы или сценария. Например, <tt>user@192.168.1.48</tt>.
  *     - <tt>ssh/password</tt> - пароль хоста по-умолчанию, к которому обращается сервис посредством ssh с целью исполнения на нем программы или сценария. Например, <tt>123</tt>
  *
  * \section EXECD_DOCUMENTATION_BUILD Сборка
  * \code {.sh}
    cargo --config Cargo.config build
  * \endcode
  *
  * \section EXECD_DOCUMENTATION_RULES Правила оформления скриптов
  * Каждый скрипт, добавленный в каталог scripts должен иметь заголовок с указанием интерпретатора, например:
  * \code {.sh}
    #!/bin/bash
  * \endcode
*/