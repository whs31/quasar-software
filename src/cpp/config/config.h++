#pragma once

#include <definitions.h++>
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtQml/QQmlPropertyMap>

class QSettings;

namespace Config
{
    class Config : public QObject
    {
        Q_OBJECT

        static Config* instance;
        const QMap<QString, QVariant> defaults = {
            {"remoteIP", "127.0.0.1"},
            {"localIP", "127.0.0.1"},
            {"telemetryPort", "9955"},
            {"lfsPort", "10000"},
            {"execdPort", "9845"},
            {"feedbackPort", "9846"},
            {"telemetryFrequency", "1.1"},
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
        QQmlPropertyMap m_values;
        QSettings* ini;

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
    };
} // namespace Config;
