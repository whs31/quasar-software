/**
 * \ingroup sdk_network
 * \class QuasarSDK::StripSocket CStripSocket.h <QuasarSDK/Networking/CStripSocket.h>
 * \brief Класс для приема больших файлов с РЛС по протоколу UDP.
 * \details Используется для приема потока полосового изображения с РЛС.
 * \extends SeamlessUDPSocket
 */

#include "stripsocket.h"

namespace QuasarSDK
{

  /// \brief Создает новый объект StripSocket с указанным родителем.
  StripSocket::StripSocket(QObject* parent)
      : SeamlessUDPSocket(parent)
  {
    this->setName("Strip");
    connect(this, &SeamlessUDPSocket::received, this, &StripSocket::processChunk);
  }

  void StripSocket::processChunk(const QByteArray data) noexcept
  {
    emit metrics("DATA with size of " + QString::number(data.size()), data.size(), false);
    emit receivedChunk(data);
  }
} // QuasarSDK