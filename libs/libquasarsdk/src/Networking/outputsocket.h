/**
 *  \file COutputSocket.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include "baseudpsocket.h"

namespace QuasarSDK
{
  class OutputSocket : public BaseUDPSocket
  {
    Q_OBJECT

    public:
      explicit OutputSocket(QObject* parent = nullptr);

    signals:
      /**
       * \brief Срабатывает при получении информации о свободном месте на диске в РЛС.
       * \param free - количество свободных байт.
       * \param total - общее количество байт.
       */
      void diskSpaceReceived(long free, long total);

    private:
      Q_SLOT void process(QByteArray data) noexcept;
  };
} // QuasarSDK
