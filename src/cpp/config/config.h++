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
        DEFINE_AS_SINGLETON(Config)

        PROPERTY_DEF(QString, remoteIP, setRemoteIP, m_remoteIP)
        PROPERTY_DEF(QString, localIP, setLocalIP, m_localIP)
        PROPERTY_DEF(QString, telemetryPort, setTelemetryPort, m_telemetryPort)
        PROPERTY_DEF(QString, tcpLFSPort, setTcpLFSPort, m_tcpLFSPort)
        PROPERTY_DEF(QString, udpLFSPort, setUdpLFSPort, m_udpLFSPort)
        PROPERTY_DEF(QString, execdPort, setExecdPort, m_execdPort)
        PROPERTY_DEF(QString, feedbackPort, setFeedbackPort, m_feedbackPort)
        PROPERTY_DEF(float, telemetryFrequency, setTelemetryFrequency, m_telemetryFrequency)
        PROPERTY_DEF(bool, proxyEnabled, setProxyEnabled, m_proxyEnabled)

        PROPERTY_DEF(bool, antennaAlignment, setAntennaAlignment, m_antennaAlignment)

        PROPERTY_DEF(float, angleCorrection, setAngleCorrection, m_angleCorrection)
        PROPERTY_DEF(bool, useRadians, setUseRadians, m_useRadians)
        PROPERTY_DEF(bool, useDriftAngle, setUseDriftAngle, m_useDriftAngle)
        PROPERTY_DEF(float, thetaAzimuthCorrection, setThetaAzimuthCorrection, m_thetaAzimuthCorrection)
        PROPERTY_DEF(bool, overrideImageHeight, setOverrideImageHeight, m_overrideImageHeight)
        PROPERTY_DEF(bool, cutImage, setCutImage, m_cutImage)

        PROPERTY_DEF(double, storedLatitude, setStoredLatitude, m_storedLatitude)
        PROPERTY_DEF(double, storedLongitude, setStoredLongitude, m_storedLongitude)
        PROPERTY_DEF(double, storedZoomLevel, setStoredZoomLevel, m_storedZoomLevel)
        PROPERTY_DEF(QString, storedCatalogue, setStoredCatalogue, m_storedCatalogue)

        public:
            virtual ~Config();

            __exposed void sync();
            __exposed void save();
            __exposed void load();
            __exposed void revert();
            __exposed void reset();

            signals:
                __property_signal remoteIPChanged();
                __property_signal localIPChanged();
                __property_signal telemetryPortChanged();
                __property_signal tcpLFSPortChanged();
                __property_signal udpLFSPortChanged();
                __property_signal execdPortChanged();
                __property_signal feedbackPortChanged();
                __property_signal proxyEnabledChanged();
                __property_signal antennaAlignmentChanged();
                __property_signal angleCorrectionChanged();
                __property_signal useRadiansChanged();
                __property_signal useDriftAngleChanged();
                __property_signal thetaAzimuthCorrectionChanged();
                __property_signal storedLatitudeChanged();
                __property_signal storedLongitudeChanged();
                __property_signal storedZoomLevelChanged();
                __property_signal storedCatalogueChanged();
                __property_signal telemetryFrequencyChanged();
                __property_signal overrideImageHeightChanged();
                __property_signal cutImageChanged();

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
