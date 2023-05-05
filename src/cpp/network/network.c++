#include "network.h++"
#include "telemetry/telemetry.h++"
#include "telemetry/telemetrysocket.h++"
#include "execd/execdsocket.h++"
#include "execd/feedbacksocket.h++"
#include "tcpsocket.h++"
#include <QtCore/QDebug>
#include <QtCore/QTimer>

Network::Network* Network::Network::instance = nullptr;
Network::Network* Network::Network::get(QObject* parent) {
    if(instance != nullptr)
        return instance;
    instance = new Network(parent);
    return instance;
}

Network::Network::Network(QObject* parent)
    : QObject{parent}
    , m_telemetry(new Telemetry(this))
    , m_remoteData(new RemoteData(this))
    , execdSocket(new ExecdSocket(this))
    , feedbackSocket(new FeedbackSocket(this))
    , tcpSocket(new TCPSocket(this))
    , m_network_delay_timer(new QTimer(this))
{
    telemetrySocket = new TelemetrySocket(this, m_telemetry);

    qDebug() << "[NETWORK] Beginning network setup";
    m_network_delay_timer->start(100);
    QObject::connect(telemetrySocket, &TelemetrySocket::ping, this, [this](){
        setNetworkDelay(0);
    });
    QObject::connect(m_network_delay_timer, &QTimer::timeout, this, [this](){
        setNetworkDelay(networkDelay() + 0.1);
    });
    QObject::connect(execdSocket, &ExecdSocket::ping, this, [this](){
        setNetworkDelay(0);
    });
    QObject::connect(telemetrySocket, &TelemetrySocket::rawData, this, &Network::telsock);
    //! @todo execdsock
    QObject::connect(feedbackSocket, &FeedbackSocket::rawData, this, &Network::feedbacksock);

    QObject::connect(feedbackSocket, &FeedbackSocket::diskSpaceReceived, this, [this](long free, long total) {
        float space = free / (float)total;
        remoteData()->setStorageSpace(space);
    });
}

void Network::Network::startTelemetrySocket(const QString& address, float frequency)
{
    telemetrySocket->setFrequency(frequency);
    telemetrySocket->start(address);
}

void Network::Network::stopTelemetrySocket()
{
    telemetrySocket->stop();
}


void Network::Network::startExecdSocket(const QString& execd_address, const QString& feedback_address)
{
    execdSocket->start(execd_address);
    feedbackSocket->start(feedback_address);
}

void Network::Network::stopExecdSocket()
{
    execdSocket->stop();
    feedbackSocket->stop();
}

void Network::Network::executeCommand(const QString& command)
{

}

void Network::Network::startTCPSocket(const QString &address)
{
    tcpSocket->startServer(address);
}

void Network::Network::stopTCPSocket()
{
    tcpSocket->stopServer();
}

namespace Network {
    Telemetry* Network::telemetry() const { return m_telemetry; }
    void Network::setTelemetry(Telemetry* other) {
        if (m_telemetry == other)
            return;
        m_telemetry = other;
        emit telemetryChanged();
    }

    RemoteData* Network::remoteData() const { return m_remoteData; }
    void Network::setRemoteData(RemoteData* other) {
        if (m_remoteData == other)
            return;
        m_remoteData = other;
        emit remoteDataChanged();
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
