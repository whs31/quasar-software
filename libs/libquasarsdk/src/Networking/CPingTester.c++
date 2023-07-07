/**
  * \class QuasarSDK::PingTester CPingTester.h <QuasarSDK/Networking/CPingTester.h>
  * \brief Класс для постоянной проверки выбранного адреса на доступность.
  * \details Выполняет постоянную проверку выбранного адреса командой \c ping
  * по протоколу ICMP. Предоставляет результат в виде сигнала со статус-кодом.
  * \note На ОС Windows проверка выполняется не 5 раз, как в обычной команде
  * \c ping на этой системе, а до тех пор, пока процесс не будет завершен, как
  * на ОС Linux.
  * \extends QObject, IConnectable
  */

#include "CPingTester.h"
#include <stdexcept>
#include <QtCore/QProcess>

namespace QuasarSDK
{

  /// \brief Создает новый экземпляр класса PingTester с указанным родителем.
  PingTester::PingTester(QObject* parent)
      : QObject(parent)
      , m_process(new QProcess(this))
      , m_address("127.0.0.1")
  {
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, &QProcess::readyRead, this, &PingTester::recv);
  }

  /// \brief Удаляет объект и принудительно завершает все дочерние процессы.
  PingTester::~PingTester() { m_process->terminate(); }

  /**
   * \brief Запускает проверку доступности по указанному адресу.
   * \details Выбрасывает исключение, если адрес некорректный.
   * \param address - IPv4-адрес для проверки в виде строки.
   * \throws std::invalid_argument.
   */
  void PingTester::start(const QString& address)
  {
    if(address.split('.').size() != 4)
      throw std::invalid_argument("Invalid address is provided to ping tester");

    m_address = address;

    this->ping();
  }

  /**
   * \brief Запускает проверку доступности по указанному адресу.
   * \param address - IPv4-адрес для проверки в виде QHostAddress.
   */
  void PingTester::start(const QHostAddress& address) noexcept
  {
    m_address = address.toString();
    this->ping();
  }

  /**
   * \brief Запускает проверку доступности по указанному адресу.
   * \param address - IPv4-адрес для проверки в виде QHostAddress.
   * \param port - не используется.
   */
  void PingTester::start(const QHostAddress& address, uint16_t port) noexcept
  {
    Q_UNUSED(port);
    this->start(address);
  }

  /// \brief Останавливает проверку доступности.
  void PingTester::stop() noexcept { m_process->kill(); }

  void PingTester::ping()
  {
    #ifdef Q_OS_WIN
    m_process->start("ping", QStringList("-t") << QString(m_address) );
    #else
    m_process->start("ping", QStringList() << QString(m_address) );
    #endif
  }

  void PingTester::recv()
  {
    auto data = m_process->readAll();
    bool success = false;
    #ifdef Q_OS_WIN
    success = data.contains("TTL=");
    #else
    success = data.contains("time=");
    #endif

    emit result(success ? Enums::PingStatus::Success : Enums::PingStatus::Timeout);
  }
} // QuasarSDK