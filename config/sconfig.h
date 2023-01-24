#ifndef SCONFIG_H
#define SCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QMessageBox>
#include <QHash>
#include <QVariant>

#include "cachemanager.h"
#include "config.h"
#include "jsonconfig.h"

#include "debug.h"
#include "thememanager.h"

class SConfig : public QObject
{
    Q_OBJECT
    
    // general
    Q_PROPERTY(QString sudoPassword               READ getSudoPassword              WRITE setSudoPassword             NOTIFY sudoPasswordChanged)
    Q_PROPERTY(bool enableDebugConsole            READ getDebugConsole              WRITE setDebugConsole             NOTIFY debugConsoleChanged)
    
    // network
    Q_PROPERTY(QString networkType                READ getNetworkType               WRITE ЫsetNetworkType             NOTIFY networkTypeChanged)
    Q_PROPERTY(QString de10IP                     READ getDE10IP                    WRITE setDE10IP                   NOTIFY de10IPChanged)
    Q_PROPERTY(QString telemetryPort              READ getTelemetryPort             WRITE setTelemetryPort            NOTIFY telemetryPortChanged)
    Q_PROPERTY(float telemetryFrequency           READ getTelemetryFrequency        WRITE setTelemetryFrequency       NOTIFY telemetryFrequencyChanged)
    Q_PROPERTY(QString computerIP                 READ getComputerIP                WRITE setComputerIP               NOTIFY computerIPChanged)
    Q_PROPERTY(QString loaderPort                 READ getLoaderPort                WRITE setLoaderPort               NOTIFY loaderPortChanged)
    Q_PROPERTY(QString execdPort                  READ getExecdPort                 WRITE setExecdPort                NOTIFY execdPortChanged)
    Q_PROPERTY(QString terminalPort               READ getTerminalPort              WRITE setTerminalPort             NOTIFY terminalPortChanged)
    Q_PROPERTY(bool useOldExecdEndline            READ getUseOldExecdEndline        WRITE setUseOldExecdEndline       NOTIFY useOldExecdEndlineChanged)

    // map
    Q_PROPERTY(bool onlineMaps                    READ getOnlineMaps                WRITE setOnlineMaps               NOTIFY onlineMapsChanged)
    Q_PROPERTY(float velocityVectorLength         READ getVelocityVectorLength      WRITE setVelocityVectorLength     NOTIFY velocityVectorLengthChanged)
    Q_PROPERTY(QString antennaPosition            READ getAntennaPosition           WRITE setAntennaPosition          NOTIFY antennaPositionChanged)
    Q_PROPERTY(float diagramThetaAzimuth          READ getDiagramThetaAzimuth       WRITE setDiagramThetaAzimuth      NOTIFY diagramThetaAzimuthChanged)
    Q_PROPERTY(qreal previousSessionLatitude      READ getPreviousSessionLatitude   WRITE setPreviousSessionLatitude  NOTIFY previousSessionLatitudeChanged)
    Q_PROPERTY(qreal previousSessionLongitude     READ getPreviousSessionLongitude  WRITE setPreviousSessionLongitude NOTIFY previousSessionLongitudeChanged)
    
    // image
    Q_PROPERTY(float angleCorrection              READ getAngleCorrection           WRITE setAngleCorrection          NOTIFY angleCorrectionChanged)
    Q_PROPERTY(bool globalRadians                 READ getGlobalRadians             WRITE setGlobalRadians            NOTIFY globalRadiansChanged)
    Q_PROPERTY(bool useDriftAngle                 READ getUseDriftAngle             WRITE setUseDriftAngle            NOTIFY useDriftAngleChanged)
    Q_PROPERTY(float thetaAzimuthCorrection       READ getThetaAzimuthCorrection    WRITE setThetaAzimuthCorrection   NOTIFY thetaAzimuthCorrectionChanged)
    Q_PROPERTY(QString defaultCatalogue           READ getDefaultCatalogue          WRITE setDefaultCatalogue         NOTIFY defaultCatalogueChanged)


public:
    static SConfig* get(QObject* parent = nullptr);

    //==============================================                 ====================================================
    //                 ==> GET ==>                //                 //                  <== SET <==                   //
    //==============================================                 ====================================================
    QString getSudoPassword();                                       void setSudoPassword(QString string);    
    bool getDebugConsole();                                          void setDebugConsole(bool state);
    QString getNetworkType();                                        void setNetworkType(QString string);
    QString getDE10IP();                                             void setDE10IP(QString string);
    QString getTelemetryPort();                                      void setTelemetryPort(QString string);    
    float getTelemetryFrequency();                                   void setTelemetryFrequency(float value);        
    QString getComputerIP();                                         void setComputerIP(QString string);    
    QString getLoaderPort();                                         void setLoaderPort(QString string);    
    QString getExecdPort();                                          void setExecdPort(QString string);
    QString getTerminalPort();                                       void setTerminalPort(QString string);    
    bool getUseOldExecdEndline();                                    void setUseOldExecdEndline(bool state);        

    bool getOnlineMaps();                                            void setOnlineMaps(bool state);
    float getVelocityVectorLength();                                 void setVelocityVectorLength(float value);    
    QString getAntennaPosition();                                    void setAntennaPosition(QString string);
    float getDiagramThetaAzimuth();                                  void setDiagramThetaAzimuth(float value);

    float getAngleCorrection();                                      void setAngleCorrection(float value);          
    bool getGlobalRadians();                                         void setGlobalRadians(bool state);        
    bool getUseDriftAngle();                                         void setUseDriftAngle(bool state);
    float getThetaAzimuthCorrection();                               void setThetaAzimuthCorrection(float value);        
    QString getDefaultCatalogue();                                   void setDefaultCatalogue(QString string);    
    qreal getPreviousSessionLatitude();                              void setPreviousSessionLatitude(qreal value);
    qreal getPreviousSessionLongitude();                             void setPreviousSessionLongitude(qreal value);

    void loadSettings(void);                                       
    void saveSettings(void);                                       
    void saveQuiet(void);                                          
    void discardSettings(void);
    QHash<QString, QVariant>* getPluginConfig(void);
signals:
    //======================================================================================================
    //                                          =!= NOTIFY =!=                                            //
    //======================================================================================================
    void sudoPasswordChanged();
    void debugConsoleChanged();

    void networkTypeChanged();
    void de10IPChanged();
    void telemetryPortChanged();
    void telemetryFrequencyChanged();
    void computerIPChanged();
    void loaderPortChanged();
    void execdPortChanged();
    void terminalPortChanged();
    void useOldExecdEndlineChanged();

    void onlineMapsChanged();
    void velocityVectorLengthChanged();
    void antennaPositionChanged();
    void diagramThetaAzimuthChanged();

    void angleCorrectionChanged();
    void globalRadiansChanged();
    void useDriftAngleChanged();
    void thetaAzimuthCorrectionChanged();
    void defaultCatalogueChanged();

    void previousSessionLatitudeChanged();
    void previousSessionLongitudeChanged();

private:
    explicit SConfig(QObject* parent = nullptr);
    static SConfig* pointer;
    static Config* config;
    static JsonConfig* jsonConfig;

    void save();
    QHash<QString, QVariant> m_pluginConfig;

    QString m_sudoPassword;
    bool m_debugConsole;
    QString m_networkType;
    QString m_de10IP;
    QString m_telemetryPort;
    float m_telemetryFrequency;
    QString m_computerIP;
    QString m_loaderPort;
    QString m_execdPort;
    QString m_terminalPort;
    bool m_useOldExecdEndline;
    bool m_onlineMaps;
    float m_velocityVectorLength;
    QString m_antennaPosition;
    float m_diagramThetaAzimuth;
    float m_angleCorrection;
    bool m_globalRadians;
    bool m_driftAngle;
    float m_thetaAzimuthCorrection;
    qreal m_previousSessionLatitude;
    qreal m_previousSessionLongitude;
    QString m_defaultCatalogue;
};

#endif // SCONFIG_H
