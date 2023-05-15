#pragma once

#include "telemetrydatagram.h"
#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QDateTime>

namespace Network
{
    class Telemetry : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
        Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)
        Q_PROPERTY(double altitude READ altitude WRITE setAltitude NOTIFY altitudeChanged)
        Q_PROPERTY(double velocityCourse READ velocityCourse WRITE setVelocityCourse NOTIFY velocityCourseChanged)
        Q_PROPERTY(double velocityEast READ velocityEast WRITE setVelocityEast NOTIFY velocityEastChanged)
        Q_PROPERTY(double velocityNorth READ velocityNorth WRITE setVelocityNorth NOTIFY velocityNorthChanged)
        Q_PROPERTY(double velocityVertical READ velocityVertical WRITE setVelocityVertical NOTIFY velocityVerticalChanged)
        Q_PROPERTY(double pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
        Q_PROPERTY(double roll READ roll WRITE setRoll NOTIFY rollChanged)
        Q_PROPERTY(double yaw READ yaw WRITE setYaw NOTIFY yawChanged)
        Q_PROPERTY(double course READ course WRITE setCourse NOTIFY courseChanged)
        Q_PROPERTY(uint64_t time READ time WRITE setTime NOTIFY timeChanged)
        Q_PROPERTY(int satellites READ satellites WRITE setSatellites NOTIFY satellitesChanged)


        public:
            explicit Telemetry(QObject* parent = nullptr);

            double latitude() const; void setLatitude(double);
            double longitude() const; void setLongitude(double);
            double altitude() const; void setAltitude(double);
            double velocityCourse() const; void setVelocityCourse(double);
            double velocityEast() const; void setVelocityEast(double);
            double velocityNorth() const; void setVelocityNorth(double);
            double velocityVertical() const; void setVelocityVertical(double);
            double pitch() const; void setPitch(double);
            double roll() const; void setRoll(double);
            double yaw() const; void setYaw(double);
            double course() const; void setCourse(double);
            uint64_t time() const; void setTime(const uint64_t&);
            int satellites() const; void setSatellites(int);

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
