/**
  * \class QuasarSDK::BaseUDPSocket quasarsdk_baseudpsocket.h <QuasarSDK/Private/BaseUDPSocket>
  * \brief Базовый класс для сокетов, работающих по протоколу UDP.
  * \details Класс расширяет функционал QUdpSocket и добавляет
  * несколько важных функций и сигналов для удобства разработки.
  * Этот класс - родительский класс для всех
  * UDP-сокетов в комплекте разработчика РЛС "Квазар".
  * \note Для случаев, когда недопустимо склеивание или кеширование
  * входящих датаграмм, используйте класс #SeamlessUDPSocket как
  * основу для класса-сокета.
  * \extends QUdpSocket
  */

#include "quasarsdk_baseudpsocket.h"

namespace QuasarSDK
{
  /// \brief Создает новый объект BaseUDPSocket с указанным родителем.
  BaseUDPSocket::BaseUDPSocket(QObject* parent)
      :
      QUdpSocket(parent)
  {

  }

  /// \brief Вызывает метод QUdpSocket::disconnect() и удаляет объект.
  BaseUDPSocket::~BaseUDPSocket()
  {

  }

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
    * \return Результат выполнения функции.
    * \throws std::invalid_argument
    */
  bool BaseUDPSocket::start(const QString& address)
  {
    return false;
  }

  /// \brief Отключает сокет от адреса, если он был подключен.
  void BaseUDPSocket::stop() noexcept
  {

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

  }

  /// \brief Возвращает текущий порт сокета в виде <tt>uint16</tt>.
  uint16_t BaseUDPSocket::port() const noexcept
  {
    return 0;
  }

  /// \brief Возвращает текущий адрес сокета в виде строки.
  QString BaseUDPSocket::addressString() const noexcept
  {
    return QString();
  }

  /// \brief Возвращает текущий \c QHostAddress сокета.
  QHostAddress BaseUDPSocket::hostAddress() const noexcept
  {
    return QHostAddress();
  }

  /// \brief Возвращает текущий \c QHostAddress сокета в виде строки.
  QString BaseUDPSocket::hostAddressString() const noexcept
  {
    return QString();
  }

  void BaseUDPSocket::readSocket() noexcept
  {

  }
} // QuasarSDK