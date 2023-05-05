#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtQml/QQmlPropertyMap>

//! @brief Useful macro for accessing config from c++
#define CONFIG Config::Config::get()->map()->value

class QSettings;

namespace Config
{
    class Config : public QObject
    {
        Q_OBJECT

        const QMap<QString, QVariant> defaults = {
            {"remoteIP", "127.0.0.1"},
            {"localIP", "127.0.0.1"},
            {"telemetryPort", "9955"},
            {"lfsPort", "10000"},
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
            {"useRadians", "false"},
            {"useDriftAngle", "true"},
            {"thetaAzimuthCorrection", "5"}
        };

        public:
            static Config* get(QObject* parent = nullptr);
            virtual ~Config() = default;

            __qml QQmlPropertyMap* map();

            void sync();
            void save();
            void load();
            void revert();
            void reset();

        private:
            explicit Config(QObject* parent = nullptr);

        private:
            static Config* instance;
            QQmlPropertyMap m_values;
            QSettings* ini;
    };
} // namespace Config;
