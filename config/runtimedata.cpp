#include "runtimedata.h"

RuntimeData *RuntimeData::_instance = nullptr;
RuntimeData::Telemetry RuntimeData::telemetry;
RuntimeData::MapSettings RuntimeData::mapSettings;
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
}

qreal RuntimeData::getLongitude() { return telemetry.longitude; }
void RuntimeData::setLongitude(qreal value)
{
    if (value == telemetry.longitude)
        return;
    telemetry.longitude = value;
}

qreal RuntimeData::getElevation() { return telemetry.elevation; }
void RuntimeData::setElevation(qreal value)
{
    if (value == telemetry.elevation)
        return;
    telemetry.elevation = value;
}

qreal RuntimeData::getSpeed() { return telemetry.speed; }
void RuntimeData::setSpeed(qreal value)
{
    if (value == telemetry.speed)
        return;
    telemetry.speed = value;
}

qint16 RuntimeData::getSatellites() { return telemetry.satellites; }
void RuntimeData::setSatellites(short value)
{
    if (value == telemetry.satellites)
        return;
    telemetry.satellites = value;
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
}

bool RuntimeData::getDrawPredict() { return mapSettings.drawPredict; }
void RuntimeData::setDrawPredict(bool state) 
{
    if (state == mapSettings.drawPredict)
        return;
    mapSettings.drawPredict = state;
}

bool RuntimeData::getDrawDiagram() { return mapSettings.drawDiagram; }
void RuntimeData::setDrawDiagram(bool state) 
{
    if (state == mapSettings.drawDiagram)
        return;
    mapSettings.drawDiagram = state;
}

bool RuntimeData::getGlobal_useOSMMaps() { return SConfig::getHashBoolean("UseOSM"); }
qreal RuntimeData::getGlobal_velocityVectorLength() { return SConfig::getHashFloat("VelocityVectorLength"); }