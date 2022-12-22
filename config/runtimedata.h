#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <QObject>
#include <qqml.h>
#include "sconfig.h"

class RuntimeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal latitude READ getLatitude WRITE setLatitude);
    Q_PROPERTY(qreal longitude READ getLongitude WRITE setLongitude);
    Q_PROPERTY(qreal elevation READ getElevation WRITE setElevation);
    Q_PROPERTY(qreal speed READ getSpeed WRITE setSpeed);
    Q_PROPERTY(qint16 satellites READ getSatellites WRITE setSatellites);

    Q_PROPERTY(bool followPlane READ getFollowPlane WRITE setFollowPlane);
    Q_PROPERTY(bool drawTooltip READ getDrawTooltip WRITE setDrawTooltip);
    Q_PROPERTY(bool drawRoute READ getDrawRoute WRITE setDrawRoute);
    Q_PROPERTY(bool drawPredict READ getDrawPredict WRITE setDrawPredict);
    Q_PROPERTY(bool drawDiagram READ getDrawDiagram WRITE setDrawDiagram);

    Q_PROPERTY(bool global_useOSMMaps READ getGlobal_useOSMMaps);
    Q_PROPERTY(qreal global_velocityVectorLength READ getGlobal_velocityVectorLength);
    QML_ELEMENT
    
public:
    static RuntimeData* initialize(QObject* parent = nullptr);
    static qreal getLatitude();
    static qreal getLongitude();
    static qreal getElevation();
    static qreal getSpeed();
    static qint16 getSatellites();

    static bool getFollowPlane();
    static bool getDrawTooltip();
    static bool getDrawRoute();
    static bool getDrawPredict();
    static bool getDrawDiagram();

    static bool getGlobal_useOSMMaps();
    static qreal getGlobal_velocityVectorLength();


    static void setLatitude(qreal value);
    static void setLongitude(qreal value);
    static void setElevation(qreal value);
    static void setSpeed(qreal value);
    static void setSatellites(qint16 value);

    static void setFollowPlane(bool state);
    static void setDrawTooltip(bool state);
    static void setDrawRoute(bool state);
    static void setDrawPredict(bool state);
    static void setDrawDiagram(bool state);

private:
    static RuntimeData* _instance;
    explicit RuntimeData(QObject *parent = nullptr);
    struct Telemetry 
    {
        qreal latitude = 0;
        qreal longitude = 0;
        qreal elevation = 0;
        qreal speed = 0;
        qreal direction = -1; //TODO: direction
        qint16 satellites = -1; 
    };
    static Telemetry telemetry;
    struct MapSettings
    {
        bool followPlane = false;
        bool drawTooltip = true;
        bool drawRoute = true;
        bool drawPredict = true;
        bool drawDiagram = true;
    };
    static MapSettings mapSettings;

signals:
    // static void latitudeChanged();
    // static void longitudeChanged();
    // static void elevationChanged();
    // static void speedChanged();
    // static void satellitesChanged();
};

#endif // RUNTIMEDATA_H
