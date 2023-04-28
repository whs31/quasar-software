#pragma once
#define __global static inline
#define __qml Q_INVOKABLE
#define __signal void

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

            __qml void setAddress(const QString& address);
            __qml void testVT100();

        private:
            void send(QByteArray data);
    };
} // namespace Debug;
