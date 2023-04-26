#pragma once

#include <QtCore/QObject>

class QUdpSocket;

namespace Debug
{
    class FeedbackEmulator : public QObject
    {
        Q_OBJECT
        QUdpSocket* socket;
        bool started = false;
        QString ip;
        uint16_t port = 0;

        public:
            explicit FeedbackEmulator(QObject *parent = nullptr);

            void setAddress(const QString& address);
            void send(QByteArray data);
            void testVT100();
    };
} // namespace Debug;
