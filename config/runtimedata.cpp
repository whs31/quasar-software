#include "runtimedata.h"

RuntimeData* RuntimeData::_instance = nullptr;
RuntimeData::Telemetry RuntimeData::telemetry;
RuntimeData* RuntimeData::initialize(QObject* parent)
{
    if(_instance != NULL)
        return _instance;
    _instance = new RuntimeData(parent);
    return _instance;
}
RuntimeData::RuntimeData(QObject *parent) : QObject{parent} {}

qreal RuntimeData::getLatitude()    { return telemetry.latitude; }
void RuntimeData::setLatitude(qreal value)  { if(value == telemetry.latitude) return; telemetry.latitude = value; }//emit latitudeChanged(); }

qreal RuntimeData::getLongitude()   { return telemetry.longitude; }
void RuntimeData::setLongitude(qreal value) { if(value == telemetry.longitude) return; telemetry.longitude = value; }// emit longitudeChanged(); }

qreal RuntimeData::getElevation()   { return telemetry.elevation; }
void RuntimeData::setElevation(qreal value) { if(value == telemetry.elevation) return; telemetry.elevation = value; }//emit elevationChanged(); }

qreal RuntimeData::getSpeed()       { return telemetry.speed; }
void RuntimeData::setSpeed(qreal value)     { if(value == telemetry.speed) return; telemetry.speed = value; }//emit speedChanged(); }

qint16 RuntimeData::getSatellites()        { return telemetry.satellites; }
void RuntimeData::setSatellites(short value)      { if(value == telemetry.satellites) return; telemetry.satellites = value; }//emit satellitesChanged(); }