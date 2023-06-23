#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariantList>
#include <QtPositioning/QGeoCoordinate>

namespace Map
{
  class Diagram : public QObject
  {
    public:
      enum DiagramType
      {
        Telescopic,
        Strip
      };

      enum DiagramDirection
      {
        Left,
        Right
      };

      Q_ENUM(DiagramType);
      Q_ENUM(DiagramDirection);

    private:
    Q_OBJECT
      Q_PROPERTY(QVariantList polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
      Q_PROPERTY(float range READ range WRITE setRange NOTIFY rangeChanged)
      Q_PROPERTY(float length READ length WRITE setLength NOTIFY lengthChanged)
      Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
      Q_PROPERTY(DiagramType type READ type WRITE setType NOTIFY typeChanged)
      Q_PROPERTY(QGeoCoordinate uavPosition READ uavPosition WRITE setUavPosition NOTIFY uavPositionChanged)
      Q_PROPERTY(double azimuth READ azimuth WRITE setAzimuth NOTIFY azimuthChanged)
      Q_PROPERTY(DiagramDirection direction READ direction WRITE setDirection NOTIFY directionChanged)

    public:
      explicit Diagram(QObject* parent = nullptr);

      [[nodiscard]] QVariantList polygon() const; void setPolygon(const QVariantList&);
      [[nodiscard]] float range() const; void setRange(float);
      [[nodiscard]] float length() const; void setLength(float);
      [[nodiscard]] float angle() const; void setAngle(float);
      [[nodiscard]] DiagramType type() const; void setType(DiagramType);
      [[nodiscard]] QGeoCoordinate uavPosition() const; void setUavPosition(const QGeoCoordinate&);
      [[nodiscard]] double azimuth() const; void setAzimuth(double);
      [[nodiscard]] DiagramDirection direction() const; void setDirection(const DiagramDirection&);

    signals:
      void polygonChanged();
      void rangeChanged();
      void lengthChanged();
      void angleChanged();
      void typeChanged();
      void uavPositionChanged();
      void azimuthChanged();
      void directionChanged();

    private:
      void update();

    private:
      QVariantList m_polygon;
      float m_range;
      float m_length;
      float m_angle;
      DiagramType m_type;
      QGeoCoordinate m_uavPosition;
      double m_azimuth;
      DiagramDirection m_direction;
  };
} // Map
