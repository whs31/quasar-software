#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariantList>

namespace Map
{
    class Diagram : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QVariantList polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)

        public:
            Diagram(QObject* parent = nullptr);

            QVariantList polygon() const; void setPolygon(const QVariantList&);

            signals:
                void polygonChanged();

        private:
            QVariantList m_polygon;
    };
} // Map
