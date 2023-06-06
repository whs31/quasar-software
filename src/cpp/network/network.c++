#include "network.h"
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include "config/config.h"
#include "telemetry/telemetry.h"
#include "telemetry/telemetrysocket.h"
#include "execd/execdsocket.h"
#include "execd/execdargumentlist.h"
#include "execd/feedbacksocket.h"
#include "tcpsocket.h"
#include "ping.h"

namespace Network {

Network::Network(QObject* parent)
    : QObject{parent}
    , m_telemetry(new Telemetry(this))
    , m_remoteData(new RemoteData(this))
    , execdSocket(new ExecdSocket(this))
    , feedbackSocket(new FeedbackSocket(this))
    , tcpSocket(new TCPSocket(this))
    , m_network_delay_timer(new QTimer(this))
    , m_networkDelay(DISCONNECT_DELAY_THRESHOLD + .1f)
    , m_connected(0)
    , m_de10Status((int)PingStatus::Idle)
    , m_jetsonStatus((int)PingStatus::Idle)
    , m_de10ping(new Pinger(this))
    , m_jetsonping(new Pinger(this))
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
    QObject::connect(telemetrySocket, &TelemetrySocket::socketMetrics, this, &Network::telemetrySocketMetrics);
    QObject::connect(feedbackSocket, &FeedbackSocket::socketMetrics, this, &Network::feedbackSocketMetrics);
    QObject::connect(execdSocket, &ExecdSocket::socketMetrics, this, &Network::execdSocketMetrics);
    QObject::connect(tcpSocket, &TCPSocket::socketMetrics, this, &Network::lfsSocketMetrics);

    QObject::connect(feedbackSocket, &FeedbackSocket::diskSpaceReceived, this, [this](long free, long total) {
        float space = free / (float)total;
        remoteData()->setStorageSpace(space);
    });

    QObject::connect(tcpSocket, &TCPSocket::progressChanged, this, [this](float progress){
        setTcpProgress(progress);
    });

    QObject::connect(m_de10ping, &Pinger::result, this, [this](int result){
        setDe10Status(result);
    });

    QObject::connect(m_jetsonping, &Pinger::result, this, [this](int result){
        setJetsonStatus(result);
    });

    m_de10ping->start(0, CONFIG(remoteIP));
    m_jetsonping->start(0, "192.168.1.48");
}

void Network::startTelemetrySocket(const QString& address, float frequency)
{
    telemetrySocket->setFrequency(frequency);
    telemetrySocket->start(address);
}

void Network::stopTelemetrySocket() { telemetrySocket->stop(); }

void Network::startExecdSocket(const QString& execd_address, const QString& feedback_address)
{
    execdSocket->start(execd_address);
    feedbackSocket->start(feedback_address);
}

void Network::stopExecdSocket()
{
    execdSocket->stop();
    feedbackSocket->stop();
}

void Network::executeCommand(const NetworkCommand command) noexcept
{
    switch (command)
    {
        case FormImage: execdSocket->executeCommand(ExecdSocket::FormImage); break;
        case FocusImage: execdSocket->executeCommand(ExecdSocket::FocusImage); break;
        case ReformImage: execdSocket->executeCommand(ExecdSocket::ReformImage); break;
        case RemoteStorageStatus: execdSocket->executeCommand(ExecdSocket::RemoteStorageStatus); break;
        case ClearRemoteStorage: execdSocket->executeCommand(ExecdSocket::ClearRemoteStorage); break;
        case Ping: execdSocket->executeCommand(ExecdSocket::Ping); break;
        default: qWarning() << "[NETWORK] Invalid command type"; break;
    }
}

QString Network::argument(const QString& key, ArgumentCategory category) const noexcept
{
    switch (category)
    {
        case Form: return execdSocket->list()->argument_list[key].value; break;
        case Focus: return execdSocket->list()->focus_argument_list[key].value; break;
        case Reform: return execdSocket->list()->reform_argument_list[key].value; break;
        default: return "Argument Category Error"; break;
    }
}

void Network::setArgument(const QString& key, const QVariant& value, ArgumentCategory category) noexcept
{
    switch (category)
    {
        case Form: execdSocket->list()->argument_list[key].set(value); break;
        case Focus: execdSocket->list()->focus_argument_list[key].set(value); break;
        case Reform: execdSocket->list()->reform_argument_list[key].set(value); break;
        default: qCritical() << "[NETWORK] Invalid category for argument provided"; break;
    }
}

void Network::startTCPSocket(const QString &address)
{
    tcpSocket->startServer(address);
}

void Network::stopTCPSocket()
{
    tcpSocket->stopServer();
}

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

float Network::tcpProgress() const { return m_tcpProgress; }
void Network::setTcpProgress(float other) {
    if (qFuzzyCompare(m_tcpProgress, other))
        return;
    m_tcpProgress = other;
    emit tcpProgressChanged();
}

int Network::de10Status() const { return m_de10Status; }
void Network::setDe10Status(int o) {
    if (m_de10Status == o)
        return;
    m_de10Status = o;
    emit de10StatusChanged();
}

int Network::jetsonStatus() const { return m_jetsonStatus; }
void Network::setJetsonStatus(int o) {
    if (m_jetsonStatus == o)
        return;
    m_jetsonStatus = o;
    emit jetsonStatusChanged();
}

}

