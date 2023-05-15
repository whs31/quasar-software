#pragma once

#include <QtCore/QObject>
#include <ccl/ccl_global.h>

namespace Map
{
    class ClickHandler : public QObject
    {
        public: enum MouseState {
            Idle,
            RulerActive,
            ProtractorActive,
            MarkerActive
        };

        Q_OBJECT
        Q_ENUM(MouseState);
        Q_PROPERTY(MouseState state READ state WRITE setState NOTIFY stateChanged)
        DEFINE_AS_SINGLETON(ClickHandler)

        public:
            MouseState state() const; void setState(const MouseState&);

            signals:
                void stateChanged();

        private:
            explicit ClickHandler(QObject* parent = nullptr);

        private:
            MouseState m_state = Idle;
    };
} // namespace Map;
