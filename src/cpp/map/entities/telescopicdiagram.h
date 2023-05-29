#pragma once

#include "diagram.h"

namespace Map
{
    class TelescopicDiagram : public Diagram
    {
        Q_OBJECT
        Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
        Q_PROPERTY(float range READ range WRITE setRange NOTIFY rangeChanged)

        public:
            TelescopicDiagram(QObject* parent = nullptr);
            float angle() const; void setAngle(float);
            float range() const; void setRange(float);

            signals:
                void angleChanged();
                void rangeChanged();

        private:
            float m_angle;
            float m_range;
    };
} // Map
