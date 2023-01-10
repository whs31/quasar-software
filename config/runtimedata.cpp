#include "runtimedata.h"

RuntimeData *RuntimeData::_instance = nullptr;
short int RuntimeData::mouseState = MouseState::Blank;
RuntimeData *RuntimeData::initialize(QObject *parent)
{
    if (_instance != NULL)
        return _instance;
    _instance = new RuntimeData(parent);
    return _instance;
}
RuntimeData::RuntimeData(QObject *parent) : QObject{parent} {}

qreal RuntimeData::getLatitude() { return telemetry.latitude; }
void RuntimeData::setLatitude(qreal value)
{
    if (value == telemetry.latitude)
        return;
    telemetry.latitude = value;
    emit latitudeChanged();
}

qreal RuntimeData::getLongitude() { return telemetry.longitude; }
void RuntimeData::setLongitude(qreal value)
{
    if (value == telemetry.longitude)
        return;
    telemetry.longitude = value;
    emit longitudeChanged();
}

qreal RuntimeData::getElevation() { return telemetry.elevation; }
void RuntimeData::setElevation(qreal value)
{
    if (value == telemetry.elevation)
        return;
    telemetry.elevation = value;
    emit elevationChanged();
}

qreal RuntimeData::getSpeed() { return telemetry.speed; }
void RuntimeData::setSpeed(qreal value)
{
    if (value == telemetry.speed)
        return;
    telemetry.speed = value;
    emit speedChanged();
}

qint16 RuntimeData::getSatellites() { return telemetry.satellites; }
void RuntimeData::setSatellites(short value)
{
    if (value == telemetry.satellites)
        return;
    telemetry.satellites = value;
    emit satellitesChanged();
}

qreal RuntimeData::getPitch() { return aircraftAxes.pitch; }
void RuntimeData::setPitch(qreal value)
{
    if (value == aircraftAxes.pitch)
        return;
    aircraftAxes.pitch = value;
    emit pitchChanged();
}

qreal RuntimeData::getRoll() { return aircraftAxes.roll; }
void RuntimeData::setRoll(qreal value)
{
    if (value == aircraftAxes.roll)
        return;
    aircraftAxes.roll = value;
    emit rollChanged();
}

qreal RuntimeData::getYaw() { return aircraftAxes.yaw; }
void RuntimeData::setYaw(qreal value)
{
    if (value == aircraftAxes.yaw)
        return;
    aircraftAxes.yaw = value;
    emit yawChanged();
}

bool RuntimeData::getFollowPlane() { return mapSettings.followPlane; }
void RuntimeData::setFollowPlane(bool state)
{
    if (state == mapSettings.followPlane)
        return;
    mapSettings.followPlane = state;
}

bool RuntimeData::getDrawTooltip() { return mapSettings.drawTooltip; }
void RuntimeData::setDrawTooltip(bool state) 
{
    if (state == mapSettings.drawTooltip)
        return;
    mapSettings.drawTooltip = state;
}

bool RuntimeData::getDrawRoute() { return mapSettings.drawRoute; }
void RuntimeData::setDrawRoute(bool state) 
{
    if (state == mapSettings.drawRoute)
        return;
    mapSettings.drawRoute = state;
    emit drawRouteChanged();
}

bool RuntimeData::getDrawPredict() { return mapSettings.drawPredict; }
void RuntimeData::setDrawPredict(bool state) 
{
    if (state == mapSettings.drawPredict)
        return;
    mapSettings.drawPredict = state;
    emit drawPredictChanged();
}

bool RuntimeData::getDrawDiagram() { return mapSettings.drawDiagram; }
void RuntimeData::setDrawDiagram(bool state) 
{
    if (state == mapSettings.drawDiagram)
        return;
    mapSettings.drawDiagram = state;
    emit drawDiagramChanged();
}

bool RuntimeData::getGlobal_useOSMMaps() { return SConfig::getHashBoolean("UseOSM"); }
qreal RuntimeData::getGlobal_velocityVectorLength() { return SConfig::getHashFloat("VelocityVectorLength"); }

bool RuntimeData::getConnected() { return connectionStatus.connected; }
void RuntimeData::setConnected(bool state) 
{
    if (state == connectionStatus.connected)
        return;
    connectionStatus.connected = state;
    emit connectedChanged();
}

QString RuntimeData::getSARIP() { return connectionStatus.sarIP; }
void RuntimeData::setSARIP(QString string) 
{
    if (string == connectionStatus.sarIP)
        return;
    connectionStatus.sarIP = string;
    emit SARIPChanged();
}

QString RuntimeData::getPCIP() { return connectionStatus.pcIP; }
void RuntimeData::setPCIP(QString string) 
{
    if (string == connectionStatus.pcIP)
        return;
    connectionStatus.pcIP = string;
    emit PCIPChanged();
}

QString RuntimeData::getTelemetryPort() { return connectionStatus.telemetryPort; }
void RuntimeData::setTelemetryPort(QString string) 
{
    if (string == connectionStatus.telemetryPort)
        return;
    connectionStatus.telemetryPort = string;
    emit telemetryPortChanged();
}

QString RuntimeData::getLoaderPort() { return connectionStatus.loaderPort; }
void RuntimeData::setLoaderPort(QString string) 
{
    if (string == connectionStatus.loaderPort)
        return;
    connectionStatus.loaderPort = string;
    emit loaderPortChanged();
}

QString RuntimeData::getCommandPort() { return connectionStatus.commandPort; }
void RuntimeData::setCommandPort(QString string) 
{
    if (string == connectionStatus.commandPort)
        return;
    connectionStatus.commandPort = string;
    emit commandPortChanged();
}

QString RuntimeData::getListenPort() { return connectionStatus.listenPort; }
void RuntimeData::setListenPort(QString string) 
{
    if (string == connectionStatus.listenPort)
        return;
    connectionStatus.listenPort = string;
    emit listenPortChanged();
}

qreal RuntimeData::getLoadingProgress() { return connectionStatus.loadingProgress; }
void RuntimeData::setLoadingProgress(qreal value) 
{
    if (value == connectionStatus.loadingProgress)
        return;
    connectionStatus.loadingProgress = value;
    emit loadingProgressChanged();
}

qreal RuntimeData::getFormProgress() { return connectionStatus.formProgress; }
void RuntimeData::setFormProgress(qreal value) 
{
    if (value == connectionStatus.formProgress)
        return;
    connectionStatus.formProgress = value;
    emit formProgressChanged();
}

QString RuntimeData::getFormStatus() { return connectionStatus.formStatus; }
void RuntimeData::setFormStatus(QString string) 
{
    if (string == connectionStatus.formStatus)
        return;
    connectionStatus.formStatus = string;
    emit formStatusChanged();
}

QString RuntimeData::getLoaderStatus() { return connectionStatus.loaderStatus; }
void RuntimeData::setLoaderStatus(QString string) 
{
    if (string == connectionStatus.loaderStatus)
        return;
    connectionStatus.loaderStatus = string;
    emit loaderStatusChanged();
}