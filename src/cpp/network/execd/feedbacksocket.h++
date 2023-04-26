#pragma once

#include <definitions.h++>
#include "../abstractudpsocket.h++"

namespace Network
{
    class FeedbackSocket : public AbstractUDPSocket
    {
        Q_OBJECT
        constexpr __global const char* STORAGE_STATUS_MARKER = "*FREE_DISK_SPACE*";

        public:
            explicit FeedbackSocket(QObject* parent = nullptr);

            void start(const QString& address);
            void stop();

            signals:
                __signal textReceived(QByteArray text);
                __signal diskSpaceReceived(long free, long total);

        private:
            private slots:
                void processResult(QByteArray data);
    };
} // namespace Network;
