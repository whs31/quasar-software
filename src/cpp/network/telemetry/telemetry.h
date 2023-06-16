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
        Q_PROPERTY(double seaLevel READ seaLevel WRITE setSeaLevel NOTIFY seaLevelChanged)

        public:
            explicit Telemetry(QObject* parent = nullptr);

            [[nodiscard]] double latitude() const; void setLatitude(double);
            [[nodiscard]] double longitude() const; void setLongitude(double);
            [[nodiscard]] double altitude() const; void setAltitude(double);
            [[nodiscard]] double velocityCourse() const; void setVelocityCourse(double);
            [[nodiscard]] double velocityEast() const; void setVelocityEast(double);
            [[nodiscard]] double velocityNorth() const; void setVelocityNorth(double);
            [[nodiscard]] double velocityVertical() const; void setVelocityVertical(double);
            [[nodiscard]] double pitch() const; void setPitch(double);
            [[nodiscard]] double roll() const; void setRoll(double);
            [[nodiscard]] double yaw() const; void setYaw(double);
            [[nodiscard]] double course() const; void setCourse(double);
            [[nodiscard]] uint64_t time() const; void setTime(const uint64_t&);
            [[nodiscard]] int satellites() const; void setSatellites(int);
            [[nodiscard]] double seaLevel() const; void setSeaLevel(double);

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
                void seaLevelChanged();

        private:
            QDateTime m_datetime;
            TelemetryDatagram datagram;
            double m_seaLevel = 0;
    };
} // namespace Network

Q_DECLARE_METATYPE(Network::Telemetry*)
