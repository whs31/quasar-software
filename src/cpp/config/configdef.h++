#pragma once

#include <QtCore/QMetaType>
#include <QtCore/QString>

namespace Config
{
    struct network_t
    {
        QString remoteIP;
        QString localIP;
        QString telemetryPort;
        QString lfsPort;
        QString execdPort;
        QString feedbackPort;
        float telemetryFrequency;
        bool useProxy;
    };

    struct map_t
    {
        double storedLatitude;
        double storedLongitude;
        float storedZoomLevel;
        bool antennaPosition;
    };

    struct image_t
    {
        float angleCorrection;
        bool useRadians;
        bool useDriftAngle;
        float thetaAzimuthCorrection;
        QString storedCatalogue;
    };
} // namespace Config;

Q_DECLARE_METATYPE(Config::network_t);
Q_DECLARE_METATYPE(Config::map_t);
Q_DECLARE_METATYPE(Config::image_t);
