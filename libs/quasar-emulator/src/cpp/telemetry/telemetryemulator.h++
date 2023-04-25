#pragma once

#include <QtCore/QObject>

#define __global static inline
#define __qml Q_INVOKABLE
#define __signal void

class QTimer;

class TelemetryEmulator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(float altitude READ altitude WRITE setAltitude NOTIFY altitudeChanged)
    Q_PROPERTY(float velocity_horizontal READ velocity_horizontal WRITE setVelocity_horizontal NOTIFY velocity_horizontalChanged)
    Q_PROPERTY(float velocity_vertical READ velocity_vertical WRITE setVelocity_vertical NOTIFY velocity_verticalChanged)
    Q_PROPERTY(float pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(float roll READ roll WRITE setRoll NOTIFY rollChanged)
    Q_PROPERTY(float course READ course WRITE setCourse NOTIFY courseChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(bool inFlight READ inFlight WRITE setInFlight NOTIFY inFlightChanged)

    constexpr __global uint32_t UPDATE_INTERVAL_MS = 100;
    constexpr __global float VELOCITY_CHANGE_COEFFICIENT = 0.40f;
    constexpr __global float SPEED_UPPER_BOUND = 50;

    QTimer* timer;

    double m_latitude;
    double m_longitude;
    float m_altitude;
    float m_velocity_horizontal;
    float m_velocity_vertical;
    float m_pitch;
    float m_roll;
    float m_course;
    QString m_time;
    bool m_inFlight;

    public:
        explicit TelemetryEmulator(QObject* parent = nullptr);

        __qml void start(double latitude = 60, double longitude = 30, float altitude = 300, float start_velocity = 30);
        __qml void stop();

        __qml QString getOsmConfig();

        double latitude() const;
        void setLatitude(double other);

        double longitude() const;
        void setLongitude(double other);

        float altitude() const;
        void setAltitude(float other);

        float velocity_horizontal() const;
        void setVelocity_horizontal(float other);

        float velocity_vertical() const;
        void setVelocity_vertical(float other);

        float pitch() const;
        void setPitch(float other);

        float roll() const;
        void setRoll(float other);

        float course() const;
        void setCourse(float other);

        QString time() const;
        void setTime(const QString& other);

        bool inFlight() const;
        void setInFlight(bool other);

        signals:
            __signal latitudeChanged();
            __signal longitudeChanged();
            __signal altitudeChanged();
            __signal velocity_horizontalChanged();
            __signal velocity_verticalChanged();
            __signal pitchChanged();
            __signal rollChanged();
            __signal courseChanged();
            __signal timeChanged();
            __signal inFlightChanged();

    private:
        void update();
};

