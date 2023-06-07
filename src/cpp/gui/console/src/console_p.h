#pragma once

#include "../console.h"
#include <QtCore/QMap>
#include <functional>

namespace Debug {
    class TelemetrySocketEmulator;
    class FeedbackEmulator;
}

class ConsolePrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Console)

    QMap<QString, std::function<void()>> command_list = {
        { "help", [this](){ help(); } },
        { "quit", [this](){ quit(); } },
        { "telsock_start", [this](){ telsock_start(); } },
        { "telsock_stop", [this](){ telsock_stop(); } },
        { "execdsock_start", [this](){ execdsock_start(); } },
        { "execdsock_stop", [this](){ execdsock_stop(); } },
        { "tcp_start", [this](){ tcp_start(); } },
        { "tcp_stop", [this](){ tcp_stop(); } },
        { "sim", [this](){ sim(); } },
        { "nets", [this](){ nets(); } }
    };

    public:
        ConsolePrivate(Console* parent);
        virtual ~ConsolePrivate() = default;

        Q_INVOKABLE void sendCommand(QString command);

        signals:
            void appendSignal(const QString& text);

    private:
        void help();
        void quit();
        void telsock_start();
        void telsock_stop();
        void execdsock_start();
        void execdsock_stop();
        void tcp_start();
        void tcp_stop();
        void sim();
        void nets();

    private:
        Console* q_ptr;
};
