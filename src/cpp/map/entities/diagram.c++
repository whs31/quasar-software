#include "diagram.h"

namespace Map
{
Diagram::Diagram(QObject* parent)
    : QObject{parent} {}

QVariantList Diagram::polygon() const { return m_polygon; }
void Diagram::setPolygon(const QVariantList& o) {
    if (m_polygon == o)
        return;
    m_polygon = o;
    emit polygonChanged();
}

float Diagram::range() const
{
    return m_range;
}

void Diagram::setRange(float other)
{
    if (qFuzzyCompare(m_range, other))
        return;
    m_range = other;
    emit rangeChanged();
}

float Diagram::length() const
{
    return m_length;
}

void Diagram::setLength(float other)
{
    if (qFuzzyCompare(m_length, other))
        return;
    m_length = other;
    emit lengthChanged();
}

float Diagram::angle() const
{
    return m_angle;
}

void Diagram::setAngle(float other)
{
    if (qFuzzyCompare(m_angle, other))
        return;
    m_angle = other;
    emit angleChanged();
}

Diagram::DiagramType Diagram::type() const
{
    return m_type;
}

void Diagram::setType(DiagramType other)
{
    if (m_type == other)
        return;
    m_type = other;
    emit typeChanged();
}

QGeoCoordinate Diagram::uavPosition() const
{
    return m_uavPosition;
}

void Diagram::setUavPosition(const QGeoCoordinate& other)
{
    if (m_uavPosition == other)
        return;
    m_uavPosition = other;
    emit uavPositionChanged();
}

} // Map
