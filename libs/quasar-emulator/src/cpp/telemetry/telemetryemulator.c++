#include "telemetryemulator.h++"
#include <QtCore/QTimer>
#include <QtCore/QDateTime>

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
    this->setVelocity_horizontal(start_velocity);
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

void TelemetryEmulator::update()
{
//    this->setLatitude(0);
//    this->setLongitude(0);
//    this->setAltitude(0);
//    this->setVelocity_horizontal(0);
//    this->setVelocity_vertical(0);
    this->setTime(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
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
    m_pitch = other;
    emit pitchChanged();
}

float TelemetryEmulator::roll() const { return m_roll; }
void TelemetryEmulator::setRoll(float other) {
    if (qFuzzyCompare(m_roll, other)) return;
    if(other >= 360) other -= 360;
    m_roll = other;
    emit rollChanged();
}

float TelemetryEmulator::course() const { return m_course; }
void TelemetryEmulator::setCourse(float other) {
    if (qFuzzyCompare(m_course, other)) return;
    if(other >= 360) other -= 360;
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
