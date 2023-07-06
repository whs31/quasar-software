#include "stripsocket.h"
#include "config/paths.h"
#include "processing/streamprocessing.h"

namespace Networking
{

  StripSocket::StripSocket(QObject* parent)
    : UDPSocketBase(parent)
  {
    QObject::connect(this, &StripSocket::received, this, &StripSocket::processResult, Qt::DirectConnection);
  }

  void StripSocket::start(const QString& address)
  {
    this->connect(address);
    qInfo().noquote() << "[STRIP SOCK] Started listening to SAR on" << address;
  }

  void StripSocket::stop()
  {
    this->disconnect();
    qInfo() << "[STRIP SOCK] Socket disconnected";
  }

  void StripSocket::processResult(const QByteArray& data)
  {
    Processing::StreamProcessing::get()->append(data);
    emit socketMetrics("DATA with size of " + QString::number(data.size()), data.size(), false);
  }

} // Networking
