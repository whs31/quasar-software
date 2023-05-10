#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#define CONFIG(x) Config::Config::get()->x()

class QSettings;

namespace Config
{
    class Config : public QObject
    {
        Q_OBJECT
        DECLARE_SINGLETON(Config)

        Q_PROPERTY(QString remoteIP READ remoteIP WRITE setRemoteIP NOTIFY remoteIPChanged)
        Q_PROPERTY(QString localIP READ localIP WRITE setLocalIP NOTIFY localIPChanged)
        Q_PROPERTY(QString telemetryPort READ telemetryPort WRITE setTelemetryPort NOTIFY telemetryPortChanged)
        Q_PROPERTY(QString tcpLFSPort READ tcpLFSPort WRITE setTcpLFSPort NOTIFY tcpLFSPortChanged)
        Q_PROPERTY(QString udpLFSPort READ udpLFSPort WRITE setUdpLFSPort NOTIFY udpLFSPortChanged)
        Q_PROPERTY(QString execdPort READ execdPort WRITE setExecdPort NOTIFY execdPortChanged)
        Q_PROPERTY(QString feedbackPort READ feedbackPort WRITE setFeedbackPort NOTIFY feedbackPortChanged)
        Q_PROPERTY(float telemetryFrequency READ telemetryFrequency WRITE setTelemetryFrequency NOTIFY telemetryFrequencyChanged)
        Q_PROPERTY(bool proxyEnabled READ proxyEnabled WRITE setProxyEnabled NOTIFY proxyEnabledChanged)

        Q_PROPERTY(bool antennaAlignment READ antennaAlignment WRITE setAntennaAlignment NOTIFY antennaAlignmentChanged)

        Q_PROPERTY(float angleCorrection READ angleCorrection WRITE setAngleCorrection NOTIFY angleCorrectionChanged)
        Q_PROPERTY(bool useRadians READ useRadians WRITE setUseRadians NOTIFY useRadiansChanged)
        Q_PROPERTY(bool useDriftAngle READ useDriftAngle WRITE setUseDriftAngle NOTIFY useDriftAngleChanged)
        Q_PROPERTY(float thetaAzimuthCorrection READ thetaAzimuthCorrection WRITE setThetaAzimuthCorrection NOTIFY thetaAzimuthCorrectionChanged)
        Q_PROPERTY(bool overrideImageHeight READ overrideImageHeight WRITE setOverrideImageHeight NOTIFY overrideImageHeightChanged)
        Q_PROPERTY(bool cutImage READ cutImage WRITE setCutImage NOTIFY cutImageChanged)

        Q_PROPERTY(double storedLatitude READ storedLatitude WRITE setStoredLatitude NOTIFY storedLatitudeChanged)
        Q_PROPERTY(double storedLongitude READ storedLongitude WRITE setStoredLongitude NOTIFY storedLongitudeChanged)
        Q_PROPERTY(double storedZoomLevel READ storedZoomLevel WRITE setStoredZoomLevel NOTIFY storedZoomLevelChanged)
        Q_PROPERTY(QString storedCatalogue READ storedCatalogue WRITE setStoredCatalogue NOTIFY storedCatalogueChanged)

        public:
            virtual ~Config();

            __exposed void sync();
            __exposed void save();
            __exposed void load();
            __exposed void revert();
            __exposed void reset();

            __getter QString remoteIP() const;
            __setter void setRemoteIP(const QString& other);

            __getter QString localIP() const;
            __setter void setLocalIP(const QString& other);

            __getter QString telemetryPort() const;
            __setter void setTelemetryPort(const QString& other);

            __getter QString tcpLFSPort() const;
            __setter void setTcpLFSPort(const QString& other);

            __getter QString udpLFSPort() const;
            __setter void setUdpLFSPort(const QString& other);

            __getter QString execdPort() const;
            __setter void setExecdPort(const QString& other);

            __getter QString feedbackPort() const;
            __setter void setFeedbackPort(const QString& other);

            __getter bool proxyEnabled() const;
            __setter void setProxyEnabled(bool other);

            __getter bool antennaAlignment() const;
            __setter void setAntennaAlignment(bool other);

            __getter float angleCorrection() const;
            __setter void setAngleCorrection(float other);

            __getter bool useRadians() const;
            __setter void setUseRadians(bool other);

            __getter bool useDriftAngle() const;
            __setter void setUseDriftAngle(bool other);

            __getter float thetaAzimuthCorrection() const;
            __setter void setThetaAzimuthCorrection(float other);

            __getter double storedLatitude() const;
            __setter void setStoredLatitude(double other);

            __getter double storedLongitude() const;
            __setter void setStoredLongitude(double other);

            __getter double storedZoomLevel() const;
            __setter void setStoredZoomLevel(double other);

            __getter QString storedCatalogue() const;
            __setter void setStoredCatalogue(const QString& other);

            __getter float telemetryFrequency() const;
            __setter void setTelemetryFrequency(float other);

            __getter bool overrideImageHeight() const;
            __setter void setOverrideImageHeight(bool other);

            __getter bool cutImage() const;
            __setter void setCutImage(bool other);

            signals:
                __signal remoteIPChanged();
                __signal localIPChanged();
                __signal telemetryPortChanged();
                __signal tcpLFSPortChanged();
                __signal udpLFSPortChanged();
                __signal execdPortChanged();
                __signal feedbackPortChanged();
                __signal proxyEnabledChanged();
                __signal antennaAlignmentChanged();
                __signal angleCorrectionChanged();
                __signal useRadiansChanged();
                __signal useDriftAngleChanged();
                __signal thetaAzimuthCorrectionChanged();
                __signal storedLatitudeChanged();
                __signal storedLongitudeChanged();
                __signal storedZoomLevelChanged();
                __signal storedCatalogueChanged();
                __signal telemetryFrequencyChanged();
                __signal overrideImageHeightChanged();
                __signal cutImageChanged();

            private:
            explicit Config(QObject* parent = nullptr);

        private:
            const QMap<QString, QVariant> defaults = {
                {"remoteIP", "127.0.0.1"},
                {"localIP", "127.0.0.1"},
                {"telemetryPort", "9955"},
                {"lfsPort", "10000"},
                {"stripPort", "48455"},
                {"execdPort", "9845"},
                {"feedbackPort", "9846"},
                {"telemetryFrequency", "0.1"},
                {"proxyEnabled", "false"},
                {"storedLatitude", "60"},
                {"storedLongitude", "30"},
                {"storedZoomLevel", "6"},
                {"storedCatalogue", "C:/"},
                {"antennaAlignment", "false"},
                {"angleCorrection", "0"},
                {"useRadians", "true"},
                {"useDriftAngle", "true"},
                {"thetaAzimuthCorrection", "5"},
                {"overrideImageHeight", "true"},
                {"cutImage", "true"}
            };

            QSettings* ini;

            QString m_remoteIP;
            QString m_localIP;
            QString m_telemetryPort;
            QString m_tcpLFSPort;
            QString m_udpLFSPort;
            QString m_execdPort;
            QString m_feedbackPort;
            bool m_proxyEnabled;
            bool m_antennaAlignment;
            float m_angleCorrection;
            bool m_useRadians;
            bool m_useDriftAngle;
            float m_thetaAzimuthCorrection;
            double m_storedLatitude;
            double m_storedLongitude;
            double m_storedZoomLevel;
            QString m_storedCatalogue;
            float m_telemetryFrequency;
            bool m_overrideImageHeight;
            bool m_cutImage;
    };
} // namespace Config;
