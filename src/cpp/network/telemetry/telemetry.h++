#pragma once

#include "definitions.h++"
#include "telemetrydatagram.h++"
#include <QtCore/QObject>

namespace Network
{
    class Telemetry : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(uint32_t marker READ marker WRITE setMarker NOTIFY markerChanged)
        Q_PROPERTY(uint8_t version READ version WRITE setVersion NOTIFY versionChanged)
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

        TelemetryDatagram datagram;

        public:
            explicit Telemetry(QObject *parent = nullptr);

            uint32_t marker() const;
            void setMarker(uint32_t other);
            uint8_t version() const;
            void setVersion(uint8_t other);
            double latitude() const;
            void setLatitude(double other);
            double longitude() const;
            void setLongitude(double other);
            double altitude() const;
            void setAltitude(double other);
            double velocityCourse() const;
            void setVelocityCourse(double other);
            double velocityEast() const;
            void setVelocityEast(double other);
            double velocityNorth() const;
            void setVelocityNorth(double other);
            double velocityVertical() const;
            void setVelocityVertical(double other);
            double pitch() const;
            void setPitch(double other);
            double roll() const;
            void setRoll(double other);
            double yaw() const;
            void setYaw(double other);
            double course() const;
            void setCourse(double other);
            uint64_t time() const;
            void setTime(uint64_t other);

            signals:
                __signal markerChanged();
                __signal versionChanged();
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
    };
} // namespace Network

