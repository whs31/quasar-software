#pragma once

#include "terminalbase.h"
#include <functional>
#include <map>

namespace GUI
{
    class DebugConsole : public TerminalBase
    {
        Q_OBJECT

        public:
            static DebugConsole* get();

            Q_INVOKABLE void execute(const QString& command);

        private:
            DebugConsole(QObject* parent = nullptr);
            DebugConsole(const DebugConsole&);
            DebugConsole& operator=(const DebugConsole&);

            std::map<QString, std::function<void()>> command_list = {
                { "help", [this](){ help(); } },
                { "quit", [this](){ quit(); } },
                { "sim", [this](){ sim(); } },
                { "connect", [this](){ connect(); } },
                { "disconnect", [this](){ disconnect(); } },
                { "clear", [this](){ clear(); } }
            };

            void help();
            void quit();
            void sim();
            void connect();
            void disconnect();
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
