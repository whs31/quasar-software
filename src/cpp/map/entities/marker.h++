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
        Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
        Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QPointF anchor READ anchor WRITE setAnchor NOTIFY anchorChanged)

        QGeoCoordinate m_position;
        QString m_name;
        QString m_icon;
        QString m_color;
        QPointF m_anchor;

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

            signals:
                __signal positionChanged();
                __signal nameChanged();
                __signal iconChanged();
                __signal colorChanged();
                __signal anchorChanged();
    };
} // namespace Map;

