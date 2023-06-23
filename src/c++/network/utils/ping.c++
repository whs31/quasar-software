#include "ping.h"
#include <stdexcept>
#include <QtCore/QProcess>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include "network/netenums.h"

namespace Networking
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

  Pinger::~Pinger() { ch->terminate(); }

  void Pinger::start(uint32_t interval, const QString& address, const vector<QString>& args)
  {
    if(address.split('.').size() != 4)
      throw std::invalid_argument("Invalid address is provided to ping");

    addr = address;

    for(const auto& arg : args)
      m_args += QString(arg);

    if(interval == 0)
      ping();
    else
      t->start(interval);
  }

  void Pinger::stop() noexcept { t->stop(); }
  void Pinger::ping()
  {
    #ifdef Q_OS_WIN
    ch->start("ping", QStringList("-t") << QString(addr) );
    #else
    ch->start("ping", QStringList() << QString(addr) );
    #endif
    qDebug().noquote() << "[PING] Starting ping at" << addr;
  }

  void Pinger::recv()
  {
    auto data = ch->readAll();
    bool success = false;
    #ifdef Q_OS_WIN
    success = data.contains("TTL=");
    #else
    success = data.contains("time=");
    #endif

    emit result(success ? (int)Enums::PingStatus::Success : (int)Enums::PingStatus::Timeout);
  }

} // Network