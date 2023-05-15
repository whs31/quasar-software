#pragma once

#include <QtCore/QObject>
#include <ccl/ccl_global.h>

namespace Map
{
    class MarkerModel;

    class ClickHandler : public QObject
    {
        public: enum MouseState {
            Idle,
            RulerActive,
            ProtractorActive,
            MarkerActive,
            PlannerActive
        };

        Q_OBJECT
        Q_ENUM(MouseState);
        Q_PROPERTY(MouseState state READ state WRITE setState NOTIFY stateChanged)
        DEFINE_AS_SINGLETON(ClickHandler)

        public:
            MouseState state() const; void setState(const MouseState&);

            Q_INVOKABLE void copyCoordinatesToClipboard(double latitude, double longitude);
            Q_INVOKABLE MarkerModel* markerModel();

            signals:
                void stateChanged();

        private:
            explicit ClickHandler(QObject* parent = nullptr);

        private:
            MouseState m_state = Idle;
            MarkerModel* marker_model;
    };
} // namespace Map;
