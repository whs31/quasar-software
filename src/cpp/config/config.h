#pragma once

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <LPVL/Global>

#define CONFIG(x) Config::Config::get()->x()

class QSettings;

namespace Config
{
    class Config : public QObject
    {
        Q_OBJECT
        LPVL_DECLARE_SINGLETON(Config)

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

            Q_INVOKABLE void sync();
            Q_INVOKABLE void save();
            Q_INVOKABLE void load();
            Q_INVOKABLE void revert();
            Q_INVOKABLE void reset();
            Q_INVOKABLE QString projectVersion();

            QString remoteIP() const; void setRemoteIP(const QString&);
            QString localIP() const; void setLocalIP(const QString&);
            QString telemetryPort() const; void setTelemetryPort(const QString&);
            QString tcpLFSPort() const; void setTcpLFSPort(const QString&);
            QString udpLFSPort() const; void setUdpLFSPort(const QString&);
            QString execdPort() const; void setExecdPort(const QString&);
            QString feedbackPort() const; void setFeedbackPort(const QString&);
            bool proxyEnabled() const; void setProxyEnabled(bool);
            bool antennaAlignment() const; void setAntennaAlignment(bool);
            float angleCorrection() const; void setAngleCorrection(float);
            bool useRadians() const; void setUseRadians(bool);
            bool useDriftAngle() const; void setUseDriftAngle(bool);
            float thetaAzimuthCorrection() const; void setThetaAzimuthCorrection(float);
            double storedLatitude() const; void setStoredLatitude(double);
            double storedLongitude() const; void setStoredLongitude(double);
            double storedZoomLevel() const; void setStoredZoomLevel(double);
            QString storedCatalogue() const; void setStoredCatalogue(const QString&);
            float telemetryFrequency() const; void setTelemetryFrequency(float);
            bool overrideImageHeight() const; void setOverrideImageHeight(bool);
            bool cutImage() const; void setCutImage(bool);

            signals:
                void remoteIPChanged();
                void localIPChanged();
                void telemetryPortChanged();
                void tcpLFSPortChanged();
                void udpLFSPortChanged();
                void execdPortChanged();
                void feedbackPortChanged();
                void proxyEnabledChanged();
                void antennaAlignmentChanged();
                void angleCorrectionChanged();
                void useRadiansChanged();
                void useDriftAngleChanged();
                void thetaAzimuthCorrectionChanged();
                void storedLatitudeChanged();
                void storedLongitudeChanged();
                void storedZoomLevelChanged();
                void storedCatalogueChanged();
                void telemetryFrequencyChanged();
                void overrideImageHeightChanged();
                void cutImageChanged();

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
