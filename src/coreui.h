#ifndef COREUI_H
#define COREUI_H

#include <QMainWindow>
#include <QScreen>
#include <QSslSocket>
#include <QTimer>
#include "qqml.h"
#include <QQuickStyle>
#include <QQmlEngine>
#include <QQmlContext>
#include <QRect>
#include <QScopedPointer>
#include <QSet>
#include <QDesktopWidget>

//qml types
#include "backend/fmousekeyhandler.h"
#include "backend/recallhandler.h"
#include "backend/flightprediction.h"
#include "backend/scalegridbackend.h"

#include "udpremote.h"
#include "messageparser.h"
#include "smath.h"
#include "stext.h"

#include "dynamicresolution.h"
#include "settingsdialog.h"
#include "passworddialog.h"

#include "style.h"
#include "thememanager.h"
#include "linkerqml.h"

#include "tcpdownloader.h"
#include "tilesmanager.h"
#include "runtimedata.h"
#include "backend/signallinker.h"
#include "applicationheader.h"
#include "flightemulator.h"

#include <plugin.h>
#include <pluginHostAPI.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CoreUI; }
QT_END_NAMESPACE

enum CommandType {
    TelemetryCommand,
    FormCommand
};

class CoreUI : public QMainWindow
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
    bool eventFilter(QObject* obj, QEvent* event);

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
    FlightEmulator* flightEmulator;
    PluginHostAPI *HostAPI;
    DynamicResolution* dynamicResolutionInstance;

    //timers
    QTimer *timer;
    QTimer *udpTimeout;
    QTimer *uiTimer1;

    //global flags
    bool uiReady = false;
    bool autoUpdate = true;
    bool formingContinuous = false;

    //global variables
    double _conckc = 0;
    QSet<int> pressedKeys;

    //plugin system
    struct Plugins 
    {
        bool terminalLoaded = false;

        QWidget* terminal = nullptr;
    }; Plugins plugins;

    //private methods
    void SendRemoteCommand(QString command, CommandType type);
    void* LoadPlugin(QString path);

private slots:
    //header
    void MinimizeSlot();
    void CloseSlot();
    void SettingsSlot();
    void InfoSlot();
    void EmulatorSlot();
    void DebugSlot();

    //utility slots
    void ReadTelemetry(QByteArray data);
    void ReadForm(QByteArray data);
    void ReadSARConsole(QByteArray data);
    void Halftime(void);
    void SendClearCommand(void);

    //gui slots
    void FormSingleImage();
};
#endif // COREUI_H
