#include "stripsocket.h"
#include "config/paths.h"
#include "processing/imageprocessing.h"

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
    if(data.size() >= 1024)
        Processing::ImageProcessing::get()->processChunk(data);
    emit socketMetrics("DATA with size of " + QString::number(data.size()), data.size(), false);
  }

} // Networking
