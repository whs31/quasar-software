#pragma once

#include "../abstractudpsocket.h"

namespace Networking
{
    class FeedbackSocket : public AbstractUDPSocket
    {
        Q_OBJECT

        constexpr static const char* STORAGE_STATUS_MARKER = "*FREE_DISK_SPACE*";

        public:
            explicit FeedbackSocket(QObject* parent = nullptr);

            void start(const QString& address);
            void stop();

            signals:
                void textReceived(QByteArray text);
                void diskSpaceReceived(long free, long total);

        private:
            private slots:
                void processResult(QByteArray data);
    };
} // namespace Network;
