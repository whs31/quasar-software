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

} // Map
