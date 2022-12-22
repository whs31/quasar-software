#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <QObject>
#include <qqml.h>
#include "sconfig.h"

class RuntimeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal latitude READ getLatitude WRITE setLatitude NOTIFY latitudeChanged);
    Q_PROPERTY(qreal longitude READ getLongitude WRITE setLongitude NOTIFY longitudeChanged);
    Q_PROPERTY(qreal elevation READ getElevation WRITE setElevation NOTIFY elevationChanged);
    Q_PROPERTY(qreal speed READ getSpeed WRITE setSpeed NOTIFY speedChanged);
    Q_PROPERTY(qint16 satellites READ getSatellites WRITE setSatellites NOTIFY satellitesChanged);

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
    qreal getLatitude();
    qreal getLongitude();
    qreal getElevation();
    qreal getSpeed();
    qint16 getSatellites();

    bool getFollowPlane();
    bool getDrawTooltip();
    bool getDrawRoute();
    bool getDrawPredict();
    bool getDrawDiagram();

    bool getGlobal_useOSMMaps();
    qreal getGlobal_velocityVectorLength();


    void setLatitude(qreal value);
    void setLongitude(qreal value);
    void setElevation(qreal value);
    void setSpeed(qreal value);
    void setSatellites(qint16 value);

    void setFollowPlane(bool state);
    void setDrawTooltip(bool state);
    void setDrawRoute(bool state);
    void setDrawPredict(bool state);
    void setDrawDiagram(bool state);

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
    Telemetry telemetry;
    struct MapSettings
    {
        bool followPlane = false;
        bool drawTooltip = true;
        bool drawRoute = true;
        bool drawPredict = true;
        bool drawDiagram = true;
    };
    MapSettings mapSettings;

signals:
    void latitudeChanged();
    void longitudeChanged();
    void elevationChanged();
    void speedChanged();
    void satellitesChanged();
};

#endif // RUNTIMEDATA_H
