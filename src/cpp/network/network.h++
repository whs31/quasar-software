#pragma once

#include <QtCore/QObject>

namespace Network
{
    class Telemetry;
    class TelemetrySocket;
    class Network : public QObject
    {
        Q_OBJECT

        static Network* instance;

        Telemetry* m_telemetry;

        public:
            static Network* get(QObject* parent = nullptr);

            TelemetrySocket* telemetrySocket;

            signals:

        private:
            explicit Network(QObject *parent = nullptr);
    };
} // namespace Network;
