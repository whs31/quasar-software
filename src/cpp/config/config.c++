#include "config.h"
#include "paths.h"

#include <QtCore/QSettings>
#include <QtCore/QDebug>

#define QSTRING_CAST(x) QVariant(x).toString()

Config::Config::~Config()
{
    this->save();
    this->sync();
}

void Config::Config::save()
{
    qInfo() << "[CONFIG] Saving settings to file";

    ini->setValue("remoteIP", remoteIP());
    ini->setValue("localIP", localIP());
    ini->setValue("telemetryPort", telemetryPort());
    ini->setValue("lfsPort", tcpLFSPort());
    ini->setValue("stripPort", udpLFSPort());
    ini->setValue("execdPort", execdPort());
    ini->setValue("feedbackPort", feedbackPort());
    ini->setValue("telemetryFrequency", QSTRING_CAST(telemetryFrequency()));
    ini->setValue("proxyEnabled", QSTRING_CAST(proxyEnabled()));
    ini->setValue("tcpMarker", tcpMarker());
    ini->setValue("storedLatitude", QSTRING_CAST(storedLatitude()));
    ini->setValue("storedLongitude", QSTRING_CAST(storedLongitude()));
    ini->setValue("storedZoomLevel", QSTRING_CAST(storedZoomLevel()));
    ini->setValue("storedCatalogue", storedCatalogue());
    ini->setValue("antennaAlignment", QSTRING_CAST(antennaAlignment()));
    ini->setValue("angleCorrection", QSTRING_CAST(angleCorrection()));
    ini->setValue("useRadians", QSTRING_CAST(useRadians()));
    ini->setValue("useDriftAngle", QSTRING_CAST(useDriftAngle()));
    ini->setValue("thetaAzimuthCorrection", QSTRING_CAST(thetaAzimuthCorrection()));
    ini->setValue("overrideImageHeight", QSTRING_CAST(overrideImageHeight()));
    ini->setValue("cutImage", QSTRING_CAST(cutImage()));
    ini->setValue("theme", theme());
}

void Config::Config::load()
{
    qInfo() << "[CONFIG] Loading settings from file";

    setRemoteIP(ini->value("remoteIP").toString());
    setLocalIP(ini->value("localIP").toString());
    setTelemetryPort(ini->value("telemetryPort").toString());
    setTcpLFSPort(ini->value("lfsPort").toString());
    setUdpLFSPort(ini->value("stripPort").toString());
    setExecdPort(ini->value("execdPort").toString());
    setFeedbackPort(ini->value("feedbackPort").toString());
    setTelemetryFrequency(ini->value("telemetryFrequency").toFloat());
    setProxyEnabled(ini->value("proxyEnabled").toBool());
    setTcpMarker(ini->value("tcpMarker").toString());
    setStoredLatitude(ini->value("storedLatitude").toDouble());
    setStoredLongitude(ini->value("storedLongitude").toDouble());
    setStoredZoomLevel(ini->value("storedZoomLevel").toDouble());
    setStoredCatalogue(ini->value("storedCatalogue").toString());
    setAntennaAlignment(ini->value("antennaAlignment").toBool());
    setAngleCorrection(ini->value("angleCorrection").toFloat());
    setUseRadians(ini->value("useRadians").toBool());
    setUseDriftAngle(ini->value("useDriftAngle").toBool());
    setThetaAzimuthCorrection(ini->value("thetaAzimuthCorrection").toFloat());
    setOverrideImageHeight(ini->value("overrideImageHeight").toBool());
    setCutImage(ini->value("cutImage").toBool());
    setTheme(ini->value("theme").toString());
}

void Config::Config::revert()
{
    this->load();
}

void Config::Config::reset()
{
    qWarning() << "[CONFIG] Settings file resetted";

    for(const auto &key : defaults.keys())
        ini->setValue(key, defaults.value(key));
}

QString Config::Config::projectVersion()
{
    return PROJECT_VERSION;
}

void Config::Config::sync()
{
    ini->sync();
}

Config::Config::Config(QObject* parent)
    : QObject{parent}
    , ini(new QSettings(Paths::config() + "/config.ini", QSettings::IniFormat, this))
{
    qDebug().noquote() << "[CONFIG] Storing config in" << ini->fileName();

    if(ini->allKeys().size() < 5)
        this->reset();

    this->load();
}

namespace Config {
bool Config::overrideImageHeight() const { return m_overrideImageHeight; }
void Config::setOverrideImageHeight(bool other)
{
    if (m_overrideImageHeight == other)
        return;
    m_overrideImageHeight = other;
    emit overrideImageHeightChanged();
}

bool Config::cutImage() const { return m_cutImage; }
void Config::setCutImage(bool other)
{
    if (m_cutImage == other)
        return;
    m_cutImage = other;
    emit cutImageChanged();
}

QString Config::remoteIP() const
{
    return m_remoteIP;
}

void Config::setRemoteIP(const QString& other)
{
    if (m_remoteIP == other)
        return;
    m_remoteIP = other;
    emit remoteIPChanged();
}

QString Config::localIP() const
{
    return m_localIP;
}

void Config::setLocalIP(const QString& other)
{
    if (m_localIP == other)
        return;
    m_localIP = other;
    emit localIPChanged();
}

QString Config::telemetryPort() const
{
    return m_telemetryPort;
}

void Config::setTelemetryPort(const QString& other)
{
    if (m_telemetryPort == other)
        return;
    m_telemetryPort = other;
    emit telemetryPortChanged();
}

QString Config::tcpLFSPort() const
{
    return m_tcpLFSPort;
}

void Config::setTcpLFSPort(const QString& other)
{
    if (m_tcpLFSPort == other)
        return;
    m_tcpLFSPort = other;
    emit tcpLFSPortChanged();
}

QString Config::udpLFSPort() const
{
    return m_udpLFSPort;
}

void Config::setUdpLFSPort(const QString& other)
{
    if (m_udpLFSPort == other)
        return;
    m_udpLFSPort = other;
    emit udpLFSPortChanged();
}

QString Config::execdPort() const
{
    return m_execdPort;
}

void Config::setExecdPort(const QString& other)
{
    if (m_execdPort == other)
        return;
    m_execdPort = other;
    emit execdPortChanged();
}

QString Config::feedbackPort() const
{
    return m_feedbackPort;
}

void Config::setFeedbackPort(const QString& other)
{
    if (m_feedbackPort == other)
        return;
    m_feedbackPort = other;
    emit feedbackPortChanged();
}

bool Config::proxyEnabled() const
{
    return m_proxyEnabled;
}

void Config::setProxyEnabled(bool other)
{
    if (m_proxyEnabled == other)
        return;
    m_proxyEnabled = other;
    emit proxyEnabledChanged();
}

bool Config::antennaAlignment() const
{
    return m_antennaAlignment;
}

void Config::setAntennaAlignment(bool other)
{
    if (m_antennaAlignment == other)
        return;
    m_antennaAlignment = other;
    emit antennaAlignmentChanged();
}

float Config::angleCorrection() const
{
    return m_angleCorrection;
}

void Config::setAngleCorrection(float other)
{
    if (qFuzzyCompare(m_angleCorrection, other))
        return;
    m_angleCorrection = other;
    emit angleCorrectionChanged();
}

bool Config::useRadians() const
{
    return m_useRadians;
}

void Config::setUseRadians(bool other)
{
    if (m_useRadians == other)
        return;
    m_useRadians = other;
    emit useRadiansChanged();
}

bool Config::useDriftAngle() const
{
    return m_useDriftAngle;
}

void Config::setUseDriftAngle(bool other)
{
    if (m_useDriftAngle == other)
        return;
    m_useDriftAngle = other;
    emit useDriftAngleChanged();
}

float Config::thetaAzimuthCorrection() const
{
    return m_thetaAzimuthCorrection;
}

void Config::setThetaAzimuthCorrection(float other)
{
    if (qFuzzyCompare(m_thetaAzimuthCorrection, other))
        return;
    m_thetaAzimuthCorrection = other;
    emit thetaAzimuthCorrectionChanged();
}

double Config::storedLatitude() const
{
    return m_storedLatitude;
}

void Config::setStoredLatitude(double other)
{
    if (qFuzzyCompare(m_storedLatitude, other))
        return;
    m_storedLatitude = other;
    emit storedLatitudeChanged();
}

double Config::storedLongitude() const
{
    return m_storedLongitude;
}

void Config::setStoredLongitude(double other)
{
    if (qFuzzyCompare(m_storedLongitude, other))
        return;
    m_storedLongitude = other;
    emit storedLongitudeChanged();
}

double Config::storedZoomLevel() const
{
    return m_storedZoomLevel;
}

void Config::setStoredZoomLevel(double other)
{
    if (qFuzzyCompare(m_storedZoomLevel, other))
        return;
    m_storedZoomLevel = other;
    emit storedZoomLevelChanged();
}

QString Config::storedCatalogue() const
{
    return m_storedCatalogue;
}

void Config::setStoredCatalogue(const QString& other)
{
    if (m_storedCatalogue == other)
        return;
    if(other.startsWith("file:///"))
    {
        m_storedCatalogue = other.right(other.size() - strlen("file:///"));
#if !defined Q_OS_WINDOWS
        m_storedCatalogue.prepend('/');
#endif
    }
    else
        m_storedCatalogue = other;
    emit storedCatalogueChanged();
}

float Config::telemetryFrequency() const
{
    return m_telemetryFrequency;
}

void Config::setTelemetryFrequency(float other)
{
    if (qFuzzyCompare(m_telemetryFrequency, other))
        return;
    m_telemetryFrequency = other;
    emit telemetryFrequencyChanged();
}

QString Config::tcpMarker() const
{
    return m_tcpMarker;
}

void Config::setTcpMarker(const QString& other)
{
    if (m_tcpMarker == other)
        return;
    m_tcpMarker = other;
    emit tcpMarkerChanged();
}

QString Config::theme() const
{
    return m_theme;
}

void Config::setTheme(const QString& other)
{
    if (m_theme == other)
        return;
    m_theme = other;
    emit themeChanged();
}

}
