#include "abstractudpsocket.h++"
#include <QtCore/QDebug>

using namespace Network;

AbstractUDPSocket::AbstractUDPSocket(QObject* parent)
    : QUdpSocket{parent}
{

}

AbstractUDPSocket::~AbstractUDPSocket()
{
    this->disconnect();
}

bool Network::AbstractUDPSocket::connect(const QString& address)
{
    QObject::connect(this, &QUdpSocket::readyRead, this, &AbstractUDPSocket::readSocket);
    if(not address.contains(":")) {
        qCritical() << "[SOCKET] Incorrect host address";
        return false;
    }
    QHostAddress ip(address.split(":").constFirst());
    bool convert_result = false;
    quint16 port = address.split(":").last().toUInt(&convert_result);
    if(not convert_result) {
        qCritical() << "[SOCKET] Incorrect port";
        return false;
    }
    qDebug().noquote() << "[SOCKET] Binding UDP socket on" << address;
    m_hostaddress = ip;
    m_port = port;
    return this->bind(ip, port);
}

void AbstractUDPSocket::disconnect()
{
    QObject::disconnect(this, &QUdpSocket::readyRead, this, &AbstractUDPSocket::readSocket);
    qDebug().noquote() << "[SOCKET] Disconnecting from" << this->peerAddress();
    this->close();
    m_hostaddress.clear();
    m_port = 0;
    emit socketDisconnected();
}

bool AbstractUDPSocket::send(QByteArray data)
{
    if(m_hostaddress.isNull() or m_port == 0) {
        qWarning() << "[SOCKET] Trying to write to null host";
        return false;
    }
    return this->writeDatagram(data, m_hostaddress, m_port);
}

void AbstractUDPSocket::readSocket()
{
    if(m_hostaddress.isNull() or m_port == 0) {
        qWarning() << "[SOCKET] Trying to read from null host";
        return;
    }

    QByteArray buffer;
    buffer.resize(this->pendingDatagramSize());
    while(this->hasPendingDatagrams())
        this->readDatagram(buffer.data(), (int64_t)this->pendingDatagramSize(), &m_hostaddress, &m_port);

    emit received(buffer);
}
