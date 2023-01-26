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
    calculateVelocities(RuntimeData::get()->getFlatDirection(), RuntimeData::get()->getSpeed());
    moveByVelocity();
    udpEmulator->emulatorTelemetry.elevation = (RuntimeData::get()->getElevation() + RuntimeData::get()->getPitch() / 10);
    //qDebug()<<RuntimeData::initialize()->getElevation() << RuntimeData::initialize()->getSeaLevel();

    LinkerQML::fixedUpdate();
}

void FlightEmulator::changeVelocity(void)
{
    float velocity = RuntimeData::get()->getSpeed();
    float th = (float)RuntimeData::get()->getThrottle();

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
    float yaw = RuntimeData::get()->getYaw() / 90;
    float correction = qAbs(2 * qCos(qDegreesToRadians(azimuth))) + 1;
    float roll = RuntimeData::get()->getRoll() / 40;
    velocity_lat = velocity * qCos(qDegreesToRadians(azimuth + yaw * 6 * correction + roll));
    velocity_lon = velocity * qSin(qDegreesToRadians(azimuth + yaw * 6 * correction + roll));
}

void FlightEmulator::moveByVelocity(void)
{
    udpEmulator->emulatorTelemetry.latitude = (RuntimeData::get()->getLatitude() + SMath::metersToDegrees(velocity_lat * 0.001 * DEFAULT_UPDATE_PERIOD / 3.6));
    udpEmulator->emulatorTelemetry.longitude = (RuntimeData::get()->getLongitude() + SMath::metersToDegrees(velocity_lon * 0.001 * DEFAULT_UPDATE_PERIOD / 3.6));
}

void FlightEmulator::startEmulator(void)
{
    udpEmulator = new UDPEmulator(this);
    LinkerQML::startFlightEmulator();
    RuntimeData::get()->setLatitude(DEFAULT_COORDINATE.latitude());
    RuntimeData::get()->setLongitude(DEFAULT_COORDINATE.longitude());
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
    qreal throttle = RuntimeData::get()->getThrottle() + value;
    if(throttle > 100 || throttle < 0)
        return;
    RuntimeData::get()->setThrottle(throttle);
}

void FlightEmulator::yawChange(int value)
{
    qreal yaw = RuntimeData::get()->getYaw() + value * 5;
    if(yaw > 90 || yaw < -90)
        return;
    RuntimeData::get()->setYaw(yaw);
    yawTimer->start(1000);
}

void FlightEmulator::rollChange(int value)
{
    qreal roll = RuntimeData::get()->getRoll() + value;
    if(roll > 85 || roll < -85)
        return;
    udpEmulator->emulatorTelemetry.roll = (roll);
}

void FlightEmulator::pitchChange(int value)
{
    qreal pitch = RuntimeData::get()->getPitch() + value;
    if(pitch > 85 || pitch < -85)
        return;
    udpEmulator->emulatorTelemetry.pitch = (pitch);
}

void FlightEmulator::yawReset() { RuntimeData::get()->setYaw(0); }
