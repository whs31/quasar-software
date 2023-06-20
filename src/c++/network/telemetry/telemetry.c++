#include "telemetry.h"

using namespace Network;

Telemetry::Telemetry(QObject *parent)
    : QObject{parent}
{ }

double Telemetry::latitude() const { return datagram.latitude; }
void Telemetry::setLatitude(double other) {
    if (qFuzzyCompare(datagram.latitude, other)) return;
    if (qFuzzyCompare(other, 0)) return;
    datagram.latitude = other;
    emit latitudeChanged();
}

double Telemetry::longitude() const { return datagram.longitude; }
void Telemetry::setLongitude(double other) {
    if (qFuzzyCompare(datagram.longitude, other)) return;
    if (qFuzzyCompare(other, 0)) return;
    datagram.longitude = other;
    emit longitudeChanged();
}

double Telemetry::altitude() const { return datagram.altitude; }
void Telemetry::setAltitude(double other) {
    if(abs(other) > 20'000)
        return;
    if (qFuzzyCompare(datagram.altitude, other)) return;
    datagram.altitude = other;
    emit altitudeChanged();
}

double Telemetry::velocityCourse() const { return datagram.velocity_course; }
void Telemetry::setVelocityCourse(double other) {
    if (qFuzzyCompare(datagram.velocity_course, other)) return;
    datagram.velocity_course = other;
    emit velocityCourseChanged();
}

double Telemetry::velocityEast() const { return datagram.velocity_east; }
void Telemetry::setVelocityEast(double other) {
    if (qFuzzyCompare(datagram.velocity_east, other)) return;
    datagram.velocity_east = other;
    emit velocityEastChanged();
}

double Telemetry::velocityNorth() const { return datagram.velocity_north; }
void Telemetry::setVelocityNorth(double other) {
    if (qFuzzyCompare(datagram.velocity_north, other)) return;
    datagram.velocity_north = other;
    emit velocityNorthChanged();
}

double Telemetry::velocityVertical() const { return datagram.velocity_vertical; }
void Telemetry::setVelocityVertical(double other) {
    if (qFuzzyCompare(datagram.velocity_vertical, other)) return;
    datagram.velocity_vertical = other;
    emit velocityVerticalChanged();
}

double Telemetry::pitch() const { return datagram.pitch; }
void Telemetry::setPitch(double other) {
    if (qFuzzyCompare(datagram.pitch, other)) return;
    datagram.pitch = other;
    emit pitchChanged();
}

double Telemetry::roll() const { return datagram.roll; }
void Telemetry::setRoll(double other) {
    if (qFuzzyCompare(datagram.roll, other)) return;
    datagram.roll = other;
    emit rollChanged();
}

double Telemetry::yaw() const { return datagram.yaw; }
void Telemetry::setYaw(double other) {
    if (qFuzzyCompare(datagram.yaw, other)) return;
    datagram.yaw = other;
    emit yawChanged();
}

double Telemetry::course() const { return datagram.course; }
void Telemetry::setCourse(double other) {
    if (qFuzzyCompare(datagram.course, other)) return;
    datagram.course = other;
    emit courseChanged();
}

uint64_t Telemetry::time() const { return datagram.time; }
void Telemetry::setTime(const uint64_t& other) {
    if (datagram.time == other) return;
    datagram.time = other;
    emit timeChanged();
}

int Telemetry::satellites() const { return datagram.satellites; }
void Telemetry::setSatellites(int other) {
    if (datagram.satellites == other) return;
    datagram.satellites = other;
    emit satellitesChanged();
}

double Telemetry::seaLevel() const { return m_seaLevel; }
void Telemetry::setSeaLevel(double o) {
    if (qFuzzyCompare(m_seaLevel, o))
        return;
    m_seaLevel = o;
    emit seaLevelChanged();
}
