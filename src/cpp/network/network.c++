#include "network.h++"
#include "telemetry/telemetry.h++"
#include "telemetry/telemetrysocket.h++"
#include <QtCore/QDebug>
#include <QtCore/QTimer>

Network::Network* Network::Network::instance = nullptr;
Network::Network* Network::Network::get(QObject *parent) {
    if(instance != nullptr)
        return instance;
    instance = new Network(parent);
    return instance;
}

Network::Network::Network(QObject* parent)
    : QObject{parent}
    , m_telemetry(new Telemetry(this))
    , telemetrySocket(new TelemetrySocket(this, m_telemetry))
    , m_network_delay_timer(new QTimer(this))
{
    qDebug() << "[NETWORK] Beginning network setup";
    m_network_delay_timer->start(100);
    QObject::connect(telemetrySocket, &TelemetrySocket::ping, this, [this](){
        setNetworkDelay(0);
    });
    QObject::connect(m_network_delay_timer, &QTimer::timeout, this, [this](){
        setNetworkDelay(networkDelay() + 0.1);
    });
}


void Network::Network::startTelemetrySocket(float frequency)
{
    this->telemetrySocket->setFrequency(frequency);
    this->telemetrySocket->start("127.0.0.1:9955");
}

void Network::Network::stopTelemetrySocket()
{
    this->telemetrySocket->stop();
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

        if(networkDelay() >= DISCONNECT_DELAY_THRESHOLD)
            setConnected(0);
        else if(networkDelay() >= SEMICONNECT_DELAY_THRESHOLD)
            setConnected(1);
        else
            setConnected(2);
    }

    int Network::connected() const { return m_connected; }
    void Network::setConnected(int other) {
        if (m_connected == other) return;
        m_connected = other;
        emit connectedChanged();
    }
}
