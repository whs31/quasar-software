#include "telemetrysocketemulator.h++"
#include "utils/numeric.h++"
#include "utils/utils.h++"
#include <QtCore/QDebug>
#include <QtCore/QDataStream>
#include <QtCore/QTimer>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDateTime>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>
#include <cmath>

using namespace Debug;

TelemetrySocketEmulator::TelemetrySocketEmulator(QObject* parent)
    : QObject{parent}
    , socket(new QUdpSocket(this))
    , timer(new QTimer(this))
    , stopTimer(new QTimer(this))
    , m_hostaddress(QHostAddress())
    , m_port(0)
{
    stopTimer->setSingleShot(true);
    QObject::connect(socket, &QUdpSocket::readyRead, this, &TelemetrySocketEmulator::read);
    QObject::connect(stopTimer, &QTimer::timeout, this, [this](){
        timer->stop();
        qWarning() << "[DEBUG] No requests in 45 seconds, shutting down...";
    });
    QObject::connect(timer, &QTimer::timeout, this, &TelemetrySocketEmulator::sendTelemetry);
}

TelemetrySocketEmulator::~TelemetrySocketEmulator()
{
    if(socket)
        socket->close();
}

void TelemetrySocketEmulator::startTelemetryServer(const QString& address)
{
    qInfo().noquote() << "[DEBUG] Starting telemetry server emulator at" << address;
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

    QDataStream stream(&buf, QIODevice::ReadWrite);
    stream.setByteOrder(QDataStream::BigEndian);

    Network::TelemetryRequest received;
    stream >> received;

    qDebug().noquote().nospace() << "[TELSRV] RECEIVED PACKAGE " << Qt::hex << "<b>0x" << received.marker << " 0x" << received.init_flag
                                 << Qt::dec << "</b> port[<b>" << received.port << "</b>] interval[<b>"<< received.interval_ms << "</b>] crc[<b>" << received.crc16 << "</b>]";
    if(received.marker != MARKER)
    {
        qWarning() << "[DEBUG] Marker mismatch in telemetry emulator datagram";
        return;
    }

    timer->start(received.interval_ms);
    stopTimer->start(45'000); // will shutdown in 30 s
}

void TelemetrySocketEmulator::sendTelemetry()
{
    if(m_hostaddress.isNull() or m_port == 0) {
        qWarning() << "[DEBUG] Trying to write to null host (debug socket)";
        return;
    }

    Network::TelemetryDatagram datagram = this->generateTelemetry();
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << datagram;

    socket->writeDatagram(buffer, m_hostaddress, m_port);
}

Network::TelemetryDatagram TelemetrySocketEmulator::generateTelemetry()
{
    double yaw = local_data.yaw += (QRandomGenerator::global()->generateDouble() - 0.1);
    Network::TelemetryDatagram datagram = {
        0x55AA55AA,
        0x01,
        Utilities::Numeric::degreesToRadians(local_data.latitude += (sin(local_data.velocity) / 100)),
        Utilities::Numeric::degreesToRadians(local_data.longitude += (cos(local_data.velocity) / 100)),
        local_data.altitude += (QRandomGenerator::global()->generateDouble() - 0.3),
        local_data.velocity += (QRandomGenerator::global()->generateDouble() - 0.3),
        sin(local_data.velocity),
        cos(local_data.velocity),
        local_data.velocity_vertical,
        Utilities::Numeric::degreesToRadians(local_data.pitch += (QRandomGenerator::global()->generateDouble() - 0.1)),
        Utilities::Numeric::degreesToRadians(local_data.roll += (QRandomGenerator::global()->generateDouble() - 0.1)),
        Utilities::Numeric::degreesToRadians(yaw),
        Utilities::Numeric::degreesToRadians(yaw),
        (uint64_t)QDateTime::currentSecsSinceEpoch(),
        true,
        0
    };
    uint16_t crc = Utilities::crc16_ccitt((const char*)&datagram, sizeof(Network::TelemetryDatagram) - sizeof(uint16_t));
    datagram.crc16 = crc;

    return datagram;
}

