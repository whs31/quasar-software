#pragma once

#include <QtCore/QMetaType>
#include <QtCore/QString>

namespace Config
{
    struct network_t
    {
        QString remoteIP = "-";
        QString localIP = "-";
        QString telemetryPort = "-";
        QString lfsPort = "-";
        QString execdPort = "-";
        QString feedbackPort = "-";
        float telemetryFrequency = -1;
        bool useProxy = false;
    };

    struct map_t
    {
        double storedLatitude = -1;
        double storedLongitude = -1;
        float storedZoomLevel = -1;
        bool antennaPosition = false;
    };

    struct image_t
    {
        float angleCorrection = -1;
        bool useRadians = false;
        bool useDriftAngle = false;
        float thetaAzimuthCorrection = -1;
        QString storedCatalogue = "-";
    };
} // namespace Config;

Q_DECLARE_METATYPE(Config::network_t);
Q_DECLARE_METATYPE(Config::map_t);
Q_DECLARE_METATYPE(Config::image_t);
