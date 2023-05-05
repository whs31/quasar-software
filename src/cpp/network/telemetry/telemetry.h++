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

            __getter double latitude() const;
            __setter void setLatitude(double other);

            __getter double longitude() const;
            __setter void setLongitude(double other);

            __getter double altitude() const;
            __setter void setAltitude(double other);

            __getter double velocityCourse() const;
            __setter void setVelocityCourse(double other);

            __getter double velocityEast() const;
            __setter void setVelocityEast(double other);

            __getter double velocityNorth() const;
            __setter void setVelocityNorth(double other);

            __getter double velocityVertical() const;
            __setter void setVelocityVertical(double other);

            __getter double pitch() const;
            __setter void setPitch(double other);

            __getter double roll() const;
            __setter void setRoll(double other);

            __getter double yaw() const;
            __setter void setYaw(double other);

            __getter double course() const;
            __setter void setCourse(double other);

            __getter uint64_t time() const;
            __setter void setTime(const uint64_t& other);

            __getter int satellites() const;
            __setter void setSatellites(int other);

            signals:
                __signal latitudeChanged();
                __signal longitudeChanged();
                __signal altitudeChanged();
                __signal velocityCourseChanged();
                __signal velocityEastChanged();
                __signal velocityNorthChanged();
                __signal velocityVerticalChanged();
                __signal pitchChanged();
                __signal rollChanged();
                __signal yawChanged();
                __signal courseChanged();
                __signal timeChanged();
                __signal satellitesChanged();

        private:
            QDateTime m_datetime;
            TelemetryDatagram datagram;
    };
} // namespace Network

Q_DECLARE_METATYPE(Network::Telemetry*)
