/**
 *  \file quasarsdk_remotedata.h
 *  \author Дмитрий Рязанцев
 *  \date 06.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include "public/quasarsdk_enums.h"

namespace QuasarSDK
{
  class RemoteData : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(float storageSpace MEMBER storageSpace NOTIFY storageSpaceChanged)
    Q_PROPERTY(QList<Enums::PingStatus> pings MEMBER pings NOTIFY pingsChanged)

    public:
      explicit RemoteData(QObject* parent = nullptr);

      float storageSpace;
      QList<Enums::PingStatus> pings;

    signals:
      void storageSpaceChanged();
      void pingsChanged();
  };
} // QuasarSDK
