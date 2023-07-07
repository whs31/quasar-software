/**
  * \class QuasarSDK::SeamlessUDPSocket CSeamlessUDPSocket.h <QuasarSDK/Networking/CSeamlessUDPSocket.h>
  * \brief Базовый класс для UDP сокетов, требующих целостность датаграммы.
  * \details Класс наследует #BaseUDPSocket и отличается от него
  * только способом обработки входящей датаграммы.
  * Используйте этот класс тогда, когда требуется получать
  * датаграмму в том же виде и размере, в котором она была отправлена.
  * \extends BaseUDPSocket
  */

#include "CSeamlessUDPSocket.h"
#include <QtNetwork/QNetworkDatagram>

namespace QuasarSDK
{
  /// \brief Создает новый объект SeamlessUDPSocket с указанным родителем.
  SeamlessUDPSocket::SeamlessUDPSocket(QObject* parent)
      : BaseUDPSocket(parent)
  {
    connect(this, &QUdpSocket::readyRead, this, &SeamlessUDPSocket::readSocket, Qt::DirectConnection);
  }

  void SeamlessUDPSocket::readSocket() noexcept
  {
    while(hasPendingDatagrams())
    {
      QNetworkDatagram datagram = this->receiveDatagram();
      emit received(datagram.data());
    }
  }
} // QuasarSDK