#pragma once

#include "definitions.h++"
#include "telemetry/telemetry.h++"
#include <QtCore/QObject>

namespace Network
{
    class TelemetrySocket;
    class Network : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)

        static Network* instance;

        Telemetry* m_telemetry;

        public:
            static Network* get(QObject* parent = nullptr);

            TelemetrySocket* telemetrySocket;

            Telemetry *telemetry() const;
            void setTelemetry(Telemetry* other);

            signals:
                __signal telemetryChanged();

        private:
            explicit Network(QObject *parent = nullptr);
    };
} // namespace Network;
