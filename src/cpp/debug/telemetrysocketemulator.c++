#include "telemetrysocketemulator.h++"
#include <QtCore/QDebug>
#include <QtNetwork/QUdpSocket>

using namespace Debug;

TelemetrySocketEmulator::TelemetrySocketEmulator(QObject* parent)
    : QObject{parent}
    , socket(new QUdpSocket(this))
{

}

void TelemetrySocketEmulator::startTelemetryServer(const QString& address)
{
    qInfo().noquote() << "[DEBUG] Starting telemetry server emulator at" << address;
}

void TelemetrySocketEmulator::stop()
{
    qInfo() << "[DEBUG] Stopping telemetry server emulator...";
}

