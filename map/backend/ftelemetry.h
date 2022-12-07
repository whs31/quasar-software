#ifndef FTELEMETRY_H
#define FTELEMETRY_H

#include <QObject>
#include <qqml.h>

class FTelemetry : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(float latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged);
    //Q_PROPERTY(float longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged);
    //Q_PROPERTY(float elevation READ elevation WRITE setElevation NOTIFY elevationChanged);
    //Q_PROPERTY(float speed READ speed WRITE setSpeed NOTIFY speedChanged);
    //Q_PROPERTY(int sats READ sats WRITE setSats NOTIFY satsChanged);
    //QML_ELEMENT



public:
    explicit FTelemetry(QObject *parent = nullptr);

    float latitude();
    float longitude();
    float elevation();
    float speed();
    int sats();
    
    void setLatitude(float &latitude);
    void setLongitude(float &longitude);
    void setElevation(float &elevation);
    void setSpeed(float &speed);
    void setSats(int &sats);

signals:
    void latitudeChanged();
    void longitudeChanged();
    void elevationChanged();
    void speedChanged();
    void satsChanged();

private:
    float _latitude;
    float _longitude;
    float _elevation;
    float _speed;
    int _sats;

};

#endif // FTELEMETRY_H
