#pragma once

#include <QtCore/QVariantList>
#include <QtPositioning/QGeoCoordinate>

namespace SDK::Cartography
{
  class Orthodrom
  {
    public:
      Orthodrom(const QGeoCoordinate& first, const QGeoCoordinate& second);
      Orthodrom();

      [[nodiscard]] auto get() const noexcept -> QList<QVariant>;
      void set(const QGeoCoordinate& first, const QGeoCoordinate& second) noexcept;

      [[nodiscard]] double latitudeAt(double longitude) const noexcept;

    private:
      void distribute() noexcept;
      [[nodiscard]] double distance() const noexcept;

    private:
      double a1, a2;
      QGeoCoordinate first, second;
      QList<QVariant> path;
  };
} // SDK::Cartography
