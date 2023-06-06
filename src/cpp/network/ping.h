#pragma once

#include <vector>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include "netenums.h"

class QTimer;
class QProcess;

using std::vector;

namespace Network
{
    class Pinger : public QObject
    {
        Q_OBJECT

        public:
            explicit Pinger(QObject* parent = nullptr);

            void start(uint32_t interval, const QString& address, const vector<QString> args = {});
            void stop() noexcept;

            signals:
                void result(int status);

        private:
            private slots:
                void ping();
                void recv();

        private:
            QProcess* ch;
            QTimer* t;
            QString addr;
            QStringList m_args;
    };
} // Network
