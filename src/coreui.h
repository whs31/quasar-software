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

#include "map/linkerqml.h"
#include "map/tilesmanager.h"
#include "map/backend/fmousekeyhandler.h"
#include "map/backend/recallhandler.h"
#include "map/backend/flightprediction.h"
#include "map/backend/scalegridbackend.h"
#include "map/backend/signallinker.h"
#include "network/udpremote.h"
#include "network/messageparser.h"
#include "network/tcpdownloader.h"
#include "network/modules/telemetryremote.h"
#include "network/modules/feedbackremote.h"
#include "network/modules/execdremote.h"
#include "func/smath.h"
#include "func/stext.h"
#include "gui/dynamicresolution.h"
#include "gui/passworddialog.h"
#include "gui/thememanager.h"
#include "gui/applicationheader.h"
#include "gui/windows/dialogwindowbackend.h"
#include "gui/windows/autocapturemarkwindowbackend.h"
#include "gui/windows/settingswindowbackend.h"
#include "gui/windows/markerwindowbackend.h"
#include "emulator/flightemulator.h"

#include "data/datatelemetry.h"

#include <plugin.h>
#include <pluginHostAPI.h>

#include "emulator/saroutputconsoleemulator.h" //remove me

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
    //gui public slots
    void updateProgress(float f);
    void reconnectSlot();
    void disconnectSlot();

private:
    //object pointers
    Ui::CoreUI *ui;
    static CoreUI* debugPointer;
    TelemetryRemote* telemetryRemote = nullptr;
    FeedbackRemote* feedBackRemote = nullptr;
    UDPRemote* formRemote = nullptr;
    LinkerQML* linker = nullptr;
    TCPDownloader* downloader = nullptr;
    QQuickItem* qml = nullptr;
    FlightEmulator* flightEmulator = nullptr;
    PluginHostAPI* HostAPI = nullptr;
    DynamicResolution* dynamicResolutionInstance = nullptr;

    //global flags
    bool uiReady = false;
    bool formingContinuous = false;

    //global variables
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
    void ReadForm(QByteArray data);
    void ReadSARConsole(QByteArray data);
    void SendClearCommand(void);

    //gui slots
    void FormSingleImage();
};
#endif // COREUI_H
