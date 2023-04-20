#include "telemetrysocket.h++"
#include <QtCore/QTimer>
#include <QtCore/QDebug>

using namespace Network;

TelemetrySocket::TelemetrySocket(QObject* parent, Telemetry* output)
    : AbstractUDPSocket{parent}
    , m_updateTimer(new QTimer(this))
    , m_output(output)
{
    QObject::connect(m_updateTimer, &QTimer::timeout, this, [this](){
        this->send(REQUEST_KEY);
    });
    QObject::connect(this, &TelemetrySocket::received, this, &TelemetrySocket::processTelemetry);
}

void TelemetrySocket::start()
{
    m_updateTimer->start((int)(frequency() * 1'000));
    qDebug().noquote() << "[TELEMETRY] Started reading at frequency of" << frequency();
}

void TelemetrySocket::stop()
{
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
}
