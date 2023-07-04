/**
 *  \file quasarsdk_telemetry.h
 *  \author Дмитрий Рязанцев
 *  \date 04.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include "QuasarSDK/Telemetry/TelemetryDatagram"

namespace QuasarSDK
{
  class Telemetry : public QObject
  {
    Q_OBJECT
  };
} // QuasarSDK
