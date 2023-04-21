#pragma once

#include <definitions.h++>
#include "../console.h++"
#include <QtCore/QMap>
#include <functional>


namespace Debug {
    class TelemetrySocketEmulator;
}

class ConsolePrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Console)
    Console* q_ptr;
    Debug::TelemetrySocketEmulator* m_telemetry_socket_emulator;

    QMap<QString, std::function<void()>> command_list = {
        { "quit", [this](){ quit(); } },
        { "telsock_start", [this](){ telsock_start(); } },
        { "telsock_stop", [this](){ telsock_stop(); } },
        { "telsrv_start", [this](){ telsrv_start(); } },
        { "telsrv_stop", [this](){ telsrv_stop(); } }
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
        void __concommand telsrv_start();
        void __concommand telsrv_stop();
};
