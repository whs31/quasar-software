#pragma once

#include "../abstractudpsocket.h++"

namespace Network
{
    class FeedbackSocket : public Network::AbstractUDPSocket
    {
        Q_OBJECT

        public:
            explicit FeedbackSocket(QObject* parent = nullptr);

            void start(const QString& address);
            void stop();

            signals:
                __signal textReceived(QString text);

        private:
            private slots:
                void processResult(QByteArray data);
    };
} // namespace Network;
