#pragma once

#include <definitions.h++>
#include "network/abstractudpsocket.h++"

namespace Network
{
    class ExecdSocket : public AbstractUDPSocket
    {
        Q_OBJECT

        public:
            explicit ExecdSocket(QObject* parent = nullptr);

            void start(const QString& address);
            void stop();
    };
}
