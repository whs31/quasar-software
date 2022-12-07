#include "ftelemetry.h"

FTelemetry::FTelemetry(QObject *parent)
    : QObject{parent}
{

}

float FTelemetry::latitude()    { return _latitude; }   void FTelemetry::setLatitude(float value)  { if(value == _latitude) return; _latitude = value; emit latitudeChanged(); }
float FTelemetry::longitude()   { return _longitude; }  void FTelemetry::setLongitude(float value) { if(value == _longitude) return; _longitude = value; emit longitudeChanged(); }
float FTelemetry::elevation()   { return _elevation; }  void FTelemetry::setElevation(float value) { if(value == _elevation) return; _elevation = value; emit elevationChanged(); }
float FTelemetry::speed()       { return _speed; }      void FTelemetry::setSpeed(float value)     { if(value == _speed) return; _speed = value; emit speedChanged(); }
short FTelemetry::sats()        { return _sats; }       void FTelemetry::setSats(short value)      { if(value == _sats) return; _sats = value; emit satsChanged(); }
