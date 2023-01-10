#ifndef FLIGHTEMULATOR_H
#define FLIGHTEMULATOR_H

#include <QObject>
#include "runtimedata.h"
#include <QTimer>

class FlightEmulator : public QObject
{
    Q_OBJECT
public:
    explicit FlightEmulator(QObject *parent = nullptr);

    void pitchChange(int value); //-1 to 1
    void rollChange(int value); 
    void yawChange(int Value);
    void throttleChange(int Value);

private:
    QTimer* pitchTimer;
    QTimer* rollTimer;
    QTimer* yawTimer;

private slots:
    void pitchReset();
    void rollReset();
    void yawReset();

};

#endif // FLIGHTEMULATOR_H
