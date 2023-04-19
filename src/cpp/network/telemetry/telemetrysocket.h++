#pragma once

#include "network/abstractudpsocket.h++"

namespace Network
{
    class TelemetrySocket : public AbstractUDPSocket
    {
        Q_OBJECT

        public:
            TelemetrySocket(QObject* parent = nullptr);
    };
} // namespace Network
