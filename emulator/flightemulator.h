#ifndef FLIGHTEMULATOR_H
#define FLIGHTEMULATOR_H

#include <QObject>
#include "runtimedata.h"
#include <QTimer>
#include <QGeoCoordinate>
#include "linkerqml.h"
#include "udpemulator.h"

class FlightEmulator : public QObject
{
    Q_OBJECT
public:
    explicit FlightEmulator(QObject *parent = nullptr);

    void startEmulator(void);
    void stopEmulator(void);

    void pitchChange(int value); //-1 to 1
    void rollChange(int value); //-1 to 1
    void yawChange(int Value); //-1 to 1
    void throttleChange(int Value); //-1 to 1

protected:
    quint16 DEFAULT_UPDATE_PERIOD = 200; //ms
    QGeoCoordinate DEFAULT_COORDINATE = QGeoCoordinate(60.0123, 30.0987);
    float DEFAULT_SPEED = 50; //km-h
    float DEFAULT_ELEVATION = 100; //m

private:
    QTimer* pitchTimer;
    QTimer* rollTimer;
    QTimer* yawTimer;

    QTimer* framerateTimer;

    float ϑlat = 0;
    float ϑlon = 0; //upvartheta

    void changeVelocity(void);
    void calculateVelocities(float θ, float ϑ); //theta, upvartheta
    void moveByVelocity(void);
    UDPEmulator* udpEmulator;

private slots:
    void pitchReset();
    void rollReset();
    void yawReset();

    void Update(void);

};

#endif // FLIGHTEMULATOR_H
