#pragma once

#include <definitions.h++>
#include "../console.h++"
#include <QtCore/QMap>
#include <functional>


class ConsolePrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Console)
    Console* q_ptr;

    QMap<QString, std::function<void()>> command_list = {
        { "quit", [this](){ quit(); } },
        { "force_telemetry_socket_start", [this](){ force_telemetry_socket_start(); } },
        { "force_telemetry_socket_stop", [this](){ force_telemetry_socket_stop(); } }
    };

    public:
        ConsolePrivate(Console* parent);
        virtual ~ConsolePrivate() = default;

        __qml void sendCommand(QString command);

        signals:
            __signal appendSignal(const QString& text);

    private:
        void quit();
        void force_telemetry_socket_start();
        void force_telemetry_socket_stop();
};
