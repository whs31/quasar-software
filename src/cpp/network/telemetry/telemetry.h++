#pragma once

#include <Definitions>
#include "telemetrydatagram.h++"
#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QDateTime>

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
                __property_signal latitudeChanged();
                __property_signal longitudeChanged();
                __property_signal altitudeChanged();
                __property_signal velocityCourseChanged();
                __property_signal velocityEastChanged();
                __property_signal velocityNorthChanged();
                __property_signal velocityVerticalChanged();
                __property_signal pitchChanged();
                __property_signal rollChanged();
                __property_signal yawChanged();
                __property_signal courseChanged();
                __property_signal timeChanged();
                __property_signal satellitesChanged();

        private:
            QDateTime m_datetime;
            TelemetryDatagram datagram;
    };
} // namespace Network

Q_DECLARE_METATYPE(Network::Telemetry*)
