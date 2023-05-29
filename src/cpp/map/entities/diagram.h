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
            Q_ENUM(DiagramType);

        private:
            Q_OBJECT
            Q_PROPERTY(QVariantList polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
            Q_PROPERTY(float range READ range WRITE setRange NOTIFY rangeChanged)
            Q_PROPERTY(float length READ length WRITE setLength NOTIFY lengthChanged)
            Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
            Q_PROPERTY(DiagramType type READ type WRITE setType NOTIFY typeChanged)
            Q_PROPERTY(QGeoCoordinate uavPosition READ uavPosition WRITE setUavPosition NOTIFY uavPositionChanged)

        public:
            Diagram(QObject* parent = nullptr);

            QVariantList polygon() const; void setPolygon(const QVariantList&);
            float range() const; void setRange(float);
            float length() const; void setLength(float);
            float angle() const; void setAngle(float);
            DiagramType type() const; void setType(DiagramType);
            QGeoCoordinate uavPosition() const; void setUavPosition(const QGeoCoordinate&);

            signals:
                void polygonChanged();
                void rangeChanged();
                void lengthChanged();
                void angleChanged();
                void typeChanged();
                void uavPositionChanged();

        private:
            QVariantList m_polygon;
            float m_range;
            float m_length;
            float m_angle;
            DiagramType m_type;
            QGeoCoordinate m_uavPosition;
    };
} // Map
