#include "telemetrysocket.h++"
#include "telemetry.h++"
#include "telemetrydatagram.h++"
#include "utils/utils.h++"
#include "utils/numeric.h++"
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtCore/QDataStream>

using namespace Network;

TelemetrySocket::TelemetrySocket(QObject* parent, Telemetry* output)
    : AbstractUDPSocket{parent}
    , m_updateTimer(new QTimer(this))
    , output(output)
{
    QObject::connect(m_updateTimer, &QTimer::timeout, this, &TelemetrySocket::requestTelemetry);
    QObject::connect(this, &TelemetrySocket::received, this, &TelemetrySocket::processTelemetry);
}

void TelemetrySocket::start(const QString& address)
{
    this->connect(address);
    this->requestTelemetry();
    m_updateTimer->start((int)(30 * 1'000));
    qDebug().noquote() << "[TELEMETRY] Started reading at frequency of" << 1 / frequency() << "Hz";
}

void TelemetrySocket::stop()
{
    this->disconnect();
    m_updateTimer->stop();
    qDebug() << "[TELEMETRY] Stopped reading";
}

void TelemetrySocket::processTelemetry(QByteArray data)
{
    uint32_t marker = *(uint32_t*)data.data();
    if(marker != RECV_MARKER_LITTLE) {
        qWarning() << "[TELEMETRY] Triggered first marker mismatch";
        return;
    }

    QDataStream stream(&data, ReadOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    TelemetryDatagram received;
    stream >> received;

    if(received.marker != RECV_MARKER_BIG) {
        qWarning() << "[TELEMETRY] Triggered second marker mismatch";
        return;
    }

    output->setLatitude(received.latitude);
    output->setLongitude(received.longitude);
    output->setAltitude(received.altitude);
    output->setVelocityCourse(received.velocity_course * 3.6);
    output->setVelocityEast(received.velocity_east * 3.6);
    output->setVelocityNorth(received.velocity_north * 3.6);
    output->setVelocityCourse(received.velocity_course * 3.6);
    output->setPitch(Utilities::Numeric::radiansToDegrees(received.pitch));
    output->setRoll(Utilities::Numeric::radiansToDegrees(received.roll));
    output->setYaw(Utilities::Numeric::radiansToDegrees(received.yaw));
    output->setCourse(Utilities::Numeric::radiansToDegrees(received.course));
    output->setTime(received.time);
    output->setSatellites(received.satellites);

    uint16_t crc = CRC_CHECK ? Utilities::crc16_ccitt((const char*)&received, sizeof(Network::TelemetryDatagram) - sizeof(uint16_t))
                             : received.crc16;
    if(crc != received.crc16)
        qWarning().noquote().nospace() << "[TELSOCK] Checksum mismatch [" << crc << " : " << received.crc16 << "]";

    emit socketMetrics("[ IN  ] 0x" + QString::number(received.marker, 16) + " " + QString::number(received.version) + " "
                 + QString::number(received.latitude, 'f', 7) + " " + QString::number(received.longitude, 'f', 7)  + " "
                 + QString::number(received.altitude, 'f', 2) + " " + QString::number(received.velocity_course, 'f', 1) + " "
                 + QString::number(received.velocity_east, 'f', 1) + " " + QString::number(received.velocity_north, 'f', 1) + " "
                 + QString::number(received.velocity_vertical, 'f', 1) + " " + QString::number(received.pitch, 'f', 2) + " "
                 + QString::number(received.roll, 'f', 2) + " " +  QString::number(received.yaw, 'f', 2) + " "
                 + QString::number(received.course, 'f', 2) + " " + QString::number(received.time) + " " + QString::number(received.satellites)
                           + " 0x" + QString::number(received.crc16, 16), sizeof(output));
    emit ping();
}

void TelemetrySocket::requestTelemetry()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    TelemetryRequest request = { MARKER, 0x01, (uint16_t)(this->port()), (uint32_t)(this->frequency() * 1'000), 0 };
    uint16_t crc = Utilities::crc16_ccitt((const char*)&request, sizeof(TelemetryRequest) - sizeof(uint16_t));
    request.crc16 = crc;

    stream << request;

    this->send(buffer);
    emit socketMetrics("[ OUT ] 0x" + QString::number(request.marker, 16) + " " + QString::number(request.init_flag) + " "
                        + QString::number(request.port) + " " + QString::number(request.interval_ms)
                        + " 0x" + QString::number(request.crc16, 16), sizeof(request));
}
