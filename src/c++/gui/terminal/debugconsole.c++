#include "debugconsole.h"
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QProcess>
#include "network/network.h"
#include "config/config.h"

namespace GUI
{

void DebugConsole::execute(const QString& command)
{
    if(command_list.find(command) != command_list.end())
        command_list[command]();
    else
        qWarning().nospace().noquote() << "[CONSOLE] Unrecognized console command [" << command << "]";
}

DebugConsole::DebugConsole(QObject* parent)
    : TerminalBase(parent)
{
    qInfo() << "$ Console initialized";
}

void DebugConsole::help()
{
    qInfo() << "$ <i><u>" << CONSOLE_INTERNAL_PROJECT_STRING << "CONSOLE v0.9</u></i>";
    qInfo() << "$ \t <i>quit</i> - exits the application and cleanup used resources";
    qInfo() << "$ \t <i>telsock_start</i> - starts the telemetry socket at default frequency";
    qInfo() << "$ \t <i>telsock_stop</i> - stops the telemetry socket";
    qInfo() << "$ \t <i>execdsock_start</i> - starts the execd socket";
    qInfo() << "$ \t <i>execdsock_stop</i> - stops the execd socket";
    qInfo() << "$ \t <i>tcp_start</i> - stops the TCP-IP socket";
    qInfo() << "$ \t <i>tcp_stop</i> - stops the TCP-IP socket";
    qInfo() << "$ \t <i>connect</i> - starts all sockets, except UDP-LFS";
    qInfo() << "$ \t <i>clear</i> - clears console log";
}

void DebugConsole::quit()
{
    qInfo() << "$ [CONSOLE] Shutting down...";
    QCoreApplication::quit();
}

void DebugConsole::telsock_start()
{
    qInfo() << "$ [CONSOLE] Forcing start of telemetry socket at default frequency";
    Networking::Network::get()->startTelemetrySocket(CONFIG(remoteIP) + ":" + CONFIG(telemetryPort),
                                                  CONFIG(remoteIP) + ":" + CONFIG(telemetryRecvPort),
                                                  CONFIG(telemetryFrequency));
}

void DebugConsole::telsock_stop()
{
    qInfo() << "$ [CONSOLE] Forcing stop of telemetry socket";
    Networking::Network::get()->stopTelemetrySocket();
}

void DebugConsole::execdsock_start()
{
    qInfo() << "$ [CONSOLE] Forcing start of execd + feedback socket at default frequency";
    Networking::Network::get()->startExecdSocket(CONFIG(remoteIP) + ":" + CONFIG(execdPort),
                                              CONFIG(localIP) + ":" + CONFIG(feedbackPort));
}

void DebugConsole::execdsock_stop()
{
    qInfo() << "$ [CONSOLE] Forcing stop of execd and feedback socket";
    Networking::Network::get()->stopExecdSocket();
}

void DebugConsole::tcp_start()
{
    qInfo() << "$ [CONSOLE] Forcing start of tcp-ip socket at default frequency";
    Networking::Network::get()->startTCPSocket(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort));
}

void DebugConsole::tcp_stop()
{
    qInfo() << "$ [CONSOLE] Forcing stop of tcp-ip socket";
    Networking::Network::get()->stopTCPSocket();
}

void DebugConsole::sim()
{
    qWarning() << "[CONSOLE] Emulator support was removed in version 2.11.1";
    qWarning() << "[CONSOLE] Consider using quasar-firmware instance";
}

void DebugConsole::connect()
{
    qInfo() << "$ [CONSOLE] Trying to connect through console...";
    execdsock_start();
    telsock_start();
    tcp_start();
}

} // GUI
