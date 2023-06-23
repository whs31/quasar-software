#include "abstractudpsocket.h"
#include <QtCore/QDebug>

namespace Networking
{

  UDPSocketBase::UDPSocketBase(QObject* parent)
    : QUdpSocket{parent}
  {}

  UDPSocketBase::~UDPSocketBase() { this->disconnect(); }

  bool UDPSocketBase::connect(const QString& address)
  {
    QObject::connect(this, &QUdpSocket::readyRead, this, &UDPSocketBase::readSocket, Qt::DirectConnection);

    if(not address.contains(":"))
    {
      qCritical() << "[SOCKET] Incorrect host address";
      return false;
    }
    QHostAddress ip(address.split(":").constFirst());
    bool convert_result = false;
    quint16 port = address.split(":").last().toUInt(&convert_result);
    if(not convert_result)
    {
      qCritical() << "[SOCKET] Incorrect port";
      return false;
    }
    qDebug().noquote() << "[SOCKET] Binding UDP socket on" << address;
    m_hostaddress = ip;
    m_port = port;
    return this->bind(ip, port);
  }

  void UDPSocketBase::disconnect()
  {
    QObject::disconnect(this, &QUdpSocket::readyRead, this, &UDPSocketBase::readSocket);
    qDebug().noquote() << "[SOCKET] Disconnecting from" << this->peerAddress();
    this->close();
    m_hostaddress.clear();
    m_port = 0;

    emit socketDisconnected();
  }

  bool UDPSocketBase::send(QByteArray data)
  {
    if(m_hostaddress.isNull() or m_port == 0)
    {
      qWarning() << "[SOCKET] Trying to write to null host";
      return false;
    }
    return this->writeDatagram(data, m_hostaddress, m_port);
  }

  uint16_t UDPSocketBase::port() const noexcept { return m_port; }

  void UDPSocketBase::readSocket()
  {
    if(m_hostaddress.isNull() or m_port == 0)
    {
      qWarning() << "[SOCKET] Trying to read from null host";
      return;
    }

    QByteArray buffer(pendingDatagramSize(), 0x0);

    while(hasPendingDatagrams())
      this->readDatagram(buffer.data(), buffer.size(), &m_hostaddress, &m_port);

    emit received(buffer);
  }

} // Networking