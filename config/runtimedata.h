#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <QObject>
#include <qqml.h>
#include "sconfig.h"
#include <QVector>
#include <QGeoCoordinate>

enum MouseState : short int
{
    Blank,
    MarkerPlacement
};

class RuntimeData : public QObject
{
    Q_OBJECT

    // телеметрия
    Q_PROPERTY(qreal latitude                       READ getLatitude            WRITE setLatitude            NOTIFY latitudeChanged)
    Q_PROPERTY(qreal longitude                      READ getLongitude           WRITE setLongitude           NOTIFY longitudeChanged)
    Q_PROPERTY(qreal elevation                      READ getElevation           WRITE setElevation           NOTIFY elevationChanged)
    Q_PROPERTY(qreal speed                          READ getSpeed               WRITE setSpeed               NOTIFY speedChanged)
    Q_PROPERTY(qreal seaLevel                       READ getSeaLevel            WRITE setSeaLevel            NOTIFY seaLevelChanged)
    Q_PROPERTY(qint16 satellites                    READ getSatellites          WRITE setSatellites          NOTIFY satellitesChanged)

    // геометрия, необходимая другим классам
    Q_PROPERTY(qreal azimuthalDirection             READ getAzimuthalDirection  WRITE setAzimuthalDirection)
    Q_PROPERTY(qreal flatDirection                  READ getFlatDirection       WRITE setFlatDirection)

    // значения связанных осей
    Q_PROPERTY(qreal pitch                          READ getPitch               WRITE setPitch               NOTIFY pitchChanged)
    Q_PROPERTY(qreal roll                           READ getRoll                WRITE setRoll                NOTIFY rollChanged)
    Q_PROPERTY(qreal yaw                            READ getYaw                 WRITE setYaw                 NOTIFY yawChanged)
    Q_PROPERTY(qreal throttle                       READ getThrottle            WRITE setThrottle            NOTIFY throttleChanged)

    // настройки из выпадающего меню с чекбоксами инструментов карты
    Q_PROPERTY(bool followPlane                     READ getFollowPlane         WRITE setFollowPlane)
    Q_PROPERTY(bool drawTooltip                     READ getDrawTooltip         WRITE setDrawTooltip)
    Q_PROPERTY(bool drawRoute                       READ getDrawRoute           WRITE setDrawRoute           NOTIFY drawRouteChanged)
    Q_PROPERTY(bool drawPredict                     READ getDrawPredict         WRITE setDrawPredict         NOTIFY drawPredictChanged)
    Q_PROPERTY(bool drawDiagram                     READ getDrawDiagram         WRITE setDrawDiagram         NOTIFY drawDiagramChanged)

    // глобальные настройки из конфига, которые требуются во фронтэнде
    Q_PROPERTY(bool global_useOSMMaps               READ getGlobal_useOSMMaps)
    Q_PROPERTY(qreal global_velocityVectorLength    READ getGlobal_velocityVectorLength)
    Q_PROPERTY(bool global_emulatorEnabled          READ getEmulatorEnabled     WRITE setEmulatorEnabled     NOTIFY emulatorEnabledChanged)

    // сетевая информация
    Q_PROPERTY(bool connected                       READ getConnected           WRITE setConnected           NOTIFY connectedChanged)
    Q_PROPERTY(QString sarIP                        READ getSARIP               WRITE setSARIP               NOTIFY SARIPChanged)
    Q_PROPERTY(QString pcIP                         READ getPCIP                WRITE setPCIP                NOTIFY PCIPChanged)
    Q_PROPERTY(QString telemetryPort                READ getTelemetryPort       WRITE setTelemetryPort       NOTIFY telemetryPortChanged)
    Q_PROPERTY(QString loaderPort                   READ getLoaderPort          WRITE setLoaderPort          NOTIFY loaderPortChanged)
    Q_PROPERTY(QString commandPort                  READ getCommandPort         WRITE setCommandPort         NOTIFY commandPortChanged)
    Q_PROPERTY(QString listenPort                   READ getListenPort          WRITE setListenPort          NOTIFY listenPortChanged)
    Q_PROPERTY(qreal formProgress                   READ getFormProgress        WRITE setFormProgress        NOTIFY formProgressChanged)
    Q_PROPERTY(qreal loadingProgress                READ getLoadingProgress     WRITE setLoadingProgress     NOTIFY loadingProgressChanged)
    Q_PROPERTY(QString formStatus                   READ getFormStatus          WRITE setFormStatus          NOTIFY formStatusChanged)
    Q_PROPERTY(QString loaderStatus                 READ getLoaderStatus        WRITE setLoaderStatus        NOTIFY loaderStatusChanged)

    // параметры формирования 
    Q_PROPERTY(QString formMode                     READ getFormMode            WRITE setFormMode            NOTIFY formModeChanged)
    Q_PROPERTY(quint32 formLowerBound               READ getFormLowerBound      WRITE setFormLowerBound      NOTIFY formLowerBoundChanged)
    Q_PROPERTY(quint32 formUpperBound               READ getFormUpperBound      WRITE setFormUpperBound      NOTIFY formUpperBoundChanged)
    Q_PROPERTY(float formTime                       READ getFormTime            WRITE setFormTime            NOTIFY formTimeChanged)
    Q_PROPERTY(float formStep                       READ getFormStep            WRITE setFormStep            NOTIFY formStepChanged)
    Q_PROPERTY(int formOverrideGPSData              READ getFormOverrideGPSData WRITE setFormOverrideGPSData NOTIFY formOverrideGPSDataChanged)
    Q_PROPERTY(float formGPSHeight                  READ getFormGPSHeight       WRITE setFormGPSHeight       NOTIFY formGPSHeightChanged)
    Q_PROPERTY(float formGPSVelocity                READ getFormGPSVelocity     WRITE setFormGPSVelocity     NOTIFY formGPSVelocityChanged)
    Q_PROPERTY(bool formingContinuous               READ getFormingContinuous   WRITE setFormingContinuous   NOTIFY formingContinuousChanged)

    // автозахват РЛИ
    Q_PROPERTY(qreal autocaptureDistance           READ getAutocaptureDistance WRITE setAutocaptureDistance NOTIFY autocaptureDistanceChanged)
    Q_PROPERTY(bool autocaptureEnabled             READ getAutocaptureEnabled  WRITE setAutocaptureEnabled  NOTIFY autocaptureEnabledChanged)

    // общие переменные с РЛС
    Q_PROPERTY(qreal freeDiskSpace                 READ getFreeDiskSpace       WRITE setFreeDiskSpace       NOTIFY freeDiskSpaceChanged)
    Q_PROPERTY(qreal totalDiskSpace                READ getTotalDiskSpace      WRITE setTotalDiskSpace      NOTIFY totalDiskSpaceChanged)
    
    QML_ELEMENT
    
public:
    static RuntimeData* initialize(QObject* parent = nullptr);
    static short int mouseState;
    QVector<QGeoCoordinate> autocaptureMarks;
    void toggleConsole(void);
    void formSingleImage(void);
    void formContinuous(void);
    void clearSARDisk(void);

    //==============================================                 ====================================================
    //                 ==> GET ==>                                                        <== SET <==
    //==============================================                 ====================================================
    qreal getLatitude();                                                void setLatitude(qreal value);
    qreal getLongitude();                                               void setLongitude(qreal value);
    qreal getElevation();                                               void setElevation(qreal value);
    qreal getSpeed();                                                   void setSpeed(qreal value);
    qreal getSeaLevel();                                                void setSeaLevel(qreal value);
    qint16 getSatellites();                                             void setSatellites(qint16 value);

    qreal getAzimuthalDirection();                                      void setAzimuthalDirection(qreal value);
    qreal getFlatDirection();                                           void setFlatDirection(qreal value);

    qreal getPitch();                                                   void setPitch(qreal value);
    qreal getRoll();                                                    void setRoll(qreal value);
    qreal getYaw();                                                     void setYaw(qreal value);
    qreal getThrottle();                                                void setThrottle(qreal value);

    bool getFollowPlane();                                              void setFollowPlane(bool state);
    bool getDrawTooltip();                                              void setDrawTooltip(bool state);
    bool getDrawRoute();                                                void setDrawRoute(bool state);
    bool getDrawPredict();                                              void setDrawPredict(bool state);
    bool getDrawDiagram();                                              void setDrawDiagram(bool state);

    bool getGlobal_useOSMMaps(); 
    qreal getGlobal_velocityVectorLength();
    bool getEmulatorEnabled();                                          void setEmulatorEnabled(bool state);

    bool getConnected();                                                void setConnected(bool state);
    QString getSARIP();                                                 void setSARIP(QString string);
    QString getPCIP();                                                  void setPCIP(QString string);
    QString getTelemetryPort();                                         void setTelemetryPort(QString string);
    QString getLoaderPort();                                            void setLoaderPort(QString string);
    QString getCommandPort();                                           void setCommandPort(QString string);
    QString getListenPort();                                            void setListenPort(QString string);
    qreal getLoadingProgress();                                         void setLoadingProgress(qreal value);
    qreal getFormProgress();                                            void setFormProgress(qreal value);
    QString getFormStatus();                                            void setFormStatus(QString string);
    QString getLoaderStatus();                                          void setLoaderStatus(QString string);

    QString getFormMode();                                              void setFormMode(QString string);
    quint32 getFormLowerBound();                                        void setFormLowerBound(quint32 value);
    quint32 getFormUpperBound();                                        void setFormUpperBound(quint32 value);
    float getFormTime();                                                void setFormTime(float value);
    float getFormStep();                                                void setFormStep(float value);
    int getFormOverrideGPSData();                                       void setFormOverrideGPSData(int state);
    float getFormGPSHeight();                                           void setFormGPSHeight(float value);
    float getFormGPSVelocity();                                         void setFormGPSVelocity(float value);
    bool getFormingContinuous();                                        void setFormingContinuous(bool state);

    qreal getAutocaptureDistance() const;                               void setAutocaptureDistance(qreal newAutocaptureDistance);
    bool getAutocaptureEnabled() const;                                 void setAutocaptureEnabled(bool state);

    qreal getFreeDiskSpace() const;                                     void setFreeDiskSpace(qreal value);
    qreal getTotalDiskSpace() const;                                    void setTotalDiskSpace(qreal value);

    void autocapture(void);

signals:
    //======================================================================================================
    //                                          =!= NOTIFY =!=
    //======================================================================================================
    void latitudeChanged();
    void longitudeChanged();
    void elevationChanged();
    void speedChanged();
    void seaLevelChanged();
    void satellitesChanged();

    void pitchChanged();
    void rollChanged();
    void yawChanged();
    void throttleChanged();

    void drawRouteChanged();
    void drawPredictChanged();
    void drawDiagramChanged();

    void emulatorEnabledChanged();

    void connectedChanged();
    void SARIPChanged();
    void PCIPChanged();
    void telemetryPortChanged();
    void loaderPortChanged();
    void commandPortChanged();
    void listenPortChanged();
    void formProgressChanged();
    void loadingProgressChanged();
    void formStatusChanged();
    void loaderStatusChanged();

    void formModeChanged();
    void formLowerBoundChanged();
    void formUpperBoundChanged();
    void formTimeChanged();
    void formStepChanged();
    void formOverrideGPSDataChanged();
    void formGPSHeightChanged();
    void formGPSVelocityChanged();
    void formingContinuousChanged();

    void autocaptureDistanceChanged();
    void autocaptureEnabledChanged();

    void freeDiskSpaceChanged();
    void totalDiskSpaceChanged();

    // my signals

    void autocaptureSignal();
    void toggleConsoleSignal();
    void formSingleImageSignal();
    void formContinuousSignal();
    void clearSARDiskSignal();

private:
    static RuntimeData* _instance;
    explicit RuntimeData(QObject *parent = nullptr);

    bool m_emulatorMode = false;

    struct Telemetry {
        qreal latitude = 0;
        qreal longitude = 0;
        qreal elevation = 0;
        qreal speed = 0;
        qreal direction = -1;
        qreal pitchAngle = -1;
        qreal rollAngle = -1;
        qreal seaLevel = 0; 
        qint16 satellites = -1;

    }; Telemetry telemetry;

    qreal m_azimuthalDirection = 0;
    qreal m_flatDirection = 0;

    struct AircraftAxes {
        qreal pitch = 0;
        qreal roll = 0;
        qreal yaw = 0;
        qreal throttle = 0;
    }; AircraftAxes aircraftAxes;

    struct MapSettings{
        bool followPlane = false;
        bool drawTooltip = true;
        bool drawRoute = true;
        bool drawPredict = true;
        bool drawDiagram = true;
    }; MapSettings mapSettings;
    
    struct ConnectionStatus {
        bool connected = false;
        QString sarIP = "127.0.0.1?";
        QString pcIP = "127.0.0.1?";
        QString telemetryPort = "00000?";
        QString loaderPort = "00000?";
        QString commandPort = "00000?";
        QString listenPort = "00000?";
        qreal formProgress = 0;
        qreal loadingProgress = 0;
        QString formStatus = "ожидание подключения";
        QString loaderStatus = "Статус загрузчика";
    }; ConnectionStatus connectionStatus;

    struct FormParameters
    {
        QString mode = "m1";
        quint32 lowerBound = 100;
        quint32 upperBound = 3000;
        float time = 1;
        float step = 1;
        int overrideGPS = 0;
        float gpsHeight = 150;
        float gpsVelocity = 100;
        bool formingContinuous = false;
    }; FormParameters formParameters;

    struct AutoCaptureVariables
    {
        qreal distance = 0;
        bool enabled = false;
    }; AutoCaptureVariables autocaptureVariables;

    struct SARCommonVariables
    {
        qreal freeDiskSpace = 0;
        qreal totalDiskSpace = 0;
    }; SARCommonVariables sarCommonVariables;
};

#endif // RUNTIMEDATA_H
