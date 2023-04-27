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

float TelemetrySocket::frequency() const { return m_frequency; }
void TelemetrySocket::setFrequency(float other) {
    if (qFuzzyCompare(m_frequency, other)) return;
    m_frequency = other;
    emit frequencyChanged();
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

    output->setLatitude(Utilities::Numeric::radiansToDegrees(received.latitude));
    output->setLongitude(Utilities::Numeric::radiansToDegrees(received.longitude));
    output->setAltitude(received.altitude);
    output->setVelocityCourse(received.velocity_course);
    output->setVelocityEast(received.velocity_east);
    output->setVelocityNorth(received.velocity_north);
    output->setVelocityCourse(received.velocity_course);
    output->setPitch(Utilities::Numeric::radiansToDegrees(received.pitch));
    output->setRoll(Utilities::Numeric::radiansToDegrees(received.roll));
    output->setYaw(Utilities::Numeric::radiansToDegrees(received.yaw));
    output->setCourse(Utilities::Numeric::radiansToDegrees(received.course));
    output->setTime(received.time);

    uint16_t crc = CRC_CHECK ? Utilities::crc16_ccitt((const char*)&received, sizeof(Network::TelemetryDatagram) - sizeof(uint16_t))
                             : received.crc16;
    if(crc != received.crc16)
        qWarning().noquote().nospace() << "[TELSOCK] Checksum mismatch [" << crc << " : " << received.crc16 << "]";

    emit rawData("latitude" + QString::number(output->latitude()));
    emit ping();
}

void TelemetrySocket::requestTelemetry()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    TelemetryRequest request = { MARKER, 0x01, (uint16_t)(this->port()), (int32_t)(this->frequency() * 1'000), 0 };
    uint16_t crc = Utilities::crc16_ccitt((const char*)&request, sizeof(TelemetryRequest) - sizeof(uint16_t));
    request.crc16 = crc;

    stream << request;

    this->send(buffer);
}
