#include "stripsocket.h"
#include <QtCore/QFile>
#include <QtCore/QDateTime>
#include "config/paths.h"
#include "filesystem/filesystem.h"

namespace Networking
{

  StripSocket::StripSocket(QObject* parent)
    : UDPSocketBase(parent)
    , m_currentindex(1)
    , m_stripstatus(false)
  {
    QObject::connect(this, &StripSocket::received, this, &StripSocket::processResult, Qt::DirectConnection);
  }

  void StripSocket::start(const QString& address)
  {
    this->connect(address);
    qInfo().noquote() << "[STRIPLFS] Started listening to SAR on" << address;
  }

  void StripSocket::stop()
  {
    this->disconnect();
    qInfo() << "[STRIPLFS] Socket disconnected";
  }

  void StripSocket::setStripStatus(bool status) noexcept
  {
    if(status == m_stripstatus)
      return;
    m_stripstatus = status;
    if(m_stripstatus == true)
    {
      m_storeddata.clear();
      emit socketMetrics("Waiting for data.", 0, true);
    }
    else
    {
      if(m_storeddata.size() > 1024)
        this->saveResult(Config::Paths::tcp() + "/striplfs_" + QString::number(QDateTime::currentSecsSinceEpoch())
                         + "_" + QString::number(m_currentindex), m_storeddata);
      emit socketMetrics("Finished receiving.", 0, true);
    }
  }

  void StripSocket::processResult(QByteArray data)
  {
    m_storeddata.push_back(data);
    emit socketMetrics("DATA with size of " + QString::number(data.size()), data.size(), false);
  }

  void StripSocket::saveResult(const QString& path, const QByteArray& data) noexcept
  {
    m_currentindex++;
    QFile file(path);
    if(not file.open(QIODevice::WriteOnly))
    {
      qCritical() << "[STRIPLFS] Failed to save result";
      return;
    }

    file.write(data);
    file.close();

    OS::Filesystem::get()->fetchTCPCache();
  }

} // Networking
