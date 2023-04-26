#include "console_p.h++"
#include "network/network.h++"
#include "debug/telemetrysocketemulator.h++"
#include "debug/feedbackemulator.h++"
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
    , m_telemetry_socket_emulator(new Debug::TelemetrySocketEmulator(this))
    , m_feedbackemulator(new Debug::FeedbackEmulator(this))
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

void ConsolePrivate::telsrv_start()
{
    if(not m_telemetry_socket_emulator)
        return;
    m_telemetry_socket_emulator->startTelemetryServer("127.0.0.1:9955");
}

void ConsolePrivate::telsrv_stop()
{
    if(not m_telemetry_socket_emulator)
        return;
    m_telemetry_socket_emulator->stop();
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

void ConsolePrivate::feedbackemu_init()
{
    m_feedbackemulator->setAddress(QString("127.0.0.1:" +
                                           CONFIG("feedbackPort").toString()));
}

void ConsolePrivate::feedbackemu_vt100()
{
    m_feedbackemulator->testVT100();
}

void ConsolePrivate::sim()
{
    #ifdef Q_OS_WIN
        QProcess::startDetached(QCoreApplication::applicationDirPath() + "/libs/quasar-emulator/QuaSAR-Emulator.exe", {});
    #else
        QProcess::startDetached(QCoreApplication::applicationDirPath() + "/libs/quasar-emulator/QuaSAR-Emulator", {});
    #endif
}
