#include "debugconsole.h"
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QuasarSDK/API>
#include "config/config.h"

using QuasarSDK::QuasarAPI;

namespace GUI
{

  DebugConsole* DebugConsole::get() { static DebugConsole instance; return &instance; }

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
    qInfo() << "$ \t <i>connect</i> - starts all sockets";
    qInfo() << "$ \t <i>disconnect</i> - stops all sockets";
    qInfo() << "$ \t <i>clear</i> - clears console log";
  }

  void DebugConsole::quit()
  {
    qInfo() << "$ [CONSOLE] Shutting down...";
    QCoreApplication::quit();
  }

  void DebugConsole::sim()
  {
    qWarning() << "[CONSOLE] Emulator support was removed in version 2.11.1";
    qWarning() << "[CONSOLE] Consider using quasar-firmware instance";
  }

  void DebugConsole::connect()
  {
    qInfo() << "$ [CONSOLE] Trying to connect through console...";
    QuasarAPI::get()->start(QuasarAPI::stringify(CONFIG(remoteIP), CONFIG(telemetryPort)),
                            QuasarAPI::stringify(CONFIG(remoteIP), CONFIG(telemetryRecvPort)),
                            CONFIG(telemetryFrequency),
                            QuasarAPI::stringify(CONFIG(remoteIP), CONFIG(execdPort)),
                            QuasarAPI::stringify(CONFIG(localIP), CONFIG(feedbackPort)),
                            QuasarAPI::stringify(CONFIG(localIP), CONFIG(tcpLFSPort)),
                            QuasarAPI::stringify(CONFIG(localIP), CONFIG(udpLFSPort)));
  }

  void DebugConsole::disconnect()
  {
    qInfo() << "$ [CONSOLE] Disconnecting through console...";
    QuasarAPI::get()->stop();
  }

} // GUI
