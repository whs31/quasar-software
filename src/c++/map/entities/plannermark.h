//
// Created by whs31 on 27.07.23.
//

#pragma once
#include "geomarker.h"

namespace QuasarSDK::Datagrams {}
using namespace QuasarSDK::Datagrams;

namespace Map
{
  /**
   * \brief Геометка с заданной командой для планировщика.
   * \todo Дополнить документацию.
   */
  class PlannerMark : public GeoMarker
  {
    public:
      PlannerMark();
      PlannerMark(const QGeoCoordinate& coord, const QString& point_name, const QColor& point_color, int point_radius,
                  const QString& response_address, const QString& point_command, int lifetime = 1);

      [[nodiscard]] int id() const;
      void setID(int);

      [[nodiscard]] int radius() const;
      void setRadius(int);

      [[nodiscard]] QString address() const;
      [[nodiscard]] uint32_t iphex() const;
      [[nodiscard]] uint16_t port() const;
      void setAddress(const QString&);

      [[nodiscard]] int lifetime() const;
      void setLifetime(int);

      [[nodiscard]] QString command() const;
      void setCommand(const QString&);

      [[nodiscard]] QByteArray appendDatagram() const;
      [[nodiscard]] QByteArray removeDatagram() const;

    protected:
      int m_id;
      int m_radius;
      QString m_address;
      int m_lifetime_count;
      QString m_command;

      static int m_shared_counter;
  };
} // Map
