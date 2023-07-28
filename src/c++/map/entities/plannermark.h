//
// Created by whs31 on 27.07.23.
//

#pragma once
#include "geomarker.h"
#include <QuasarSDK/PlannerDatagrams>

namespace Map
{
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
      void setAddress(const QString&);

      [[nodiscard]] int lifetime() const;
      void setLifetime(int);

      [[nodiscard]] QString command() const;
      void setCommand(const QString&);

    protected:
      int m_id;
      int m_radius;
      QString m_address;
      int m_lifetime_count;
      QString m_command;

      static int m_shared_counter;
  };
} // Map
