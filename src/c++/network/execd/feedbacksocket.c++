#include "feedbacksocket.h"
#include "config/networkconfig.h"

namespace Networking
{

  FeedbackSocket::FeedbackSocket(QObject* parent)
    : UDPSocketBase{parent}
  {
    QObject::connect(this, &FeedbackSocket::received, this, &FeedbackSocket::processResult, Qt::DirectConnection);
  }

  void FeedbackSocket::start(const QString& address)
  {
    this->connect(address);
    qInfo().noquote() << "[FEEDBACK] Started listening to SAR on" << address;
  }

  void FeedbackSocket::stop()
  {
    this->disconnect();
    qInfo() << "[FEEDBACK] Socket disconnected";
  }

  void FeedbackSocket::processResult(QByteArray data)
  {
    try
    {
      QString dataString = data;
      if(dataString.contains(NETCFG("STDOUT_STORAGE_STATUS")))
      {
        dataString.remove(NETCFG("STDOUT_STORAGE_STATUS"));
        dataString.remove(0, 1);

        qDebug().noquote() << "[SAR] Received storage status: " << dataString;

        emit diskSpaceReceived(dataString.split(' ', Qt::SkipEmptyParts).first().toLong(),
                               dataString.split(' ', Qt::SkipEmptyParts).last().toLong());
      }

      emit textReceived(data);
    }
    catch(...)
    {
      qCritical() << "[FEEDBACK] Exception at parsing result";
    }
  }

} // Networking