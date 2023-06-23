#include "diagram.h"

namespace Map
{

  Diagram::Diagram(QObject* parent)
    : QObject{parent}
  {}

  QVariantList Diagram::polygon() const { return m_polygon; }
  void Diagram::setPolygon(const QVariantList& o) {
    if (m_polygon == o)
      return;
    m_polygon = o;
    emit polygonChanged();

    // call to this->update() here was removed. needs testing.
  }

  float Diagram::range() const { return m_range; }
  void Diagram::setRange(float other) {
    if (qFuzzyCompare(m_range, other))
      return;
    m_range = other;
    emit rangeChanged();
  }

  float Diagram::length() const { return m_length; }
  void Diagram::setLength(float other) {
    if (qFuzzyCompare(m_length, other))
      return;
    m_length = other;
    emit lengthChanged();

    this->update();
  }

  float Diagram::angle() const { return m_angle; }
  void Diagram::setAngle(float other) {
    if (qFuzzyCompare(m_angle, other))
      return;
    m_angle = other;
    emit angleChanged();

    this->update();
  }

  Diagram::DiagramType Diagram::type() const { return m_type; }
  void Diagram::setType(DiagramType other) {
    if (m_type == other)
      return;
    m_type = other;
    emit typeChanged();

    this->update();
  }

  QGeoCoordinate Diagram::uavPosition() const { return m_uavPosition; }
  void Diagram::setUavPosition(const QGeoCoordinate& other) {
    if (m_uavPosition == other)
      return;
    m_uavPosition = other;
    emit uavPositionChanged();

    this->update();
  }

  void Diagram::update()
  {
    if(not uavPosition().isValid())
      return;

    if(type() != DiagramType::Telescopic)
      return;

    float az_angle = azimuth() + ((direction() == Left) ? -90 : 90);

    QVariantList res = {
      QVariant::fromValue(uavPosition()),
      QVariant::fromValue(uavPosition().atDistanceAndAzimuth(range(), az_angle - angle() / 2)),
      QVariant::fromValue(uavPosition().atDistanceAndAzimuth(range(), az_angle - angle() / 4)),
      QVariant::fromValue(uavPosition().atDistanceAndAzimuth(range(), az_angle)),
      QVariant::fromValue(uavPosition().atDistanceAndAzimuth(range(), az_angle + angle() / 4)),
      QVariant::fromValue(uavPosition().atDistanceAndAzimuth(range(), az_angle + angle() / 2))
    };

    setPolygon(res);
  }

  double Diagram::azimuth() const { return m_azimuth; }
  void Diagram::setAzimuth(double other) {
    if (qFuzzyCompare(m_azimuth, other))
      return;
    m_azimuth = other;
    emit azimuthChanged();

    this->update();
  }

  Diagram::DiagramDirection Diagram::direction() const { return m_direction; }
  void Diagram::setDirection(const DiagramDirection& other) {
    if (m_direction == other)
      return;
    m_direction = other;
    emit directionChanged();

    this->update();
  }

} // Map
