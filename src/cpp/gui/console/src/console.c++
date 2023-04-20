#include "console_p.h++"
#include <QtQml/qqml.h>
#include <QtCore/QCoreApplication>
#include "network/network.h++"

Console::Console(QObject* parent)
    : QObject{parent}
    , d_ptr(new ConsolePrivate(this))
{
}

void Console::append(const QString& message)
{
    Q_D(Console);
    emit (d->appendSignal(message));
}

void Console::sendCommand(const QString& command)
{
    Q_D(Console);
    d->sendCommand(command);
}

ConsolePrivate::ConsolePrivate(Console* parent)
    : QObject{parent}
    , q_ptr(parent)
{
    qmlRegisterSingletonInstance("ConsoleWidget", 1, 0, "Impl", this);
}

void ConsolePrivate::sendCommand(QString command)
{
    if(command_list.contains(command))
        command_list[command]();
    else
        qWarning() << "[CONSOLE] Unrecognized console command (" << command << ")";
}

void ConsolePrivate::quit()
{
    qInfo() << "[CONSOLE] Shutting down...";
    QCoreApplication::quit();
}

void ConsolePrivate::force_telemetry_socket_start()
{
    qDebug() << "[CONSOLE] Forcing start of telemetry socket at default frequency";
    Network::Network::get()->startTelemetrySocket(0.2);
}

void ConsolePrivate::force_telemetry_socket_stop()
{
    qWarning() << "[CONSOLE] Forcing stop of telemetry socket";
    Network::Network::get()->stopTelemetrySocket();
}
