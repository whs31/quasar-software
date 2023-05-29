#include "telescopicdiagram.h"

using namespace Map;

TelescopicDiagram::TelescopicDiagram(QObject* parent)
    : Diagram(parent) {}

float TelescopicDiagram::angle() const { return m_angle; }
void TelescopicDiagram::setAngle(float o) {
    if (qFuzzyCompare(m_angle, o))
        return;
    m_angle = o;
    emit angleChanged();
}

float TelescopicDiagram::range() const { return m_range; }
void TelescopicDiagram::setRange(float o) {
    if (qFuzzyCompare(m_range, o))
        return;
    m_range = o;
    emit rangeChanged();
}
