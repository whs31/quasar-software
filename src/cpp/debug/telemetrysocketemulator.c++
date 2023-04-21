#include "telemetrysocketemulator.h++"
#include <QtCore/QDebug>
#include <QtCore/QDataStream>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

using namespace Debug;

TelemetrySocketEmulator::TelemetrySocketEmulator(QObject* parent)
    : QObject{parent}
    , socket(new QUdpSocket(this))
    , m_hostaddress(QHostAddress())
    , m_port(0)
{
    QObject::connect(socket, &QUdpSocket::readyRead, this, &TelemetrySocketEmulator::read);
}

TelemetrySocketEmulator::~TelemetrySocketEmulator()
{
    if(socket)
        socket->close();
}

void TelemetrySocketEmulator::startTelemetryServer(const QString& address)
{
    qInfo().noquote() << "[DEBUG] Starting telemetry server emulator at" << address;
    qDebug() << socket;
    m_hostaddress.setAddress(address.split(":").first());
    m_port = address.split(":").last().toUShort();
    if(not address.contains(":"))
    {
        qCritical() << "[DEBUG] Incorrect address";
        return;
    }

    socket->bind(m_hostaddress, m_port);
}

void TelemetrySocketEmulator::stop()
{
    qInfo() << "[DEBUG] Stopping telemetry server emulator...";
    m_hostaddress.clear();
    m_port = 0;
    socket->close();
}

void TelemetrySocketEmulator::read()
{
    QByteArray buf;
    buf.resize(socket->pendingDatagramSize());
    while(socket->hasPendingDatagrams())
        socket->readDatagram(buf.data(), (int64_t)socket->pendingDatagramSize(), &m_hostaddress, &m_port);
    qDebug() << buf;
}

