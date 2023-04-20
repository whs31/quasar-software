#include "network.h++"
#include "telemetry/telemetry.h++"
#include "telemetry/telemetrysocket.h++"
#include <QtCore/QDebug>

Network::Network* Network::Network::instance = nullptr;
Network::Network* Network::Network::get(QObject *parent) {
    if(instance != nullptr)
        return instance;
    instance = new Network(parent);
    return instance;
}

void Network::Network::startTelemetrySocket(float frequency)
{
    this->telemetrySocket->setFrequency(frequency);
    this->telemetrySocket->start();
}

void Network::Network::stopTelemetrySocket()
{
    this->telemetrySocket->stop();
}

Network::Network::Network(QObject *parent)
    : QObject{parent}
    , m_telemetry(new Telemetry(this))
    , telemetrySocket(new TelemetrySocket(this, m_telemetry))
{
    qDebug() << "[NETWORK] Beginning network setup";

}



namespace Network {
    Telemetry *Network::telemetry() const { return m_telemetry; }
    void Network::setTelemetry(Telemetry* other) {
        if (m_telemetry == other)
            return;
        m_telemetry = other;
        emit telemetryChanged();
    }

    float Network::networkDelay() const { return m_networkDelay; }
    void Network::setNetworkDelay(float other) {
        if (qFuzzyCompare(m_networkDelay, other)) return;
        m_networkDelay = other;
        emit networkDelayChanged();
    }
}
