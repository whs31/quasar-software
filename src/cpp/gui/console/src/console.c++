#include "console_p.h"
#include "network/network.h"
#include "config/config.h"
#include "config/paths.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QProcess>
#include <QtQml/qqml.h>

Console::Console(QObject* parent)
    : QObject{parent}
    , d_ptr(new ConsolePrivate(this))
{
}

void Console::append(const QString& message)
{
    if(QCoreApplication::closingDown())
        return;

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
    qInfo() << "$ Console initialized";
}

void ConsolePrivate::sendCommand(QString command)
{
    if(command_list.contains(command))
        command_list[command]();
    else
        qWarning().nospace().noquote() << "[CONSOLE] Unrecognized console command [" << command << "]";
}

void ConsolePrivate::quit()
{
    qInfo() << "[CONSOLE] Shutting down...";
    QCoreApplication::quit();
}

void ConsolePrivate::telsock_start()
{
    qDebug() << "[CONSOLE] Forcing start of telemetry socket at default frequency";
    Network::Network::get()->startTelemetrySocket(CONFIG(remoteIP) + ":" + CONFIG(telemetryPort),
                                                  CONFIG(telemetryFrequency));
}

void ConsolePrivate::telsock_stop()
{
    qWarning() << "[CONSOLE] Forcing stop of telemetry socket";
    Network::Network::get()->stopTelemetrySocket();
}

void ConsolePrivate::execdsock_start()
{
    Network::Network::get()->startExecdSocket(CONFIG(remoteIP) + ":" + CONFIG(execdPort),
                                              CONFIG(localIP) + ":" + CONFIG(feedbackPort));
}

void ConsolePrivate::execdsock_stop()
{
    Network::Network::get()->stopExecdSocket();
}

void ConsolePrivate::tcp_start()
{
    Network::Network::get()->startTCPSocket(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort));
}

void ConsolePrivate::tcp_stop()
{
    Network::Network::get()->stopTCPSocket();
}

void ConsolePrivate::sim()
{
    #ifdef Q_OS_WIN
        QProcess::startDetached(Config::Paths::root() + "/bin/QuaSAR-Emulator.exe", {});
        qDebug().noquote().nospace() << "[CONSOLE] Launching simulator from";
        qDebug().noquote().nospace() << Config::Paths::root() << "/bin/QuaSAR-Emulator.exe";
    #else
        qWarning() << "[CONSOLE] Your operating system is Linux. Emulator support for Linux was removed in version 2.10.1";
#endif
}

void ConsolePrivate::nets()
{
    execdsock_start();
    telsock_start();
    tcp_start();
}
