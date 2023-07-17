/**
 * \ingroup sdk_network
 * \class QuasarSDK::TCPServer CTCPServer.h <QuasarSDK/Networking/CTCPServer.h>
 * \brief Класс для приема больших файлов с РЛС по протоколу TCP-IP.
 * \details Используется для приема цельных пакетов с телескопическими и
 * полосовыми изображениями с РЛС, а также для приёма .zip-архивов.
 *
 * Предоставляет отладочные метрики по аналогии с классами-наследниками
 * BaseUDPSocket.
 * \extends QObject, IConnectable
 */

#include "CTCPServer.h"
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include "CConfig.h"

namespace QuasarSDK
{
  /// \brief Создает новый объект TCPServer с указанным родителем.
  TCPServer::TCPServer(QObject* parent)
    : QObject(parent)
    , server(new QTcpServer(this))
    , timer(new QTimer(this))
    , splitIndex(0)
    , fileSize(0)
    , socket(nullptr)
  {
    connect(server, &QTcpServer::newConnection, this, &TCPServer::clientConnected);
    connect(timer, &QTimer::timeout, this, &TCPServer::connectionTimeout);

    timer->setInterval(Config::get()->value<int>("TCP_SERVER_TIMEOUT"));
  }

  /**
   * \brief Запускает TCP-IP сервер на указанном адресе.
   * \param address - строка адреса в формате <tt>192.168.1.10:10000</tt>.
   */
  void TCPServer::start(const QString& address)
  {
    if(not address.contains(":") or address.split(":").size() > 2)
    {
      qCritical().noquote() << "[TCP] Provided incorrect IP:" << address;
      return;
    }

    QString ip = address.split(":").first();
    uint16_t port = address.split(":").last().toUInt();
    if(not server->listen(QHostAddress(ip), port))
    {
      qCritical() << "[TCP] TCP-IP server has failed to start.";
      return;
    }

    qInfo() << "[TCP] TCP-IP server started.";
  }

  /// \brief Останавливает запущенный TCP-IP сервер.
  void TCPServer::stop() noexcept
  {
    server->close();
    qInfo() << "[TCP] TCP-IP server closed connection";
  }

  void TCPServer::readFileInfo(QByteArray data)
  {
    readFile = &TCPServer::readFileBody;

    uint8_t i = data.indexOf('\n') + 1;
    filename = data.left(i - 1).data();
    memcpy(&fileSize, data.mid(i, sizeof(uint32_t)).data(), sizeof(uint32_t));

    i += sizeof(uint32_t);

    qDebug().noquote() << "[TCP] LFS filename:" << filename;
    qDebug().noquote() << "[TCP] LFS size:" << QString::number(fileSize) << "kB";
    emit metrics(filename, filename.size(), false);
    emit metrics(QString::number(fileSize), 32, false);

    data.remove(0, i);

    timer->stop();
    timer->start();
    (this->*readFile)(data);
  }

  void TCPServer::readFileBody(QByteArray data)
  {
    timer->stop();
    timer->start();

    if(data.size())
      imageData.append(data);

    this->progress();
    emit metrics("DATA with size of " + QString::number(data.size()), data.size(), false);
  }

  void TCPServer::clientConnected()
  {
    qInfo() << "[TCP] SAR connected";
    emit metrics("Started receiving", 0, true);

    socket = server->nextPendingConnection();
    if(not socket)
    {
      qCritical() << "[TCP] NextPendingConnection returned nullptr. Aborting connection";
      return;
    }

    connect(socket, &QTcpSocket::readyRead, this, &TCPServer::serverRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPServer::clientDisconnected);
    imageData.clear();
    readFile = &TCPServer::readFileInfo;
    success = false;
    timer->start();
    splitIndex = 0;

    qInfo() << "[TCP] SAR ready to send image";
  }

  void TCPServer::serverRead() { (this->*readFile)(socket->readAll()); }

  void TCPServer::clientDisconnected()
  {
    emit metrics("Finished receiving", 0, true);
    socket->close();
    timer->stop();

    (fileSize == imageData.size()) ? qInfo() << "[TCP] Package fully received from SAR"
                                   : qWarning() << "[TCP] Something went wrong in receiving SAR image";

    emit received(imageData, filename);
  }

  void TCPServer::connectionTimeout() { socket->close(); }

  void TCPServer::progress()
  {
    float percent = static_cast<float>(imageData.size()) / static_cast<float>(fileSize);
    emit progressChanged(percent * 100);
  }

  /**
   * \brief Не имеет реализации.
   * \details Функция унаследована от интерфейса IConnectable и не имеет реализации
   * в этом классе.
   * \param address - QHostAddress.
   */
  void TCPServer::start(const QHostAddress& address) noexcept { qCritical() << "NOT IMPLEMENTED"; }

  /**
   * \brief Запускает TCP-IP сервер на указанном адресе.
   * \param address - IPv4-адрес сервера.
   * \param port - порт, на котором должен быть запущен сервер.
   */
  void TCPServer::start(const QHostAddress& address, uint16_t port) noexcept
  {
    if(not server->listen(address, port))
    {
      qCritical() << "[TCP] TCP-IP server has failed to start.";
      return;
    }

    qInfo() << "[TCP] TCP-IP server started.";
  }
} // QuasarSDK