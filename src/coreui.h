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


#include "extension.h"
#include "udpremote.h"
#include "tcpremote.h"
#include "settingsdialog.h"
#include "imageprocessing.h"
#include "imagemanager.h"
#include "messageparser.h"
#include "debug.h"

#include "style.h"
#include "linkerqml.h"
#include "sconfig.h"
#include "tcpdownloader.h"
#include "tilesmanager.h"

// #define MAPTOOLS_WIDTH 120
// #define MAPTOOLS_HEIGHT 70
// #define DEBUG_WIDTH 250
// #define DEBUG_HEIGHT 150

QT_BEGIN_NAMESPACE
namespace Ui { class CoreUI; }
QT_END_NAMESPACE

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
    void WriteSampleDebugLog(); //delme

    //gui public slots
    void setPushButton_goLeftEnabled(bool state);
    void setPushButton_goRightEnabled(bool state);
    void updateLoaderLabel(void);
    void updateDirectory(void);
    void updateImageManagerLabels(int total, int current);
    void updateImageMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, float lx, float ly, float divAngle, QString hexSum, QString datetime, bool match);
    void enableImageBar(bool b);
    void updateProgress(float f);
    void updateTelemetryLabels(float lat, float lon, float speed, float elevation, int satcount);

private:
    //object pointers
    Ui::CoreUI *ui;
    static CoreUI* debugPointer;
    UDPRemote *udpRemote;
    TCPRemote *tcpRemote;
    ImageProcessing *imageProcessing;
    LinkerQML *linker;
    TCPDownloader *downloader;
    QQuickItem* qml;

    //qml types
    FTelemetry* fTelemetry;

    //timers
    QTimer *timer;
    QTimer *udpTimeout;
    QTimer *uiTimer1;

    //global flags
    bool uiReady = false;
    bool connected = false;
    bool autoUpdate = true;

    //global variables
    double _conckc = 0;
    std::array<double, 5> telemetry; //lat, lon, speed, elevation, sats

    //private methods
    void InitializeUI();
    void InitializeConnections();
    void InitializeDockwidgets();
    void SendRemoteCommand(QString command);

private slots:
    //header
    void on_minButton_clicked();
    void on_minmaxButton_clicked();
    void on_closeButton_clicked();
    void on_settingsButton_clicked();

    //utility slots
    void ReadUDPData(QByteArray data);
    void Halftime();

    //gui slots
    void on_checkBox_drawTooltip_stateChanged(int arg1);
    void on_checkBox_drawTrack_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_drawPredict_stateChanged(int arg1);
    void on_checkBox_drawDiagram_stateChanged(int arg1);
    void on_pushButton_panGPS_clicked();
    void on_pushButton_goLeft_clicked();
    void on_pushButton_goRight_clicked();
    void on_checkBox_autoUpdate_stateChanged(int arg1);
    void on_pushButton_expandImageInfo_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_panImage_clicked();
    void on_pushButton_showImage_clicked();
    void on_pushButton_clearTrack_clicked();
    void on_pushButton_showAllImages_clicked();
    void on_pushButton_reconnect_clicked();
    void on_pushButton_clearCache_clicked();
    void on_pushButton_formSingleImage_clicked();
    void on_pushButton_launchContinuous_clicked();
    void on_pushButton_stopContinuous_clicked();
    void on_pushButton_showDebugConsoleDock_clicked();
    void on_pushButton_showMapToolsDock_clicked();
};
#endif // COREUI_H
