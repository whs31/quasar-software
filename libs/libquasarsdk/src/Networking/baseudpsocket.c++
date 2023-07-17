/**
 * \ingroup sdk_network
 * \class QuasarSDK::BaseUDPSocket CBaseUDPSocket.h <QuasarSDK/Networking/CBaseUDPSocket.h>
 * \brief Базовый класс для сокетов, работающих по протоколу UDP.
 * \details Класс расширяет функционал QUdpSocket и добавляет
 * несколько важных функций и сигналов для удобства разработки.
 * Этот класс - родительский класс для всех
 * UDP-сокетов в комплекте разработчика РЛС "Квазар".
 * \note Для случаев, когда недопустимо склеивание или кеширование
 * входящих датаграмм, используйте класс SeamlessUDPSocket как
 * основу для класса-сокета.
 */

#include "CBaseUDPSocket.h"
#include <stdexcept>
#include <QtCore/QDebug>

namespace QuasarSDK
{
  /// \brief Создает новый объект BaseUDPSocket с указанным родителем.
  BaseUDPSocket::BaseUDPSocket(QObject* parent)
      : QUdpSocket(parent)
      , m_address(QHostAddress())
      , m_port(0)
      , m_socketname("Unnamed")
  {
    connect(this, &QUdpSocket::readyRead, this, &BaseUDPSocket::readSocket, Qt::DirectConnection);
  }

  /// \brief Вызывает метод QUdpSocket::disconnect() и удаляет объект.
  BaseUDPSocket::~BaseUDPSocket() { this->stop(); }

  /// \brief Возвращает отладочное название сокета.
  QString BaseUDPSocket::name() const { return m_socketname; }

  /// \brief Задает отладочное название сокета.
  void BaseUDPSocket::setName(const QString& name) noexcept { m_socketname = name; }

  /**
    * \brief Производит попытку подключения к указанному адресу.
    * \details Адрес предоставляется в сокет в виде строки. Пример:
    * \code {.cpp}
    * try
    * {
    *    this->connect("192.168.1.47:9955");
    * }
    * catch(std::invalid_argument)
    * {
    *    // ...
    * }
    * \endcode
    *
    * При неверном типе адреса будет выброшено исключение.
    * Вместо IPv4 адреса можно предоставить строку AnyIPv4. Пример:
    * \code {.cpp}
    * this->connect("AnyIPv4:1234");
    * \endcode
    * \param address - адрес в виде строки.
    * \throws std::invalid_argument
    */
  void BaseUDPSocket::start(const QString& address)
  {
    if(not address.contains(":"))
      throw std::invalid_argument("Address string must contain semicolon");

    auto spl = address.split(':');
    if(not address.contains("AnyIPv4") and spl.first().split('.').size() != 4)
      throw std::invalid_argument("Provided invalid address");

    QHostAddress ip;
    if(address.contains("AnyIPv4"))
      ip = QHostAddress(QHostAddress::AnyIPv4);
    else
      ip = QHostAddress(spl.first());

    bool uint_success = false;
    uint16_t p = spl.last().toUInt(&uint_success);
    if(not uint_success)
      throw std::invalid_argument("Provided incorrect port");

    qInfo().noquote() << "[UDP] Starting" << name() << "UDP socket on" << address;
    m_address = ip;
    m_port = p;

    this->bind(hostAddress(), port());
    emit metrics("Socket opened on " + addressString(), 0, true);
  }

  /// \brief Отключает сокет от адреса, если он был подключен.
  void BaseUDPSocket::stop() noexcept
  {
    qInfo() << "[UDP] Disconnecting" << name() << "UDP socket from" << addressString();
    this->close();
    m_address.clear();
    m_port = 0;

    emit metrics("Socket closed", 0, true);
  }

  /**
    * \brief Посылает в сокет данные.
    * \details Функция отправит данные, только если
    * произведено подключение. В противном случае она просто
    * выдаст метрики сокета для предоставленных данных.
    * \param data - массив с данными для отправки.
    */
  void BaseUDPSocket::send(const QByteArray& data) noexcept
  {
    if(m_address.isNull() or m_port == 0)
      qWarning().noquote() << "[UDP]" << name() << "is trying to write to null host";

    this->writeDatagram(data, m_address, m_port);
  }

  /// \brief Возвращает текущий порт сокета в виде <tt>uint16</tt>.
  uint16_t BaseUDPSocket::port() const noexcept { return m_port; }

  /// \brief Возвращает текущий адрес сокета в виде строки.
  QString BaseUDPSocket::addressString() const noexcept { return m_address.toString() + ":" + QString::number(m_port); }

  /// \brief Возвращает текущий \c QHostAddress сокета.
  QHostAddress BaseUDPSocket::hostAddress() const noexcept { return m_address; }

  /// \brief Возвращает текущий \c QHostAddress сокета в виде строки.
  QString BaseUDPSocket::hostAddressString() const noexcept { return m_address.toString(); }

  void BaseUDPSocket::readSocket() noexcept
  {
    QByteArray buffer(static_cast<int>(pendingDatagramSize()), 0x0);

    while(hasPendingDatagrams())
      this->readDatagram(buffer.data(), buffer.size(), &m_address, &m_port);

    emit received(buffer);
  }

  /**
   * \brief Не имеет реализации.
   * \details Эта функция наследуется от интерфейса IConnectable и не имеет
   * реализации в этом классе.
   * \param address - сетевой адрес.
   */
  void BaseUDPSocket::start(const QHostAddress& address) noexcept { qCritical() << "NOT IMPLEMENTED"; }

  /**
    * \brief Производит попытку подключения к указанному адресу.
    * \param address - адрес в виде QHostAddress.
    * \param _port - порт для подключения.
    */
  void BaseUDPSocket::start(const QHostAddress& address, uint16_t _port) noexcept
  {
    qInfo().noquote() << "[UDP] Starting" << name() << "UDP socket on" << address;
    m_address = address;
    m_port = _port;

    this->bind(hostAddress(), port());
    emit metrics("Socket opened on " + addressString(), 0, true);
  }
} // QuasarSDK
