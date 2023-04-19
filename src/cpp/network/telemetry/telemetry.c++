#include "telemetry.h++"

using namespace Network;

Telemetry::Telemetry(QObject *parent)
    : QObject{parent}
{

}


uint32_t Telemetry::marker() const { return datagram.marker; }
void Telemetry::setMarker(uint32_t other) {
    if (datagram.marker == other) return;
    datagram.marker = other;
    emit markerChanged();
}

uint8_t Telemetry::version() const { return datagram.version; }
void Telemetry::setVersion(uint8_t other) {
    if (datagram.version == other) return;
    datagram.version = other;
    emit versionChanged();
}

double Telemetry::latitude() const { return datagram.latitude; }
void Telemetry::setLatitude(double other) {
    if (qFuzzyCompare(datagram.latitude, other)) return;
    datagram.latitude = other;
    emit latitudeChanged();
}

double Telemetry::longitude() const { return datagram.longitude; }
void Telemetry::setLongitude(double other) {
    if (qFuzzyCompare(datagram.longitude, other)) return;
    datagram.longitude = other;
    emit longitudeChanged();
}

double Telemetry::altitude() const { return datagram.altitude; }
void Telemetry::setAltitude(double other) {
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
void Telemetry::setTime(uint64_t other) {
    if (datagram.time == other) return;
    datagram.time = other;
    emit timeChanged();
}
