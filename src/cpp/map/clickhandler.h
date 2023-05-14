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
        DEFINE_AS_SINGLETON(ClickHandler)

        Q_ENUM(MouseState);
        PROPERTY_DEF(MouseState, state, setState, m_state)

        public:
            signals:
                void stateChanged();

        private:
            explicit ClickHandler(QObject* parent = nullptr);

        private:
            MouseState m_state = Idle;
    };
} // namespace Map;
