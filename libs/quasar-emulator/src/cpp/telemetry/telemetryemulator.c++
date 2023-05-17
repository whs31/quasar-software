#include "telemetryemulator.h++"
#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QSaveFile>
#include <QtCore/QDebug>
#include <QtPositioning/QGeoCoordinate>
#include <cmath>

TelemetryEmulator::TelemetryEmulator(QObject *parent)
    : QObject{parent}
    , timer(new QTimer(this))
{
    QObject::connect(timer, &QTimer::timeout, this, &TelemetryEmulator::update);
}

void TelemetryEmulator::start(double latitude, double longitude, float altitude, float start_velocity)
{
    timer->start(UPDATE_INTERVAL_MS);

    this->setLatitude(latitude);
    this->setLongitude(longitude);
    this->setAltitude(altitude);
    this->setVelocity_horizontal(0);
    this->setVelocity_vertical(0);
    this->setPitch(0);
    this->setRoll(0);
    this->setCourse(0);
}

void TelemetryEmulator::stop()
{
    timer->stop();

    this->setLatitude(0);
    this->setLongitude(0);
    this->setAltitude(0);
    this->setVelocity_horizontal(0);
    this->setVelocity_vertical(0);
    this->setPitch(0);
    this->setRoll(0);
    this->setCourse(0);
    this->setTime("БПЛА не в полете");
}

QString TelemetryEmulator::getOsmConfig()
{
    QString config_path = QCoreApplication::applicationDirPath() + "/mapconfig";

    QDir dir(config_path);
    if(not dir.exists())
    {
        dir.mkpath(config_path);
        qInfo() << "[PATH] Created map config folder at " << config_path;
    }

    QString _satellite;
    QFile f_satellite(":/satellite");
    f_satellite.open(QIODevice::ReadOnly);
    _satellite = f_satellite.readAll();

    QSaveFile satellite(config_path + "/satellite");
    satellite.open(QIODevice::WriteOnly);
    QTextStream out1(&satellite);
    out1 << _satellite;
    satellite.commit();

    return config_path;
}

void TelemetryEmulator::update()
{
//    this->setLatitude(0);
//    this->setLongitude(0);
//    this->setAltitude(0);
//    this->setVelocity_horizontal(0);
//    this->setVelocity_vertical(0);
    float velocity_delta = sin(this->pitch() / 180 * M_PI) * VELOCITY_CHANGE_COEFFICIENT;
    velocity_delta = velocity_delta * (1 - velocity_horizontal() / SPEED_UPPER_BOUND);
    if(velocity_horizontal() > -SPEED_UPPER_BOUND)
        this->setVelocity_horizontal(velocity_horizontal() + velocity_delta);
    else
        this->setVelocity_horizontal(velocity_horizontal() - velocity_delta);

    float vertical_velocity_delta = cos(2 * this->pitch() / 180 * M_PI) * VELOCITY_CHANGE_COEFFICIENT / 10;
    if(pitch() > 90 or pitch() < -90)
        vertical_velocity_delta *= -1;
    vertical_velocity_delta = vertical_velocity_delta * (1 - velocity_vertical() / (SPEED_UPPER_BOUND / 10));
    this->setVelocity_vertical(velocity_vertical() + vertical_velocity_delta);

    if(altitude() < 3000 and altitude() > 0)
        this->setAltitude(this->altitude() + velocity_vertical());
    else
        this->setAltitude(this->altitude() - velocity_vertical());

    this->setTime(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));

    QGeoCoordinate old_coords = { latitude(), longitude() };
    QGeoCoordinate new_coords = old_coords.atDistanceAndAzimuth(velocity_horizontal() * UPDATE_INTERVAL_MS / 1'000, course());
    this->setLatitude(new_coords.latitude());
    this->setLongitude(new_coords.longitude());
}

double TelemetryEmulator::latitude() const { return m_latitude; }
void TelemetryEmulator::setLatitude(double other) {
    if (qFuzzyCompare(m_latitude, other)) return;
    m_latitude = other;
    emit latitudeChanged();
}

double TelemetryEmulator::longitude() const { return m_longitude; }
void TelemetryEmulator::setLongitude(double other) {
    if (qFuzzyCompare(m_longitude, other)) return;
    m_longitude = other;
    emit longitudeChanged();
}

float TelemetryEmulator::altitude() const { return m_altitude; }
void TelemetryEmulator::setAltitude(float other) {
    if (qFuzzyCompare(m_altitude, other)) return;
    m_altitude = other;
    emit altitudeChanged();
}

float TelemetryEmulator::velocity_horizontal() const { return m_velocity_horizontal; }
void TelemetryEmulator::setVelocity_horizontal(float other) {
    if (qFuzzyCompare(m_velocity_horizontal, other)) return;
    m_velocity_horizontal = other;
    emit velocity_horizontalChanged();
}

float TelemetryEmulator::velocity_vertical() const { return m_velocity_vertical; }
void TelemetryEmulator::setVelocity_vertical(float other) {
    if (qFuzzyCompare(m_velocity_vertical, other)) return;
    m_velocity_vertical = other;
    emit velocity_verticalChanged();
}

float TelemetryEmulator::pitch() const { return m_pitch; }
void TelemetryEmulator::setPitch(float other) {
    if (qFuzzyCompare(m_pitch, other)) return;
    if(other >= 360) other -= 360;
    if(other <= -360) other += 360;
    m_pitch = other;
    emit pitchChanged();
}

float TelemetryEmulator::roll() const { return m_roll; }
void TelemetryEmulator::setRoll(float other) {
    if (qFuzzyCompare(m_roll, other)) return;
    if(other >= 360) other -= 360;
    if(other <= -360) other += 360;
    m_roll = other;
    emit rollChanged();
}

float TelemetryEmulator::course() const { return m_course; }
void TelemetryEmulator::setCourse(float other) {
    if (qFuzzyCompare(m_course, other)) return;
    if(other >= 360) other -= 360;
    if(other <= -360) other += 360;
    m_course = other;
    emit courseChanged();
}

QString TelemetryEmulator::time() const { return m_time; }
void TelemetryEmulator::setTime(const QString& other) {
    if (m_time == other) return;
    m_time = other;
    emit timeChanged();
}

bool TelemetryEmulator::inFlight() const { return m_inFlight; }
void TelemetryEmulator::setInFlight(bool other) {
    if (m_inFlight == other) return;
    m_inFlight = other;
    emit inFlightChanged();
}
