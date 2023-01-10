#include "flightemulator.h"

FlightEmulator::FlightEmulator(QObject *parent)
    : QObject{parent}
{
    pitchTimer = new QTimer(this);
    rollTimer = new QTimer(this);
    yawTimer = new QTimer(this);
    connect(pitchTimer, SIGNAL(timeout()), this, SLOT(pitchReset()));
    connect(rollTimer, SIGNAL(timeout()), this, SLOT(rollReset()));
    connect(yawTimer, SIGNAL(timeout()), this, SLOT(yawReset()));
}

void FlightEmulator::throttleChange(int value)
{
    qreal throttle = RuntimeData::initialize()->getThrottle() + value;
    if(throttle > 100 || throttle < 0)
        return;
    RuntimeData::initialize()->setThrottle(throttle);
}

void FlightEmulator::yawChange(int value)
{
    qreal yaw = RuntimeData::initialize()->getYaw() + value * 5;
    if(yaw > 90 || yaw < -90)
        return;
    RuntimeData::initialize()->setYaw(yaw);
    yawTimer->start(1000);
}

void FlightEmulator::rollChange(int value)
{
    qreal roll = RuntimeData::initialize()->getRoll() + value * 5;
    if(roll > 45 || roll < -45)
        return;
    RuntimeData::initialize()->setRoll(roll);
    rollTimer->start(1000);
}

void FlightEmulator::pitchChange(int value)
{
    qreal pitch = RuntimeData::initialize()->getPitch() + value * 5;
    if(pitch > 45 || pitch < -45)
        return;
    RuntimeData::initialize()->setPitch(pitch);
    pitchTimer->start(1000);
}

void FlightEmulator::pitchReset() { RuntimeData::initialize()->setPitch(0); }
void FlightEmulator::rollReset() { RuntimeData::initialize()->setRoll(0); }
void FlightEmulator::yawReset() { RuntimeData::initialize()->setYaw(0); }