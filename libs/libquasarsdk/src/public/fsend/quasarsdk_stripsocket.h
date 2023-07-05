/**
 *  \file quasarsdk_stripsocket.h
 *  \author Дмитрий Рязанцев
 *  \date 05.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "private/quasarsdk_lfsudpsocket.h"

namespace QuasarSDK
{
  class StripSocket : public SeamlessUDPSocket
  {
    Q_OBJECT

    public:
      explicit StripSocket(QObject* parent = nullptr);

    signals:
      /// \brief Срабатывает при получении чанка полосового РЛИ.
      void receivedChunk(QByteArray chunk);

    private:
      Q_SLOT void processChunk(const QByteArray data) noexcept;
  };
} // QuasarSDK
