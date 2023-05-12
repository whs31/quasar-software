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
void Marker::setPosition(const QGeoCoordinate &other) { m_position = other; }

QString Marker::name() const { return m_name; }
void Marker::setName(const QString &other) { m_name = other; }

QString Marker::icon() const { return m_icon; }
void Marker::setIcon(const QString &other) { m_icon = other; }

QString Marker::color() const { return m_color; }
void Marker::setColor(const QString &other) { m_color = other; }

QPointF Marker::anchor() const { return m_anchor; }
void Marker::setAnchor(QPointF other) { m_anchor = other; }
