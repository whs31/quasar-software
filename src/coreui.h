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

#include "config/settingsdialog.h"
#include "config/runtimedata.h"

//qml types
#include "backend/fmousekeyhandler.h"
#include "backend/recallhandler.h"
#include "backend/flightprediction.h"
#include "backend/scalegridbackend.h"
#include "backend/signallinker.h"

#include "udpremote.h"
#include "messageparser.h"
#include "smath.h"
#include "stext.h"
#include "dynamicresolution.h"
#include "passworddialog.h"
#include "style.h"
#include "thememanager.h"
#include "linkerqml.h"
#include "tcpdownloader.h"
#include "tilesmanager.h"
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

    //public methods
    void debugStreamUpdate(QString _text, int msgtype);

    //public getters
    bool getReady(void);
    bool eventFilter(QObject* obj, QEvent* event);

public slots:
    //utility public slots
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
    bool formingContinuous = false;

    //global variables
    double _conckc = 0;
    QSet<int> pressedKeys;
    static QRect screenResolution;

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
    void TelemetryHeartbeat(void);
    void SendClearCommand(void);

    //gui slots
    void FormSingleImage();
};
#endif // COREUI_H
