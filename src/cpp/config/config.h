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
        Q_PROPERTY(QString jetsonIP READ jetsonIP WRITE setJetsonIP NOTIFY jetsonIPChanged)
        Q_PROPERTY(QString navIP READ navIP WRITE setNavIP NOTIFY navIPChanged)
        Q_PROPERTY(QString utl1IP READ utl1IP WRITE setUtl1IP NOTIFY utl1IPChanged)
        Q_PROPERTY(QString utl2IP READ utl2IP WRITE setUtl2IP NOTIFY utl2IPChanged)
        Q_PROPERTY(QString telemetryPort READ telemetryPort WRITE setTelemetryPort NOTIFY telemetryPortChanged)
        Q_PROPERTY(QString telemetryRecvPort READ telemetryRecvPort WRITE setTelemetryRecvPort NOTIFY telemetryRecvPortChanged)
        Q_PROPERTY(QString tcpLFSPort READ tcpLFSPort WRITE setTcpLFSPort NOTIFY tcpLFSPortChanged)
        Q_PROPERTY(QString udpLFSPort READ udpLFSPort WRITE setUdpLFSPort NOTIFY udpLFSPortChanged)
        Q_PROPERTY(QString execdPort READ execdPort WRITE setExecdPort NOTIFY execdPortChanged)
        Q_PROPERTY(QString feedbackPort READ feedbackPort WRITE setFeedbackPort NOTIFY feedbackPortChanged)
        Q_PROPERTY(float telemetryFrequency READ telemetryFrequency WRITE setTelemetryFrequency NOTIFY telemetryFrequencyChanged)
        Q_PROPERTY(bool proxyEnabled READ proxyEnabled WRITE setProxyEnabled NOTIFY proxyEnabledChanged)
        Q_PROPERTY(QString tcpMarker READ tcpMarker WRITE setTcpMarker NOTIFY tcpMarkerChanged)

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

        Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)

        public:
            virtual ~Config();

            Q_INVOKABLE void sync();
            Q_INVOKABLE void save();
            Q_INVOKABLE void load();
            Q_INVOKABLE void revert();
            Q_INVOKABLE void reset();
            Q_INVOKABLE QString projectVersion();

            [[nodiscard]] QString remoteIP() const; void setRemoteIP(const QString&);
            [[nodiscard]] QString localIP() const; void setLocalIP(const QString&);
            [[nodiscard]] QString telemetryPort() const; void setTelemetryPort(const QString&);
            [[nodiscard]] QString tcpLFSPort() const; void setTcpLFSPort(const QString&);
            [[nodiscard]] QString udpLFSPort() const; void setUdpLFSPort(const QString&);
            [[nodiscard]] QString execdPort() const; void setExecdPort(const QString&);
            [[nodiscard]] QString feedbackPort() const; void setFeedbackPort(const QString&);
            [[nodiscard]] bool proxyEnabled() const; void setProxyEnabled(bool);
            [[nodiscard]] bool antennaAlignment() const; void setAntennaAlignment(bool);
            [[nodiscard]] float angleCorrection() const; void setAngleCorrection(float);
            [[nodiscard]] bool useRadians() const; void setUseRadians(bool);
            [[nodiscard]] bool useDriftAngle() const; void setUseDriftAngle(bool);
            [[nodiscard]] float thetaAzimuthCorrection() const; void setThetaAzimuthCorrection(float);
            [[nodiscard]] double storedLatitude() const; void setStoredLatitude(double);
            [[nodiscard]] double storedLongitude() const; void setStoredLongitude(double);
            [[nodiscard]] double storedZoomLevel() const; void setStoredZoomLevel(double);
            [[nodiscard]] QString storedCatalogue() const; void setStoredCatalogue(const QString&);
            [[nodiscard]] float telemetryFrequency() const; void setTelemetryFrequency(float);
            [[nodiscard]] bool overrideImageHeight() const; void setOverrideImageHeight(bool);
            [[nodiscard]] bool cutImage() const; void setCutImage(bool);
            [[nodiscard]] QString tcpMarker() const; void setTcpMarker(const QString&);
            [[nodiscard]] QString theme() const; void setTheme(const QString&);
            [[nodiscard]] QString jetsonIP() const; void setJetsonIP(const QString&);
            [[nodiscard]] QString navIP() const; void setNavIP(const QString&);
            [[nodiscard]] QString utl1IP() const; void setUtl1IP(const QString&);
            [[nodiscard]] QString utl2IP() const; void setUtl2IP(const QString&);
            [[nodiscard]] QString telemetryRecvPort() const; void setTelemetryRecvPort(const QString&);

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
                void tcpMarkerChanged();
                void themeChanged();
                void scheduleRestart();
                void jetsonIPChanged();
                void navIPChanged();
                void utl1IPChanged();
                void utl2IPChanged();
                void telemetryRecvPortChanged();

        private:
            explicit Config(QObject* parent = nullptr);

        private:
            const QMap<QString, QVariant> defaults = {
                {"remoteIP", "127.0.0.1"},
                {"jetsonIP", "192.168.1.48"},
                {"navIP", "192.168.1.49"},
                {"utl1IP", "192.168.1.50"},
                {"utl2IP", "192.168.1.51"},
                {"localIP", "127.0.0.1"},
                {"telemetryPort", "9955"},
                {"telemetryRecvPort", 10337},
                {"lfsPort", "10000"},
                {"stripPort", "48455"},
                {"execdPort", "9845"},
                {"feedbackPort", "9846"},
                {"telemetryFrequency", "0.1"},
                {"proxyEnabled", "false"},
                {"tcpMarker", "\0"},
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
                {"cutImage", "true"},
                {"theme", "contrast"}
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
            QString m_tcpMarker;
            QString m_theme;
            QString m_jetsonIP;
            QString m_navIP;
            QString m_utl1IP;
            QString m_utl2IP;
            QString m_telemetryRecvPort;
    };
} // namespace Config;
