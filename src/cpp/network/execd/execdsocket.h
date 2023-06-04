#pragma once

#include "network/abstractudpsocket.h"

namespace Network
{
    class ExecdSocket : public AbstractUDPSocket
    {
        Q_OBJECT

        public:
            enum Command
            {
                FormImage,
                FocusImage,
                RemoteStorageStatus,
                ClearRemoteStorage,
                Ping
            };

            explicit ExecdSocket(QObject* parent = nullptr);

            void start(const QString& address);
            void stop();
            void executeCommand(const QString& command);
            void executeCommand(Command command);

            signals:
                void ping();

        private:
            QString wrap(const QString& string);
            QByteArray finalize(const QString& string);

            private slots:
                void processResult(QByteArray data);

        private:
            uint16_t message_uid = 0;
    };
}
