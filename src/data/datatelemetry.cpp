#include "datatelemetry.h"

DataTelemetry *DataTelemetry::_instance = nullptr;
DataTelemetry *DataTelemetry::get(QObject *parent) { if (_instance != NULL) return _instance;
_instance = new DataTelemetry(parent); return _instance; }
DataTelemetry::DataTelemetry(QObject *parent) : QObject{parent} {}

qreal DataTelemetry::getLatitude() { return latitude; }
void DataTelemetry::setLatitude(qreal value) { if (value == latitude) return;
latitude = value; emit latitudeChanged(); }

qreal DataTelemetry::getLongitude() { return longitude; }
void DataTelemetry::setLongitude(qreal value) { if (value == longitude) return;
longitude = value; emit longitudeChanged(); }

qreal DataTelemetry::getElevation() { return elevation; }
void DataTelemetry::setElevation(qreal value) { if (value == elevation) return;
elevation = value; emit elevationChanged(); }

qreal DataTelemetry::getSpeed() { return speed; }
void DataTelemetry::setSpeed(qreal value) { if (value == speed) return;
speed = value; emit speedChanged(); }

qreal DataTelemetry::getSeaLevel() { return seaLevel; }
void DataTelemetry::setSeaLevel(qreal value) { if (value == seaLevel) return;
seaLevel = value; emit seaLevelChanged(); }

qint16 DataTelemetry::getSatellites() { return satellites; }
void DataTelemetry::setSatellites(short value) { if (value == satellites) return; 
satellites = value; emit satellitesChanged(); }

qreal DataTelemetry::getPitch() { return pitch; }
void DataTelemetry::setPitch(qreal value) { if (value == pitch) return;
pitch = value; emit pitchChanged(); }

qreal DataTelemetry::getRoll() { return roll; }
void DataTelemetry::setRoll(qreal value) { if (value == roll) return;
roll = value; emit rollChanged(); }

qreal DataTelemetry::getYaw() { return yaw; }
void DataTelemetry::setYaw(qreal value) { if (value == yaw) return;
yaw = value; emit yawChanged(); }

qreal DataTelemetry::getThrottle() { return throttle; }
void DataTelemetry::setThrottle(qreal value) { if (value == throttle) return;
throttle = value; emit throttleChanged(); }
