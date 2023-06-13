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
#include "gui/terminal/vt100terminal.h"
#include "utils/vt100parser.h"

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
    , m_de10ping(new Pinger(this))
    , m_jetsonping(new Pinger(this))
    , m_navping(new Pinger(this))
    , m_utl1ping(new Pinger(this))
    , m_utl2ping(new Pinger(this))
{
    telemetrySocket = new TelemetrySocket(this, m_telemetry);

    qDebug() << "[NETWORK] Beginning network setup";

    m_network_delay_timer->start(100);
    QObject::connect(telemetrySocket, &TelemetrySocket::ping, this, [this](){ setNetworkDelay(0); });
    QObject::connect(telemetrySocket, &TelemetrySocket::socketMetrics, this, &Network::telemetrySocketMetrics);
    QObject::connect(m_network_delay_timer, &QTimer::timeout, this, [this](){ setNetworkDelay(networkDelay() + 0.1); });
    QObject::connect(execdSocket, &ExecdSocket::ping, this, [this](){ setNetworkDelay(0); });
    QObject::connect(execdSocket, &ExecdSocket::socketMetrics, this, &Network::execdSocketMetrics);
    QObject::connect(feedbackSocket, &FeedbackSocket::socketMetrics, this, &Network::feedbackSocketMetrics);
    QObject::connect(feedbackSocket, &FeedbackSocket::socketMetrics, this, [this](const QString& data, int, bool){
        auto st = utils::parse_vt100_string(data);
        //if(st.move_up and st.return_carriage)
            //GUI::VT100Terminal::get()->replaceLast(st.result);
        //else
        GUI::VT100Terminal::get()->append(st.result);
    });
    QObject::connect(feedbackSocket, &FeedbackSocket::diskSpaceReceived, this, [this](long free, long total) {
        float space = free / (float)total;
        remoteData()->setStorageSpace(space);
    });

    QObject::connect(tcpSocket, &TCPSocket::progressChanged, this, [this](float progress){ setTcpProgress(progress); });
    QObject::connect(tcpSocket, &TCPSocket::receivingFinished, this, [this](){ executeCommand(RemoteStorageStatus); });
    QObject::connect(tcpSocket, &TCPSocket::socketMetrics, this, &Network::lfsSocketMetrics);

    QObject::connect(m_de10ping, &Pinger::result, this, [this](int result){ remoteData()->setDe10ping(result); });
    QObject::connect(m_jetsonping, &Pinger::result, this, [this](int result){ remoteData()->setJetsonping(result); });
    QObject::connect(m_navping, &Pinger::result, this, [this](int result){ remoteData()->setNavping(result); });
    QObject::connect(m_utl1ping, &Pinger::result, this, [this](int result){ remoteData()->setUtl1ping(result); });
    QObject::connect(m_utl2ping, &Pinger::result, this, [this](int result){ remoteData()->setUtl2ping(result); });

    m_de10ping->start(0, CONFIG(remoteIP));
    m_jetsonping->start(0, CONFIG(jetsonIP));
    m_navping->start(0, CONFIG(navIP));
    m_utl1ping->start(0, CONFIG(utl1IP));
    m_utl2ping->start(0, CONFIG(utl2IP));

    QObject::connect(telemetry(), &Telemetry::seaLevelChanged, this, [this](){
        setArgument("--e0", telemetry()->seaLevel(), Form);
        setArgument("--e0", telemetry()->seaLevel(), Reform);
        setArgument("--e0", telemetry()->seaLevel(), Focus);
    });
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
        case Reboot: execdSocket->executeCommand(ExecdSocket::Reboot); break;
        case Poweroff: execdSocket->executeCommand(ExecdSocket::Poweroff); break;
        default: qWarning() << "[NETWORK] Invalid command type"; break;
    }
}

void Network::executeString(const QString &string) noexcept { execdSocket->executeCommand(string); }
QString Network::argument(const QString& key, ArgumentCategory category) const noexcept
{
    switch (category)
    {
        case Form: return execdSocket->list()->argument_list[key].value;
        case Focus: return execdSocket->list()->focus_argument_list[key].value;
        case Reform: return execdSocket->list()->reform_argument_list[key].value;
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

void Network::startTCPSocket(const QString &address) { tcpSocket->startServer(address); }
void Network::stopTCPSocket() { tcpSocket->stopServer(); }

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

}

