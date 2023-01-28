#ifndef DATATELEMETRY_H
#define DATATELEMETRY_H

#include <QObject>

class DataTelemetry : public QObject
{
    Q_OBJECT

    // телеметрия
    Q_PROPERTY(qreal latitude                       READ getLatitude            WRITE setLatitude            NOTIFY latitudeChanged)
    Q_PROPERTY(qreal longitude                      READ getLongitude           WRITE setLongitude           NOTIFY longitudeChanged)
    Q_PROPERTY(qreal elevation                      READ getElevation           WRITE setElevation           NOTIFY elevationChanged)
    Q_PROPERTY(qreal speed                          READ getSpeed               WRITE setSpeed               NOTIFY speedChanged)
    Q_PROPERTY(qreal seaLevel                       READ getSeaLevel            WRITE setSeaLevel            NOTIFY seaLevelChanged)
    Q_PROPERTY(qint16 satellites                    READ getSatellites          WRITE setSatellites          NOTIFY satellitesChanged)

    // значения связанных осей
    Q_PROPERTY(qreal pitch                          READ getPitch               WRITE setPitch               NOTIFY pitchChanged)
    Q_PROPERTY(qreal roll                           READ getRoll                WRITE setRoll                NOTIFY rollChanged)
    Q_PROPERTY(qreal yaw                            READ getYaw                 WRITE setYaw                 NOTIFY yawChanged)     //deprecated!
    Q_PROPERTY(qreal throttle                       READ getThrottle            WRITE setThrottle            NOTIFY throttleChanged)//deprecated!

public:
    static DataTelemetry* get(QObject* parent = nullptr);

    qreal getLatitude();                                                void setLatitude(qreal value);
    qreal getLongitude();                                               void setLongitude(qreal value);
    qreal getElevation();                                               void setElevation(qreal value);
    qreal getSpeed();                                                   void setSpeed(qreal value);
    qreal getSeaLevel();                                                void setSeaLevel(qreal value);
    qint16 getSatellites();                                             void setSatellites(qint16 value);

    qreal getPitch();                                                   void setPitch(qreal value);
    qreal getRoll();                                                    void setRoll(qreal value);
    qreal getYaw();                                                     void setYaw(qreal value);       //deprecated!
    qreal getThrottle();                                                void setThrottle(qreal value); //deprecated!

signals:
    void latitudeChanged();
    void longitudeChanged();
    void elevationChanged();
    void speedChanged();
    void seaLevelChanged();
    void satellitesChanged();

    void pitchChanged();
    void rollChanged();
    void yawChanged();      //deprecated~!
    void throttleChanged(); //deprecated~!

private:
    static DataTelemetry* _instance;
    explicit DataTelemetry(QObject *parent = nullptr);

    qreal latitude = 0;
    qreal longitude = 0;
    qreal elevation = 0;
    qreal speed = 0;
    qreal direction = -1;
    qreal pitchAngle = -1;
    qreal rollAngle = -1;
    qreal seaLevel = 0;
    qint16 satellites = -1;

    qreal pitch = 0;
    qreal roll = 0;
    qreal yaw = 0; //deprecated!
    qreal throttle = 0; //deprecated!
};

#endif // DATATELEMETRY_H
