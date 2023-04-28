#include "console_p.h++"
#include "network/network.h++"
#include "config/config.h++"
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
    Network::Network::get()->startTelemetrySocket(QString(CONFIG("remoteIP").toString() + ":" +
                                                          CONFIG("telemetryPort").toString()),
                                                          CONFIG("telemetryFrequency").toFloat());
}

void ConsolePrivate::telsock_stop()
{
    qWarning() << "[CONSOLE] Forcing stop of telemetry socket";
    Network::Network::get()->stopTelemetrySocket();
}

void ConsolePrivate::execdsock_start()
{
    Network::Network::get()->startExecdSocket(QString(CONFIG("remoteIP").toString() + ":" +
                                                      CONFIG("execdPort").toString()),
                                              QString(CONFIG("localIP").toString() + ":" +
                                                      CONFIG("feedbackPort").toString()));
}

void ConsolePrivate::execdsock_stop()
{
    Network::Network::get()->stopExecdSocket();
}

void ConsolePrivate::tcp_start()
{
    Network::Network::get()->startTCPSocket(QString(CONFIG("localIP").toString() + ":" +
                                                    CONFIG("lfsPort").toString()));
}

void ConsolePrivate::tcp_stop()
{
    Network::Network::get()->stopTCPSocket();
}

void ConsolePrivate::sim()
{
    #ifdef Q_OS_WIN
        QProcess::startDetached(QCoreApplication::applicationDirPath() + "/QuaSAR-Emulator.exe", {});
    #else
        QProcess::startDetached(QCoreApplication::applicationDirPath() + "/QuaSAR-Emulator", {});
    #endif
}
