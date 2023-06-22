#pragma once

#include "network/abstractudpsocket.h"
#include "network/netenums.h"

namespace Networking
{
    class ExecdArgumentList;
    class ExecdSocket : public AbstractUDPSocket
    {
        Q_OBJECT
        constexpr static const char* COMMAND_TELESCOPIC = "$telescopic";
        constexpr static const char* COMMAND_START_STRIP = "$strip_start";
        constexpr static const char* COMMAND_STOP_STRIP = "$strip_stop";
        constexpr static const char* COMMAND_FOCUS = "$focus";
        constexpr static const char* COMMAND_STORAGE_STATUS = "$storage_status()";
        constexpr static const char* COMMAND_CLEAR_STORAGE = "$clear_storage()";

        public:
            explicit ExecdSocket(QObject* parent = nullptr);

            void start(const QString& address);
            void stop();
            void executeCommand(const QString& command);
            void executeCommand(Enums::NetworkCommand command);
            ExecdArgumentList* list() const noexcept;

            signals:
                void ping();

        private:
            QString wrap(const QString& string);
            QByteArray finalize(const QString& string);

            private slots:
                void processResult(QByteArray data);

        private:
            ExecdArgumentList* args;
            uint16_t message_uid;
    };
}
