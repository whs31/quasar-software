#include "marker.h++"

using namespace Map;

Marker::Marker()
    : m_position({0, 0})
    , m_name("Unnamed marker")
    , m_icon(QString())
    , m_anchor(QPointF(0, 0))
{

}

Marker::Marker(const QGeoCoordinate &coordinates, const QString &name, const QString &icon, QPointF anchors)
    : m_position(coordinates)
    , m_name(name)
    , m_icon(icon)
    , m_anchor(anchors)
{

}

Marker::Marker(double latitude, double longitude, const QString &name, const QString &icon, QPointF anchors)
    : m_position({latitude, longitude})
    , m_name(name)
    , m_icon(icon)
    , m_anchor(anchors)
{

}


QGeoCoordinate Marker::position() const { return m_position; }
void Marker::setPosition(const QGeoCoordinate &other) {
    if (m_position == other)
        return;
    m_position = other;
    emit positionChanged();
}

QString Marker::name() const { return m_name; }
void Marker::setName(const QString &other) {
    if (m_name == other)
        return;
    m_name = other;
    emit nameChanged();
}

QString Marker::icon() const { return m_icon; }
void Marker::setIcon(const QString &other) {
    if (m_icon == other)
        return;
    m_icon = other;
    emit iconChanged();
}

QString Marker::color() const { return m_color; }

void Marker::setColor(const QString &other) {
    if (m_color == other)
        return;
    m_color = other;
    emit colorChanged();
}

QPointF Marker::anchor() const { return m_anchor; }
void Marker::setAnchor(QPointF other) {
    if (m_anchor == other)
        return;
    m_anchor = other;
    emit anchorChanged();
}
