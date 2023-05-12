#pragma once

#include <Definitions>
#include <QtCore/QObject>

namespace Map
{
    class ClickHandler : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(MouseState state READ state WRITE setState NOTIFY stateChanged)

        public:
            enum MouseState {
                Idle,
                RulerActive,
                ProtractorActive,
                MarkerActive
            };
            Q_ENUM(MouseState);

        public:
            static ClickHandler* get(QObject* parent = nullptr);

            __getter MouseState state() const;
            __setter void setState(const MouseState& other);

            signals:
                __signal stateChanged();

        private:
            explicit ClickHandler(QObject* parent = nullptr);

        private:
            static ClickHandler* instance;
            MouseState m_state = Idle;
    };
} // namespace Map;