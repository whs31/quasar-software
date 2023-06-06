#include "ping.h"
#include <stdexcept>
#include <QtCore/QProcess>
#include <QtCore/QTimer>

namespace Network
{

Pinger::Pinger(QObject *parent)
    : QObject{parent}
    , t(new QTimer(this))
    , ch(new QProcess(this))
    , addr("127.0.0.1")
    , m_args("")
{
    ch->setProcessChannelMode(QProcess::MergedChannels);
    connect(ch, &QProcess::readyRead, this, &Pinger::recv);
    connect(t, &QTimer::timeout, this, &Pinger::ping);
}

void Pinger::start(uint32_t interval, const QString& address, const vector<QString> args)
{
    if(address.split('.').size() != 4)
        throw std::invalid_argument("Invalid address is provided to ping");

    addr = address;

    for(const auto& arg : args)
        m_args += QString(arg + " ");

    if(interval == 0)
        ch->start("ping", QStringList() << QString(address) );
    else
        t->start(interval);
}

void Pinger::stop() noexcept { t->stop(); }
void Pinger::ping() { ch->start("ping", QStringList() << QString(addr) ); }

void Pinger::recv()
{
    auto data = ch->readAll();
    bool success = false;
    #ifdef Q_OS_WIN
    success = data.contains("TTL=");
    #else
    success = data.contains("time=");
    #endif

    emit result(success ? (int)PingStatus::Success : (int)PingStatus::Timeout);
}

} // Network
