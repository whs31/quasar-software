/**
 *  \file CSeamlessUDPSocket.h
 *  \author Дмитрий Рязанцев
 *  \date 04.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "baseudpsocket.h"

namespace QuasarSDK
{
  class SeamlessUDPSocket : public BaseUDPSocket
  {
    Q_OBJECT

    public:
      explicit SeamlessUDPSocket(QObject* parent = nullptr);

    protected:
      Q_SLOT void readSocket() noexcept override;
  };
} // QuasarSDK
