#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

namespace Map
{
    class ClickHandler : public QObject
    {
        public:
            enum MouseState {
                Idle,
                RulerActive,
                MarkerActive
            };
            Q_ENUM(MouseState);

        private:
            Q_OBJECT
            Q_PROPERTY(MouseState state READ state WRITE setState NOTIFY stateChanged)

            static ClickHandler* instance;
            MouseState m_state = RulerActive;

        public:
            static ClickHandler* get(QObject* parent = nullptr);

            MouseState state() const;
            void setState(const MouseState &newState);

            signals:
                __signal stateChanged();

        private:
            explicit ClickHandler(QObject* parent = nullptr);
    };
} // namespace Map;
