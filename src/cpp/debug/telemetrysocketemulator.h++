#pragma once

#include <definitions.h++>
#include <QtCore/QObject>

namespace Debug
{
    class TelemetrySocketEmulator : public QObject
    {
        Q_OBJECT

        public:
            TelemetrySocketEmulator(QObject* parent = nullptr);

            signals:

    };
} // namespace Debug;
