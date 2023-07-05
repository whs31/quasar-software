/**
  * \class QuasarSDK::StripSocket quasarsdk_stripsocket.h <QuasarSDK/FSend/UDP>
  * \brief Класс для приема больших файлов с РЛС по протоколу UDP.
  * \details Используется для приема потока полосового изображения с РЛС.
  * \extends SeamlessUDPSocket
  */


#include "quasarsdk_stripsocket.h"

namespace QuasarSDK
{

  /// \brief Создает новый объект StripSocket с указанным родителем.
  StripSocket::StripSocket(QObject* parent)
      : SeamlessUDPSocket(parent)
  {
    connect(this, &SeamlessUDPSocket::received, this, &StripSocket::processChunk);
  }

  void StripSocket::processChunk(const QByteArray data) noexcept
  {
    emit metrics("DATA with size of " + QString::number(data.size()), data.size(), false);
    emit receivedChunk(data);
  }
} // QuasarSDK