#pragma once

#include <QtCore/QObject>
#include <QtCore/QPointF>

namespace GUI
{
    class FocusBackend : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QPointF mouseCoords READ mouseCoords WRITE setMouseCoords NOTIFY mouseCoordsChanged)
        Q_PROPERTY(int imageIndex READ imageIndex WRITE setImageIndex NOTIFY imageIndexChanged)

        public:
            explicit FocusBackend(QObject *parent = nullptr);

            Q_INVOKABLE void setArguments() noexcept;

            [[nodiscard]] QPointF mouseCoords() const; void setMouseCoords(QPointF);
            [[nodiscard]] int imageIndex() const; void setImageIndex(int);

            signals:
                void mouseCoordsChanged();
                void imageIndexChanged();

        private:
            QPointF m_mouseCoords;
            int m_imageIndex;
    };
} // GUI
