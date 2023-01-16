#include "flightemulator.h"

FlightEmulator::FlightEmulator(QObject *parent)
    : QObject{parent}
{
    framerateTimer = new QTimer(this);
    framerateTimer->setInterval(DEFAULT_UPDATE_PERIOD);
    connect(framerateTimer, SIGNAL(timeout()), this, SLOT(Update()));
    yawTimer = new QTimer(this);
    connect(yawTimer, SIGNAL(timeout()), this, SLOT(yawReset()));
}

void FlightEmulator::Update(void)
{
    changeVelocity();
    calculateVelocities(RuntimeData::initialize()->getFlatDirection(), RuntimeData::initialize()->getSpeed());
    moveByVelocity();
    udpEmulator->emulatorTelemetry.elevation = (RuntimeData::initialize()->getElevation() - RuntimeData::initialize()->getPitch() / 10);
    //qDebug()<<RuntimeData::initialize()->getElevation() << RuntimeData::initialize()->getSeaLevel();

    LinkerQML::fixedUpdate();
}

void FlightEmulator::changeVelocity(void)
{
    float velocity = RuntimeData::initialize()->getSpeed();
    float th = (float)RuntimeData::initialize()->getThrottle();

    if(velocity > 10 * th - 10)
    {
        velocity = (10 * th);
        if(velocity < 2)
        {
            velocity = 3;
        }
    }
    if(velocity < 2)
    {
        velocity = 3;
    }
    velocity += 10;
    udpEmulator->emulatorTelemetry.speed = (velocity);
}

void FlightEmulator::calculateVelocities(float azimuth, float velocity)
{
    float yaw = RuntimeData::initialize()->getYaw() / 90;
    float correction = qAbs(2 * qCos(qDegreesToRadians(azimuth))) + 1;
    velocity_lat = velocity * qCos(qDegreesToRadians(azimuth + yaw * 6 * correction));
    velocity_lon = velocity * qSin(qDegreesToRadians(azimuth + yaw * 6 * correction));
}

void FlightEmulator::moveByVelocity(void)
{
    udpEmulator->emulatorTelemetry.latitude = (RuntimeData::initialize()->getLatitude() + SMath::metersToDegrees(velocity_lat * 0.001 * DEFAULT_UPDATE_PERIOD / 3.6));
    udpEmulator->emulatorTelemetry.longitude = (RuntimeData::initialize()->getLongitude() + SMath::metersToDegrees(velocity_lon * 0.001 * DEFAULT_UPDATE_PERIOD / 3.6));
}

void FlightEmulator::startEmulator(void)
{
    udpEmulator = new UDPEmulator(this);
    LinkerQML::startFlightEmulator();
    RuntimeData::initialize()->setLatitude(DEFAULT_COORDINATE.latitude());
    RuntimeData::initialize()->setLongitude(DEFAULT_COORDINATE.longitude());
    udpEmulator->emulatorTelemetry.latitude = DEFAULT_COORDINATE.latitude();
    udpEmulator->emulatorTelemetry.longitude = DEFAULT_COORDINATE.longitude();
    udpEmulator->emulatorTelemetry.speed = DEFAULT_SPEED;
    udpEmulator->emulatorTelemetry.elevation = DEFAULT_ELEVATION;
    LinkerQML::fixedUpdate();
    framerateTimer->start();
}

void FlightEmulator::stopEmulator(void)
{
    framerateTimer->stop();
    delete udpEmulator;
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
    qreal roll = RuntimeData::initialize()->getRoll() + value;
    if(roll > 45 || roll < -45)
        return;
    RuntimeData::initialize()->setRoll(roll);
}

void FlightEmulator::pitchChange(int value)
{
    qreal pitch = RuntimeData::initialize()->getPitch() + value;
    if(pitch > 45 || pitch < -45)
        return;
    RuntimeData::initialize()->setPitch(pitch);
}

void FlightEmulator::yawReset() { RuntimeData::initialize()->setYaw(0); }
