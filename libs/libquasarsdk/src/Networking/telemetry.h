/**
 *  \file CTelemetry.h
 *  \author Дмитрий Рязанцев
 *  \date 04.07.2023
 *  \copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtPositioning/QGeoCoordinate>
#include "telemetry_datagrams.h"

namespace QuasarSDK
{
  class Telemetry : public QObject
  {
    Q_OBJECT

    Q_PROPERTY(QGeoCoordinate position READ position NOTIFY positionChanged)
    Q_PROPERTY(QVector2D velocity READ velocity NOTIFY velocityChanged)
    Q_PROPERTY(QVector3D eulerAxes READ eulerAxes NOTIFY eulerAxesChanged)
    Q_PROPERTY(int satellites READ satellites NOTIFY satellitesChanged)
    Q_PROPERTY(float seaLevel READ seaLevel WRITE setSeaLevel NOTIFY seaLevelChanged)

    public:
      explicit Telemetry(QObject* parent = nullptr);

      void setDatagram(const Datagrams::TelemetryDatagram& datagram) noexcept;

      [[nodiscard]] QGeoCoordinate position() const;
      [[nodiscard]] QVector2D velocity() const;
      [[nodiscard]] QVector3D eulerAxes() const;
      [[nodiscard]] int satellites() const;
      [[nodiscard]] float seaLevel() const; void setSeaLevel(float);

    signals:
      void positionChanged();
      void velocityChanged();
      void eulerAxesChanged();
      void satellitesChanged();
      void seaLevelChanged();

    private:
      Datagrams::TelemetryDatagram m_datagram;
      float m_seaLevel;
  };
} // QuasarSDK

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(QuasarSDK::Telemetry*)