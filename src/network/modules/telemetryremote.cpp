#include "telemetryremote.h"

TelemetryRemote::TelemetryRemote(QObject *parent)
    : QObject{parent}
{
    updateTimer = new QTimer(this);
    timeoutTimer = new QTimer(this);
    udpRemote = new UDPRemote();

    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(askForTelemetry()));
    QObject::connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    QObject::connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(receiveTelemetry(QByteArray)));
}

TelemetryRemote::~TelemetryRemote()
{
    udpRemote->Disconnect();
    delete udpRemote;
}

void TelemetryRemote::connect(QString ip, quint16 port, qreal frequency)
{
    disconnect();
    updateTimer->start(frequency * 1000);
    timeoutTimer->start(TIMEOUT_TIME);
    udpRemote->Connect(ip + ":" + QString::number(port));
    Debug::Log("[TELEMETRY REMOTE] Listening to SAR on " + ip + ":" + QString::number(port) + " with frequency: "
                + QString::number(frequency) + " s");
}

void TelemetryRemote::disconnect(void)
{
    udpRemote->Disconnect();
    updateTimer->stop();
    timeoutTimer->stop();
    Debug::Log("[TELEMETRY REMOTE] Disconnecting...");
}

void TelemetryRemote::timeoutSlot(void)
{
    emit timeout();
    RuntimeData::get()->setConnected(false);
    Debug::Log("![TELEMETRY REMOTE] Reached TIMEOUT");
}

void TelemetryRemote::askForTelemetry(void)     
{ 
    udpRemote->Send(REQUEST_TELEMETRY_MARKER.toUtf8());
}

void TelemetryRemote::receiveTelemetry(QByteArray data)
{
    QString stringData = data.data();
    if(!stringData.startsWith(REQUEST_TELEMETRY_MARKER))
        return;
    timeoutTimer->start(TIMEOUT_TIME);
    m_satteliteDifferenceCheck = 0;
    
    parseTelemetry(data);
    LinkerQML::fixedUpdate();
    if (m_satteliteDifferenceCheck != 0 || m_differenceCheck != m_parsedDifferenceCheck)
        RuntimeData::get()->setConnected(true);
    else 
        RuntimeData::get()->setConnected(false);
}

void TelemetryRemote::parseTelemetry(QString data)
{
    data.remove(0, REQUEST_TELEMETRY_MARKER.length());

    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8());
    double latitude =  jsonDocument.object().value("Latitude").toDouble();
    double longitude =  jsonDocument.object().value("Longitude").toDouble();
    double speed =  jsonDocument.object().value("Speed").toDouble();
    double elevation =  jsonDocument.object().value("Elevation").toDouble(); 
    double satellites =  jsonDocument.object().value("Sats").toDouble(); 
    double pitch =  jsonDocument.object().value("Pitch").toDouble(); 
    double roll =  jsonDocument.object().value("Roll").toDouble(); 
    double course = jsonDocument.object().value("Direction").toDouble(); 

    DataTelemetry::get()->setLatitude(latitude);
    DataTelemetry::get()->setLongitude(longitude);
    DataTelemetry::get()->setElevation(elevation);
    DataTelemetry::get()->setSpeed(speed);
    DataTelemetry::get()->setSatellites(satellites);
    DataTelemetry::get()->setPitch(pitch);
    DataTelemetry::get()->setRoll(roll);

    m_parsedDifferenceCheck = latitude;
    m_satteliteDifferenceCheck = satellites;
}
