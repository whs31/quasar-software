#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <QObject>
#include <qqml.h>

class RuntimeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float latitude READ getLatitude WRITE setLatitude);//NOTIFY latitudeChanged);
    Q_PROPERTY(float longitude READ getLongitude WRITE setLongitude);// NOTIFY longitudeChanged);
    Q_PROPERTY(float elevation READ getElevation WRITE setElevation);// NOTIFY elevationChanged);
    Q_PROPERTY(float speed READ getSpeed WRITE setSpeed );//NOTIFY);// speedChanged);
    Q_PROPERTY(int satellites READ getSatellites WRITE setSatellites);// NOTIFY satsChanged);
    QML_ELEMENT
    
public:
    static RuntimeData* initialize(QObject* parent = nullptr);
    static qreal getLatitude();
    static qreal getLongitude();
    static qreal getElevation();
    static qreal getSpeed();
    static qint16 getSatellites();

    static void setLatitude(qreal value);
    static void setLongitude(qreal value);
    static void setElevation(qreal value);
    static void setSpeed(qreal value);
    static void setSatellites(qint16 value);

private:
    static RuntimeData* _instance;
    explicit RuntimeData(QObject *parent = nullptr);
    struct Telemetry 
    {
        qreal latitude = 0;
        qreal longitude = 0;
        qreal elevation = 0;
        qreal speed = 0;
        qreal direction = -1; //TODO: direction
        qint16 satellites = -1; 
    };
    static Telemetry telemetry;

signals:
    // static void latitudeChanged();
    // static void longitudeChanged();
    // static void elevationChanged();
    // static void speedChanged();
    // static void satellitesChanged();
};

#endif // RUNTIMEDATA_H
