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
}
