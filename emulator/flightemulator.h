#ifndef FLIGHTEMULATOR_H
#define FLIGHTEMULATOR_H

#include <QObject>
#include "runtimedata.h"

class FlightEmulator : public QObject
{
    Q_OBJECT
public:
    explicit FlightEmulator(QObject *parent = nullptr);
    void pitchChange(int value); //-1 to 1
    void rollChange(int value); 
    void yawChange(int Value);


signals:

};

#endif // FLIGHTEMULATOR_H
