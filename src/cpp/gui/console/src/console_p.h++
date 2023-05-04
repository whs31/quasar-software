#pragma once

#include <definitions.h>
#include "../console.h++"
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

        __qml void sendCommand(QString command);

        signals:
            __signal appendSignal(const QString& text);

    private:
        void __concommand quit();
        void __concommand telsock_start();
        void __concommand telsock_stop();
        void __concommand execdsock_start();
        void __concommand execdsock_stop();
        void __concommand tcp_start();
        void __concommand tcp_stop();
        void __concommand sim();
        void __concommand nets();

    private:
        Console* q_ptr;
};
