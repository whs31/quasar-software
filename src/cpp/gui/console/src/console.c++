#include "console_p.h++"
#include "network/network.h++"
#include "debug/telemetrysocketemulator.h++"
#include <QtQml/qqml.h>
#include <QtCore/QCoreApplication>

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
    , m_telemetry_socket_emulator(new Debug::TelemetrySocketEmulator(this))
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

void ConsolePrivate::telsock_start()
{
    qDebug() << "[CONSOLE] Forcing start of telemetry socket at default frequency";
    Network::Network::get()->startTelemetrySocket(0.2);
}

void ConsolePrivate::telsock_stop()
{
    qWarning() << "[CONSOLE] Forcing stop of telemetry socket";
    Network::Network::get()->stopTelemetrySocket();
}

void ConsolePrivate::telsrv_start()
{
    if(not m_telemetry_socket_emulator)
        return;
    m_telemetry_socket_emulator->startTelemetryServer(); // add args
}

void ConsolePrivate::telsrv_stop()
{
    if(not m_telemetry_socket_emulator)
        return;
    m_telemetry_socket_emulator->stop();
}
