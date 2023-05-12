#include "config.h++"
#include "paths.h++"

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
