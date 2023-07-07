/**
  * \class QuasarSDK::OutputRedirectServer quasarsdk_outputredirectserver.h <QuasarSDK/Utility/OutputRedirect>
  * \brief Класс для перенаправления вывода РЛС в отдельный Telnet сервер.
  * \details Запускает TCP-IP сервер на выбранном адресе и перенаправляет
  * в него любые массивы данных, приходящие в функцию push().
  * \extends QObject, IConnectable
  */

#include "quasarsdk_outputredirectserver.h"
#include <QtCore/QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

namespace QuasarSDK
{
  /// \brief Создает новый объект сервера перенаправления вывода с указанным родителем.
  OutputRedirectServer::OutputRedirectServer(QObject* parent)
      : QObject(parent)
      , m_server(new QTcpServer(this))
      , m_socket(nullptr)
  {
    connect(m_server, &QTcpServer::newConnection, this, &OutputRedirectServer::clientConnected);
  }

  /// \brief Удаляет объект и закрывает сервер.
  OutputRedirectServer::~OutputRedirectServer()
  {
    if(m_socket)
      delete m_socket;
    m_server->close();
  }

  /**
   * \brief Запускает сервер перенаправления вывода на указанном адресе.
   * \param address - адрес для запуска сервера в формате <tt>192.168.1.47:25565</tt>.
   */
  void OutputRedirectServer::start(const QString& address)
  {
    if(not address.contains(":") or address.split(":").size() > 2)
    {
      qCritical().noquote() << "[TCP] Provided incorrect IP:" << address;
      return;
    }

    QString ip = address.split(":").first();
    uint16_t port = address.split(":").last().toUInt();

    if(m_server->listen(QHostAddress(ip), port))
      qDebug() << "[REDIRECT] Server started successfully at" << address;
    else
      qCritical() << "[REDIRECT] Server failed to start";
  }

  /// \brief Останавливает сервер.
  void OutputRedirectServer::stop() noexcept { m_server->close(); }

  /**
   * \brief Отправляет данные в сервер.
   * \param data - данные для отправки.
   */
  void OutputRedirectServer::push(const QByteArray& data) noexcept
  {
    if(m_socket == nullptr)
      return;
    m_socket->write(data);
    m_socket->flush();
    m_socket->waitForBytesWritten();
  }

  void OutputRedirectServer::clientConnected()
  {
    if(m_socket != nullptr)
      delete m_socket;
    m_socket = m_server->nextPendingConnection();
  }

  /**
   * \brief Не имеет реализации.
   * \param address - QHostAddress.
   */
  void OutputRedirectServer::start(const QHostAddress& address) noexcept
  {
    qCritical() << "NOT IMPLEMENTED";
  }

  /**
   * \brief Запускает сервер перенаправления вывода на указанном адресе.
   * \param address - IPv4-адрес сервера.
   * \param port - порт, на котором будет запущен сервер.
   */
  void OutputRedirectServer::start(const QHostAddress& address, uint16_t port) noexcept
  {
    this->start(address.toString() + ":" + QString::number(port));
  }
} // QuasarSDK