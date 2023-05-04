#pragma once

#include <definitions.h++>
#include <QtCore/QString>
#include <QtCore/QPointF>
#include <QtPositioning/QGeoCoordinate>

namespace Map
{
    class Marker
    {
        Q_GADGET
        Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition)
        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(QString icon READ icon WRITE setIcon)
        Q_PROPERTY(QString color READ color WRITE setColor)
        Q_PROPERTY(QPointF anchor READ anchor WRITE setAnchor)

        public:
            Marker();
            Marker(const QGeoCoordinate& coordinates, const QString& name, const QString& icon, QPointF anchors);
            Marker(double latitude, double longitude, const QString& name, const QString& icon, QPointF anchors);

            QGeoCoordinate position() const;
            void setPosition(const QGeoCoordinate& other);

            QString name() const;
            void setName(const QString& other);

            QString icon() const;
            void setIcon(const QString& other);

            QString color() const;
            void setColor(const QString& other);

            QPointF anchor() const;
            void setAnchor(QPointF other);

        private:
            QGeoCoordinate m_position;
            QString m_name;
            QString m_icon;
            QString m_color;
            QPointF m_anchor;
    };
} // namespace Map;

