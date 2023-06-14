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

#ifdef PROJECT_NAME
    #define CONSOLE_INTERNAL_PROJECT_STRING PROJECT_NAME
#else
    #define CONSOLE_INTERNAL_PROJECT_STRING QString()
#endif

#define CONSOLE_HANDLER consoleHandler

#define CONSOLE_INIT_HANDLER void consoleHandler(QtMsgType type, const QMessageLogContext &, const QString &msg) {  \
                                if(QCoreApplication::closingDown())                                                 \
                                    return;                                                                         \
                                GUI::DebugConsole::MessageType t;                                                   \
                                bool chop = false;                                                                  \
                                switch (type) {                                                                     \
                                    case QtDebugMsg:                                                                \
                                        if(msg.startsWith("$ ")) {                                                  \
                                            chop = true;                                                            \
                                            t = GUI::TerminalBase::Extra1;                                          \
                                        }                                                                           \
                                        else                                                                        \
                                            t = GUI::TerminalBase::Debug;                                           \
                                        break;                                                                      \
                                    case QtWarningMsg: t = GUI::TerminalBase::Warning; break;                       \
                                    case QtInfoMsg:                                                                 \
                                        if(msg.startsWith("$ ")) {                                                  \
                                            chop = true;                                                            \
                                            t = GUI::TerminalBase::Extra2;                                          \
                                        }                                                                           \
                                        else                                                                        \
                                            t = GUI::TerminalBase::Info;                                            \
                                        break;                                                                      \
                                    case QtCriticalMsg:                                                             \
                                    case QtFatalMsg: t = GUI::TerminalBase::Error; break;                           \
                                }                                                                                   \
                                QString res = msg;                                                                  \
                                if(chop)                                                                            \
                                    res.remove(0, 2);                                                               \
                                GUI::DebugConsole::get()->append(res, "[]", t);                                     \
                            };
