#pragma once

#include "terminalbase.h"
#include <functional>
#include <map>
#include <LPVL/Global>

namespace GUI
{
    class DebugConsole : public TerminalBase
    {
        Q_OBJECT
        LPVL_DECLARE_SINGLETON(DebugConsole)

        std::map<QString, std::function<void()>> command_list = {
            { "help", [this](){ help(); } },
            { "quit", [this](){ quit(); } },
            { "telsock_start", [this](){ telsock_start(); } },
            { "telsock_stop", [this](){ telsock_stop(); } },
            { "execdsock_start", [this](){ execdsock_start(); } },
            { "execdsock_stop", [this](){ execdsock_stop(); } },
            { "tcp_start", [this](){ tcp_start(); } },
            { "tcp_stop", [this](){ tcp_stop(); } },
            { "sim", [this](){ sim(); } },
            { "connect", [this](){ connect(); } },
            { "clear", [this](){ clear(); } }
        };

        public:
            Q_INVOKABLE void execute(const QString& command);

        private:
            DebugConsole(QObject* parent = nullptr);
            void help();
            void quit();
            void telsock_start();
            void telsock_stop();
            void execdsock_start();
            void execdsock_stop();
            void tcp_start();
            void tcp_stop();
            void sim();
            void connect();
    };
} // GUI


