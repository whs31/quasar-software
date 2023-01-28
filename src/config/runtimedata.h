#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <QObject>
#include <qqml.h>
#include "sconfig.h"
#include <QVector>
#include <QGeoCoordinate>

class RuntimeData : public QObject
{
    Q_OBJECT

    // мышь
    Q_PROPERTY(quint8 mouseState                    READ getMouseState          WRITE setMouseState          NOTIFY mouseStateChanged)

    // геометрия, необходимая другим классам
    Q_PROPERTY(qreal azimuthalDirection             READ getAzimuthalDirection  WRITE setAzimuthalDirection)
    Q_PROPERTY(qreal flatDirection                  READ getFlatDirection       WRITE setFlatDirection)
    Q_PROPERTY(qreal currentZoomLevel               READ getCurrentZoomLevel    WRITE setCurrentZoomLevel    NOTIFY currentZoomLevelChanged)

    // настройки из выпадающего меню с чекбоксами инструментов карты
    Q_PROPERTY(bool followPlane                     READ getFollowPlane         WRITE setFollowPlane         NOTIFY followPlaneChanged)
    Q_PROPERTY(bool drawGrid                        READ getDrawGrid            WRITE setDrawGrid            NOTIFY drawGridChanged)
    Q_PROPERTY(bool drawTooltip                     READ getDrawTooltip         WRITE setDrawTooltip         NOTIFY drawTooltipChanged)
    Q_PROPERTY(bool drawRoute                       READ getDrawRoute           WRITE setDrawRoute           NOTIFY drawRouteChanged)
    Q_PROPERTY(bool drawPredict                     READ getDrawPredict         WRITE setDrawPredict         NOTIFY drawPredictChanged)
    Q_PROPERTY(bool drawDiagram                     READ getDrawDiagram         WRITE setDrawDiagram         NOTIFY drawDiagramChanged)

    // глобальные настройки НЕ из конфига, которые требуются во фронтэнде
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

    // автозахват РЛИ
    Q_PROPERTY(qreal autocaptureDistance            READ getAutocaptureDistance WRITE setAutocaptureDistance NOTIFY autocaptureDistanceChanged)
    Q_PROPERTY(bool autocaptureEnabled              READ getAutocaptureEnabled  WRITE setAutocaptureEnabled  NOTIFY autocaptureEnabledChanged)
    Q_PROPERTY(int totalAutocapCount                READ getTotalAutocapCount   WRITE setTotalAutocapCount   NOTIFY totalAutocapCountChanged)

    // переменные карты и списков
    Q_PROPERTY(int totalImageCount                  READ getTotalImageCount     WRITE setTotalImageCount     NOTIFY totalImageCountChanged)

    // состояния дочерних "окон" на карте и всё, что к ним относится
    Q_PROPERTY(bool infoWindow                      READ getInfoWindow          WRITE setInfoWindow          NOTIFY infoWindowChanged)
    Q_PROPERTY(bool settingsWindow                  READ getSettingsWindow      WRITE setSettingsWindow      NOTIFY settingsWindowChanged)
    Q_PROPERTY(bool markerWindow                    READ getMarkerWindow        WRITE setMarkerWindow        NOTIFY markerWindowChanged)
    Q_PROPERTY(bool passwordWindow                  READ getPasswordWindow      WRITE setPasswordWindow      NOTIFY passwordWindowChanged)
    Q_PROPERTY(QString enteredPassword              READ getEnteredPassword     WRITE setEnteredPassword     NOTIFY enteredPasswordChanged)
    Q_PROPERTY(QString statusPopup                  READ getStatusPopup         WRITE setStatusPopup         NOTIFY statusPopupChanged)
    Q_PROPERTY(bool statusPopupTrigger              READ getStatusPopupTrigger  WRITE setStatusPopupTrigger  NOTIFY statusPopupTriggerChanged)
    Q_PROPERTY(bool windowLock                      READ getWindowLock          WRITE setWindowLock          NOTIFY windowLockChanged)
    
    QML_ELEMENT
    
public:
    static RuntimeData* get(QObject* parent = nullptr);
    QVector<QGeoCoordinate> autocaptureMarks;
    void clearSARDisk(void);
    void closeAllWindows(void);

    //==============================================                 ====================================================
    //                 ==> GET ==>                                                        <== SET <==
    //==============================================                 ====================================================
    quint8 getMouseState() const;                                       void setMouseState(quint8 state);

    qreal getAzimuthalDirection();                                      void setAzimuthalDirection(qreal value);
    qreal getFlatDirection();                                           void setFlatDirection(qreal value);
    qreal getCurrentZoomLevel();                                        void setCurrentZoomLevel(qreal value);

    bool getFollowPlane();                                              void setFollowPlane(bool state);
    bool getDrawGrid();                                                 void setDrawGrid(bool state);
    bool getDrawTooltip();                                              void setDrawTooltip(bool state);
    bool getDrawRoute();                                                void setDrawRoute(bool state);
    bool getDrawPredict();                                              void setDrawPredict(bool state);
    bool getDrawDiagram();                                              void setDrawDiagram(bool state);

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

    qreal getAutocaptureDistance() const;                               void setAutocaptureDistance(qreal newAutocaptureDistance);
    bool getAutocaptureEnabled() const;                                 void setAutocaptureEnabled(bool state);
    int getTotalAutocapCount() const;                                   void setTotalAutocapCount(int value);

    int getTotalImageCount() const;                                     void setTotalImageCount(int value);

    bool getInfoWindow() const;                                         void setInfoWindow(bool state);
    bool getSettingsWindow() const;                                     void setSettingsWindow(bool state);
    bool getMarkerWindow() const;                                       void setMarkerWindow(bool state);
    bool getPasswordWindow() const;                                     void setPasswordWindow(bool state);
    QString getEnteredPassword() const;                                 void setEnteredPassword(QString string);
    QString getStatusPopup() const;                                     void setStatusPopup(QString string);
    bool getStatusPopupTrigger() const;                                 void setStatusPopupTrigger(bool state);
    bool getWindowLock() const;                                         void setWindowLock(bool state);

    void autocapture(void);

signals:
    //======================================================================================================
    //                                          =!= NOTIFY =!=
    //======================================================================================================
    void mouseStateChanged();

    void currentZoomLevelChanged();

    void followPlaneChanged();
    void drawGridChanged();
    void drawTooltipChanged();
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

    void autocaptureDistanceChanged();
    void autocaptureEnabledChanged();
    void totalAutocapCountChanged();

    void totalImageCountChanged();

    void infoWindowChanged();
    void settingsWindowChanged();
    void markerWindowChanged();
    void passwordWindowChanged();
    void enteredPasswordChanged();
    void statusPopupChanged();
    void statusPopupTriggerChanged();
    void windowLockChanged();

    // my signals TODO: DEPRECATED 

    void autocaptureSignal();
    void clearSARDiskSignal();

private:
    static RuntimeData* _instance;
    explicit RuntimeData(QObject *parent = nullptr);

    quint8 m_mouseState = 0;
    bool m_emulatorMode = false;

    qreal m_azimuthalDirection = 0;
    qreal m_flatDirection = 0;
    qreal m_currentZoomLevel = 2;

    struct MapSettings{
        bool followPlane = false;
        bool drawGrid = false;
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

    struct AutoCaptureVariables
    {
        qreal distance = 0;
        bool enabled = false;
        int totalCount = 0;
    }; AutoCaptureVariables autocaptureVariables;

    struct MapVariables
    {
        int totalImages = 0;
    }; MapVariables mapVariables;

    struct WindowStates
    {
        bool info = false;
        bool settings = false;
        bool marker = false;
        bool password = false;
        QString enteredPassword = "";
        QString statusPopup = "";
        bool statusPopupTrigger = false;
        bool windowLock = false;
    }; WindowStates windowStates;
};

#endif // RUNTIMEDATA_H
