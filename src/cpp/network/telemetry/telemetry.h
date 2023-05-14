#pragma once

#include "telemetrydatagram.h"
#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QDateTime>
#include <ccl/ccl_global.h>

namespace Network
{
    class Telemetry : public QObject
    {
        Q_OBJECT
        PROPERTY(double, latitude, setLatitude, datagram.latitude)
        PROPERTY(double, longitude, setLongitude, datagram.longitude)
        PROPERTY_DEF(double, altitude, setAltitude, datagram.altitude)
        PROPERTY_DEF(double, velocityCourse, setVelocityCourse, datagram.velocity_course)
        PROPERTY_DEF(double, velocityEast, setVelocityEast, datagram.velocity_east)
        PROPERTY_DEF(double, velocityNorth, setVelocityNorth, datagram.velocity_north)
        PROPERTY_DEF(double, velocityVertical, setVelocityVertical, datagram.velocity_vertical)
        PROPERTY_DEF(double, pitch, setPitch, datagram.pitch)
        PROPERTY_DEF(double, roll, setRoll, datagram.roll)
        PROPERTY_DEF(double, yaw, setYaw, datagram.yaw)
        PROPERTY_DEF(double, course, setCourse, datagram.course)
        PROPERTY_DEF(uint64_t, time, setTime, datagram.time)
        PROPERTY_DEF(int, satellites, setSatellites, datagram.satellites)

        public:
            explicit Telemetry(QObject* parent = nullptr);

            signals:
                void latitudeChanged();
                void longitudeChanged();
                void altitudeChanged();
                void velocityCourseChanged();
                void velocityEastChanged();
                void velocityNorthChanged();
                void velocityVerticalChanged();
                void pitchChanged();
                void rollChanged();
                void yawChanged();
                void courseChanged();
                void timeChanged();
                void satellitesChanged();

        private:
            QDateTime m_datetime;
            TelemetryDatagram datagram;
    };
} // namespace Network

Q_DECLARE_METATYPE(Network::Telemetry*)
