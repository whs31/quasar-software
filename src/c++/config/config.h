#pragma once

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QVariant>

//! @macro Useful macro for accessing config value from
//!        property name.
#define CONFIG(x) Config::Config::get()->x()

class QSettings;

//! @namespace Namespace for working with data,
//!            which is shared between sessions.
namespace Config
{
    //! @class Class for working with local application
    //!        settings, stored in filesystem.
    class Config : public QObject
    {
        Q_OBJECT

        //! @defgroup Network settings
        //! @{
        //! @var IPv4-address of SAR (DE10-NANO).
        Q_PROPERTY(QString remoteIP READ remoteIP WRITE setRemoteIP NOTIFY remoteIPChanged)
        //! @var IPv4-address of host computer.
        Q_PROPERTY(QString localIP READ localIP WRITE setLocalIP NOTIFY localIPChanged)
        //! @var IPv4-address of Jetson block.
        Q_PROPERTY(QString jetsonIP READ jetsonIP WRITE setJetsonIP NOTIFY jetsonIPChanged)
        //! @var IPv4-address of NavSAR.
        Q_PROPERTY(QString navIP READ navIP WRITE setNavIP NOTIFY navIPChanged)
        //! @var IPv4-address (reserved for commutator).
        Q_PROPERTY(QString utl1IP READ utl1IP WRITE setUtl1IP NOTIFY utl1IPChanged)
        //! @var IPv4-address (reserved for commutator).
        Q_PROPERTY(QString utl2IP READ utl2IP WRITE setUtl2IP NOTIFY utl2IPChanged)
        //! @var Port for telemetry request.
        Q_PROPERTY(QString telemetryPort READ telemetryPort WRITE setTelemetryPort NOTIFY telemetryPortChanged)
        //! @var Port for telemetry feedback.
        Q_PROPERTY(QString telemetryRecvPort READ telemetryRecvPort WRITE setTelemetryRecvPort NOTIFY telemetryRecvPortChanged)
        //! @var Port for fsend TCP-IP service.
        Q_PROPERTY(QString tcpLFSPort READ tcpLFSPort WRITE setTcpLFSPort NOTIFY tcpLFSPortChanged)
        //! @var Port for fsend UDP service.
        Q_PROPERTY(QString udpLFSPort READ udpLFSPort WRITE setUdpLFSPort NOTIFY udpLFSPortChanged)
        //! @var Port for execd service requests.
        Q_PROPERTY(QString execdPort READ execdPort WRITE setExecdPort NOTIFY execdPortChanged)
        //! @var Port for execd service feedback.
        Q_PROPERTY(QString feedbackPort READ feedbackPort WRITE setFeedbackPort NOTIFY feedbackPortChanged)
        //! @var Telemetry receivement interval in seconds.
        Q_PROPERTY(float telemetryFrequency READ telemetryFrequency WRITE setTelemetryFrequency NOTIFY telemetryFrequencyChanged)
        //! @var Legacy setting for proxy --remote flag.
        Q_PROPERTY(bool proxyEnabled READ proxyEnabled WRITE setProxyEnabled NOTIFY proxyEnabledChanged)
        //! @var Fsend TCP-IP split marker. Can be '\0' or '\n'.
        Q_PROPERTY(QString tcpMarker READ tcpMarker WRITE setTcpMarker NOTIFY tcpMarkerChanged)
        //! @}

        //! @defgroup UAV settings
        //! @{
        //! @var Antenna alignment. True means antenna aligned to right.
        Q_PROPERTY(bool antennaAlignment READ antennaAlignment WRITE setAntennaAlignment NOTIFY antennaAlignmentChanged)

        //! @var Value, added to azimuth in SAR image metadata in degrees.
        Q_PROPERTY(float angleCorrection READ angleCorrection WRITE setAngleCorrection NOTIFY angleCorrectionChanged)
        //! @var Flag for expecting using radians in SAR image metadata.
        Q_PROPERTY(bool useRadians READ useRadians WRITE setUseRadians NOTIFY useRadiansChanged)
        //! @var Flag for expecting using drift angle value in SAR image metadata.
        Q_PROPERTY(bool useDriftAngle READ useDriftAngle WRITE setUseDriftAngle NOTIFY useDriftAngleChanged)
        //! @var Value, subtracted from thetha-azimuth in SAR image metadata (degrees).
        Q_PROPERTY(float thetaAzimuthCorrection READ thetaAzimuthCorrection WRITE setThetaAzimuthCorrection NOTIFY thetaAzimuthCorrectionChanged)
        //! @var Flag for overriding ly field in SAR image metadata. True means that received ly will be replaced with image pixel height.
        Q_PROPERTY(bool overrideImageHeight READ overrideImageHeight WRITE setOverrideImageHeight NOTIFY overrideImageHeightChanged)
        //! @var Flag for enabling software cutting telescopic images.
        Q_PROPERTY(bool cutImage READ cutImage WRITE setCutImage NOTIFY cutImageChanged)
        //! @}

        //! @defgroup Previous session settings
        //! @{
        //! @var Previous session camera latitude.
        Q_PROPERTY(double storedLatitude READ storedLatitude WRITE setStoredLatitude NOTIFY storedLatitudeChanged)
        //! @var Previous session camera longitude.
        Q_PROPERTY(double storedLongitude READ storedLongitude WRITE setStoredLongitude NOTIFY storedLongitudeChanged)
        //! @var Previous session camera zoom level.
        Q_PROPERTY(double storedZoomLevel READ storedZoomLevel WRITE setStoredZoomLevel NOTIFY storedZoomLevelChanged)
        //! @var Previous session image folder.
        Q_PROPERTY(QString storedCatalogue READ storedCatalogue WRITE setStoredCatalogue NOTIFY storedCatalogueChanged)
        //! @}

        //! @defgroup Application settings
        //! @{
        //! @var Current selected theme.
        Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
        //! @}

        public:
            //! @brief Returns singleton instance of class.
            static Config* get() { static Config instance; return &instance; }
            virtual ~Config();

            //! @brief Syncs settings from RAM to .ini file on disk.
            //! @sa Internal function. Do not call if you are not exactly knowing
            //!     what you want to achieve.
            Q_INVOKABLE void sync();

            //! @brief Saves settings from RAM to .ini file on disk.
            Q_INVOKABLE void save();

            //! @brief Discards all current settings and loads stored settings
            //!        from .ini file on disk.
            Q_INVOKABLE void load();

            //! @brief Alias for load().
            Q_INVOKABLE void revert();

            //! @brief Discards current settings, .ini file and loads default settings.
            Q_INVOKABLE void reset();

            //! @brief Returns application version.
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
            Config(const Config &);
            Config &operator=(const Config &);

        private:
            //! @var Default settings for fresh application build.
            const QMap<QString, QVariant> defaults = {
                {"remoteIP", "127.0.0.1"},
                {"jetsonIP", "192.168.1.48"},
                {"navIP", "192.168.1.49"},
                {"utl1IP", "192.168.1.50"},
                {"utl2IP", "192.168.1.51"},
                {"localIP", "127.0.0.1"},
                {"telemetryPort", "9955"},
                {"telemetryRecvPort", "10337"},
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
