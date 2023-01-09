#ifndef COREUI_H
#define COREUI_H

#include <QSslSocket>
#include <QTimer>
#include "qqml.h"
#include <QQuickStyle>
#include <QQmlEngine>
#include <QQmlContext>
#include <QRect>
#include <QScopedPointer>

//qml types
#include "backend/fmousekeyhandler.h"
#include "backend/ibackendiohandler.h"

#include "extension.h"
#include "udpremote.h"
#include "messageparser.h"
#include "smath.h"

#include "settingsdialog.h"
#include "aboutdialog.h"
#include "passworddialog.h"

#include "style.h"
#include "linkerqml.h"

#include "tcpdownloader.h"
#include "tilesmanager.h"
#include "runtimedata.h"
#include "backend/flightprediction.h"

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
    void updateProgress(float f);
    void reconnectSlot();
    void disconnectSlot();

private:
    //object pointers
    Ui::CoreUI *ui;
    static CoreUI* debugPointer;
    UDPRemote *telemetryRemote;
    UDPRemote *formRemote;
    UDPRemote *consoleListenerRemote;
    LinkerQML *linker;
    TCPDownloader *downloader;
    QQuickItem* qml;

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

    //@TODO new class
    QString sar_mode = "m1";
    quint32 sar_lowerbound = 100;
    quint32 sar_upperbound = 3000;
    float sar_time = 1.0;
    float sar_dx = 1;
    int sar_override_gps = 0;
    float sar_gps_height = 150;
    float sar_gps_velocity = 100;

    //private methods
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
    void on_pushButton_placeMarker_clicked();
    void on_pushButton_formSingleImage_clicked();
    void on_pushButton_launchContinuous_clicked();
    void on_pushButton_stopContinuous_clicked();
    void on_pushButton_showDebugConsoleDock_clicked();
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
