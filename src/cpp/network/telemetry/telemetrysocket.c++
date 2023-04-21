#include "telemetrysocket.h++"
#include "telemetry.h++"
#include "telemetrydatagram.h++"
#include "utils/utils.h++"
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
    emit ping();
    QDataStream stream(&data, ReadOnly);
    TelemetryDatagram received;
    stream >> received;

//    qDebug().noquote().nospace() << "[TELSOCK] RECEIVED PACKAGE " << Qt::hex << "<b>0x" << received.marker << " 0x" << received.version
//                                 << Qt::dec << "</b> lat[<b>" << received.latitude << "</b>] lon[<b>"<< received.longitude << "</b>] alt[<b>"
//                                 << received.altitude << "</b>]";
    output->setLatitude(received.latitude);
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
