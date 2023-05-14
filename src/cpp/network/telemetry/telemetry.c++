#include "telemetry.h"

using namespace Network;

Telemetry::Telemetry(QObject *parent)
    : QObject{parent}
{ }

void Telemetry::setLatitude(const double& other) {
    if (qFuzzyCompare(datagram.latitude, other)) return;
    if (qFuzzyCompare(other, 0)) return;
    datagram.latitude = other;
    emit latitudeChanged();
}

void Telemetry::setLongitude(const double& other) {
    if (qFuzzyCompare(datagram.longitude, other)) return;
    if (qFuzzyCompare(other, 0)) return;
    datagram.longitude = other;
    emit longitudeChanged();
}
