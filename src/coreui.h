#ifndef COREUI_H
#define COREUI_H

#include <QSslSocket>
#include <QTimer>
#include "qqml.h"
#include <QQmlEngine>
#include <QQmlContext>
#include <QRect>
#include <QScopedPointer>

//qml types
#include "backend/ftelemetry.h"
#include "backend/fdynamicvariables.h"
#include "backend/fstaticvariables.h"


#include "extension.h"
#include "udpremote.h"
#include "tcpremote.h"
#include "imageprocessing.h"
#include "imagemanager.h"
#include "messageparser.h"
#include "debug.h"

#include "stext.h"
#include "backend/smousestate.h"

#include "settingsdialog.h"
#include "aboutdialog.h"
#include "passworddialog.h"

#include "style.h"
#include "linkerqml.h"
#include "sconfig.h"
#include "cachemanager.h"
#include "tcpdownloader.h"
#include "tilesmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CoreUI; }
QT_END_NAMESPACE

enum CommandType {
    TelemetryCommand,
    FormCommand
};

class CoreUI : public QGoodWindow
{
    Q_OBJECT

public:
    CoreUI(QWidget *parent = nullptr);
    ~CoreUI();
    //static public methods
    static CoreUI* getDebugPointer(void);
    static QRect screenResolution;

    //public methods
    void debugStreamUpdate(QString _text, int msgtype);

    //public getters
    void getConfig(QString s1, QString s2, QString s3, float f1, float f2, float f3, float f4, float f5, float f6, QString s4, QString s5, bool b1, bool b2, bool b3);
    bool getReady(void);
    QQuickItem* getMapPointer(void);

public slots:
    //utility public slots
    void Connected();
    void Disconnected();

    //gui public slots
    void setPushButton_goLeftEnabled(bool state);
    void setPushButton_goRightEnabled(bool state);
    void updateLoaderLabel(void);
    void updateDirectory(void);
    void updateImageManagerLabels(int total, int current);
    void updateImageMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, float lx, float ly, float divAngle, QString hexSum, QString datetime, bool match);
    void enableImageBar(bool b);
    void updateProgress(float f);
    void updateTelemetryLabels(int satcount);
    void setCheckboxState(bool b);

private:
    //object pointers
    Ui::CoreUI *ui;
    static CoreUI* debugPointer;
    UDPRemote *telemetryRemote;
    UDPRemote *formRemote;
    UDPRemote *consoleListenerRemote;
    TCPRemote *tcpRemote;
    ImageProcessing *imageProcessing;
    LinkerQML *linker;
    TCPDownloader *downloader;
    QQuickItem* qml;

    //qml types
    FTelemetry* fTelemetry;
    FDynamicVariables* fDynamicVariables;
    FStaticVariables* fStaticVariables;

    //timers
    QTimer *timer;
    QTimer *udpTimeout;
    QTimer *uiTimer1;

    //global flags
    bool uiReady = false;
    bool connected = false;
    bool autoUpdate = true;
    bool formingContinuous = false;

    //global variables
    double _conckc = 0;

    QString sar_mode = "m1";
    quint32 sar_lowerbound = 100;
    quint32 sar_upperbound = 3000;
    float sar_time = 1.0;
    float sar_dx = 1;
    int sar_override_gps = 0;
    float sar_gps_height = 150;
    float sar_gps_velocity = 100;

    //private methods
    void InitializeUI();
    void InitializeConnections();
    void InitializeDockwidgets();
    void SendRemoteCommand(QString command, CommandType type);

private slots:
    //header
    void on_minButton_clicked();
    void on_minmaxButton_clicked();
    void on_closeButton_clicked();
    void on_settingsButton_clicked();
    void on_infoButton_clicked();

    //utility slots
    void ReadTelemetry(QByteArray data);
    void ReadForm(QByteArray data);
    void ReadSARConsole(QByteArray data);
    void Halftime();

    //gui slots
    void on_checkBox_drawTooltip_stateChanged(int arg1);
    void on_checkBox_drawTrack_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_drawPredict_stateChanged(int arg1);
    void on_checkBox_drawDiagram_stateChanged(int arg1);
    void on_pushButton_goLeft_clicked();
    void on_pushButton_goRight_clicked();
    void on_checkBox_autoUpdate_stateChanged(int arg1);
    void on_pushButton_expandImageInfo_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_panImage_clicked();
    void on_pushButton_showImage_clicked();
    void on_pushButton_clearTrack_clicked();
    void on_pushButton_placeMarker_clicked();
    void on_pushButton_showAllImages_clicked();
    void on_pushButton_reconnect_clicked();
    void on_pushButton_clearCache_clicked();
    void on_pushButton_formSingleImage_clicked();
    void on_pushButton_launchContinuous_clicked();
    void on_pushButton_stopContinuous_clicked();
    void on_pushButton_showDebugConsoleDock_clicked();
    void on_pushButton_showMapToolsDock_clicked();
    void on_spinBox_sarLowerBound_valueChanged(int arg1);
    void on_spinBox_sarUpperBound_valueChanged(int arg1);
    void on_doubleSpinBox_sarTime_valueChanged(double arg1);
    void on_doubleSpinBox_sarDX_valueChanged(double arg1);
    void on_checkBoxEnableManualGPS_stateChanged(int arg1);
    void on_doubleSpinBox_height_valueChanged(double arg1);
    void on_doubleSpinBox_velocity_valueChanged(double arg1);
    void on_pushButton_showSARConsole_clicked();
};
#endif // COREUI_H
