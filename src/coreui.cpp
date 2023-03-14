#include "coreui.h"
#include "ui_coreui.h"
#include "gui/windows/focuswindowbackend.h"
#include "theme/include/theme.hpp"
#include "config/settingsdialog.h"
#include "config/runtimedata.h"
#include "map/tilesmanager.h"
#include "map/backend/routelogger.h"
#include "map/backend/fmousekeyhandler.h"
#include "map/backend/recallhandler.h"
#include "map/backend/flightprediction.h"
#include "map/backend/scalegridbackend.h"
#include "map/backend/signallinker.h"
#include "func/smath.h"
#include "func/stext.h"
#include "gui/passworddialog.h"
#include "gui/applicationheader.h"
#include "gui/windows/dialogwindowbackend.h"
#include "gui/windows/autocapturemarkwindowbackend.h"
#include "gui/windows/settingswindowbackend.h"
#include "gui/windows/markerwindowbackend.h"
#include "data/datatelemetry.h"
#include "data/datasar.h"
#include "data/dataformparameters.h"

#include <QDebug>
#include "qqml.h"
#include <QQuickStyle>
#include <QQmlEngine>
#include <QQmlContext>
#include <QRect>
#include <QScreen>
#include <QSslSocket>

bool CoreUI::uiReady = false;
QRect CoreUI::screenResolution;
CoreUI::CoreUI(QWidget *parent) : QMainWindow(parent),
                                  ui(new Ui::CoreUI)
{
    // cache setup
    CacheManager::get(this);

    // qml registration here
    qmlRegisterType<SMath>("SMath", 1, 0, "SMath");
    qmlRegisterType<SText>("SText", 1, 0, "SText");
    qmlRegisterType<FMouseKeyHandler>("MouseKeyHandler", 1, 0, "MouseKeyHandler");
    qmlRegisterSingletonInstance<MarkerManager>("MarkerManager", 1, 0, "MarkerManager", MarkerManager::get());
    qmlRegisterSingletonInstance<ImageManager>("ImageManager", 1, 0, "ImageManager", ImageManager::get(this));
    qmlRegisterSingletonInstance<DiskTools>("DiskManager", 1, 0, "DiskManager", DiskTools::get(this));
    
    // ux and tiles must be called before ui initialization
    TilesManager::get();
    

    // ui setup. do not call any unintentional code before ui is initialized (uiReady == true)
    ui->setupUi(this);
    uiReady = true;
    this->setStyleSheet("QWidget\n{\n	background-color: " + Theme::get(this)->color("dark1") + ";\n}\nQAbstractScrollArea "
                        "{\n  background-color: " + Theme::get()->color("dark1") + ";\n"
                        "  border: 1px solid " + Theme::get()->color("dark1") + ";\n  border-radius: 4px;\n  /* fix #159 */\n  padding: 2px;\n  "
                        "\n  color: #3B4252;\n}\nQScrollBar:vertical {\n  background-color: #3B4252;\n  width: 16px;\n  "
                        "margin: 16px 2px 16px 2px;\n  border: 1px solid #121617;\n  border-radius: 4px;\n}\nQScrollBar::handle:vertical "
                        "{\n  background-color: #293133;\n  border: 1px solid #121617;\n  min-height: 8px;\n  border-radius: 4px;\n}\n"
                        "QScrollBar::handle:vertical:hover {\n  background-color: #3e4c4f;\n  border: #3e4c4f;\n  border-radius: 4px;\n  "
                        "min-height: 8px;\n}");

    qDebug() << "[CORE] Starting UI initialization...";

    #ifdef QMAKE_COMPILATOR
    qWarning() << "[CORE] Using QMAKE_COMPILATOR build settings";
    #else
    qInfo() << "[CORE] Using CMake build settings";
    #endif

    // config
    qmlRegisterSingletonInstance("Config", 1, 0, "Config", SConfig::get());

    if (SConfig::get()->getOnlineMaps())
        qDebug() << "[CORE] Using ONLINE map tileserver";
    else
        qDebug() << "[CORE] Using OFFLINE map tileserver";

    // qml types that require SConfig declared here
    qmlRegisterSingletonInstance<RuntimeData>("RuntimeData", 1, 0, "RuntimeData", RuntimeData::get(this));
    qmlRegisterType<RecallHandler>("RecallHandler", 1, 0, "RecallHandler");
    qmlRegisterType<FlightPrediction>("FlightPrediction", 1, 0, "Predict");
    qmlRegisterType<ScaleGridBackend>("ScaleGridBackend", 1, 0, "ScaleGridBackend");
    qmlRegisterSingletonInstance<RouteLogger>("RouteLogger", 1, 0, "RouteLogger", new RouteLogger(this));

    // signal linker setup
    qmlRegisterSingletonInstance<SignalLinker>("SignalLinker", 1, 0, "SignalLinker", SignalLinker::get(this));
    connect(SignalLinker::get(), SIGNAL(closeSignal()), this, SLOT(CloseSlot()));
    connect(SignalLinker::get(), SIGNAL(minimizeSignal()), this, SLOT(MinimizeSlot()));
    connect(SignalLinker::get(), SIGNAL(logSignal()), this, SLOT(DebugSlot()));
    connect(SignalLinker::get(), SIGNAL(settingsSignal()), this, SLOT(SettingsSlot()));
    connect(SignalLinker::get(), SIGNAL(infoSignal()), this, SLOT(InfoSlot()));
    connect(SignalLinker::get(), SIGNAL(emulatorSignal()), this, SLOT(EmulatorSlot()));


    // data types here
    qmlRegisterSingletonInstance<DataTelemetry>("Telemetry", 1, 0, "Telemetry", DataTelemetry::get(this));
    qmlRegisterSingletonInstance<DataSAR>("SAR", 1, 0, "SAR", DataSAR::get(this));
    qmlRegisterSingletonInstance<DataFormParameters>("FormParameters", 1, 0, "FormParameters", DataFormParameters::get(this));

    // get resolution for some ui rescaling and start new log in debug

    screenResolution = QGuiApplication::primaryScreen()->availableGeometry();
    qmlRegisterSingletonInstance<Theme>("Theme", 1, 0, "Theme", Theme::get(this));
    Theme::get()->setWindowDimension(screenResolution.width(), screenResolution.height());

    // qml ux/ui setup
    qmlRegisterSingletonInstance<DialogWindowBackend>("DialogWindowBackend", 1, 0, "DialogWindowBackend", DialogWindowBackend::get());
    qmlRegisterSingletonInstance<MarkerWindowBackend>("MarkerWindowBackend", 1, 0, "MarkerWindowBackend", MarkerWindowBackend::get());
    qmlRegisterSingletonInstance<AutocaptureMarkWindowBackend>("AutocaptureMarkWindowBackend", 1, 0, "AutocaptureMarkWindowBackend", AutocaptureMarkWindowBackend::get());
    qmlRegisterSingletonInstance<SettingsWindowBackend>("SettingsWindowBackend", 1, 0, "SettingsWindowBackend", SettingsWindowBackend::get());
    qmlRegisterSingletonInstance<FocusWindowBackend>("FocusWindowBackend", 1, 0, "FocusWindowBackend", FocusWindowBackend::get());

    // qml base setup
    ui->map->rootContext()->setContextProperty("OsmConfigPath", CacheManager::getMapProviderCache());
    ui->map->setSource(QUrl("qrc:/qml/CoreQML.qml"));
    ui->map->show();

    // declare only-header qml types here
    qmlRegisterType<ApplicationHeader>("ApplicationHeader", 1, 0, "ApplicationHeader");

    // qml header setup
    ui->applicationHeader->setSource(QUrl("qrc:/qml/application-header/ApplicationHeader.qml")); 
    ui->applicationHeader->show();
    qml = ui->map->rootObject();
    QMetaObject::invokeMethod(qml, "qmlBackendStart");

    // debug logging misc code
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());

    qDebug() << "[CORE] UI initialization finished";
    qInfo() << "[CORE] Session started at " << localTime;

    // openssl check
    QString ssl1 = QSslSocket::supportsSsl() ? "true" : "false";

    if (QSslSocket::supportsSsl())
    {
        qInfo() << "[CORE] OpenSSL detected: " << ssl1 << ", OpenSSL build version: " << QSslSocket::sslLibraryBuildVersionString()
                << ", OpenSSL ver.: " << QSslSocket::sslLibraryVersionString();
    }
    else
    {
        qCritical() << "[CORE] OpenSSL detected: " << ssl1 << ", OpenSSL build version: " << QSslSocket::sslLibraryBuildVersionString()
                    << ", OpenSSL ver.: " << QSslSocket::sslLibraryVersionString();
        QMessageBox openSSLDialogue;
        openSSLDialogue.setWindowTitle("Библиотека OpenSSL не обнаружена!");
        openSSLDialogue.setIcon(QMessageBox::Critical);
        openSSLDialogue.setText("Попробуйте переустановить программу.");
        openSSLDialogue.exec(); //? @TODO: maybe to qml?
    }

    // core
    // (!) do not touch it.

    qInfo() << "[CORE] Setuping connections...";

    LinkerQML::get(qml);
    connect(LinkerQML::get(), SIGNAL(signalReconnect()), this, SLOT(reconnectSlot()));
    connect(LinkerQML::get(), SIGNAL(signalDisconnect()), this, SLOT(disconnectSlot()));

    // ui misc initialization and assignment
    RuntimeData::get()->setSARIP("(" + SConfig::get()->getNetworkType() + ") " + SConfig::get()->getDE10IP());
    RuntimeData::get()->setPCIP(SConfig::get()->getComputerIP());
    RuntimeData::get()->setTelemetryPort(SConfig::get()->getTelemetryPort());
    RuntimeData::get()->setLoaderPort(SConfig::get()->getLoaderPort());
    RuntimeData::get()->setCommandPort(SConfig::get()->getExecdPort());
    RuntimeData::get()->setListenPort(SConfig::get()->getTerminalPort());
    RuntimeData::get()->setLoaderStatus("Oжидание подключения..."); //TODO: remove me 
    RuntimeData::get()->setFormStatus("Oжидание подключения...");

    // startup functions
    RuntimeData::get()->setConnected(false);

    qDebug() << "[CORE] Connections set up successfully";

    // emulator
    this->installEventFilter(this);
    flightEmulator = new FlightEmulator(this);

    // plugin system setup
        HostAPI = new PluginHostAPI;
        QObject* runtimeData = RuntimeData::get();
        HostAPI->addData("Host.runtimeData", (void*) runtimeData, sizeof(runtimeData));
        HostAPI->parseConfig(SConfig::get(), "appconfig/config2.ini");
        // Отсюда начинается процедура добавления плагина
        // Тут можно значения из конфига передавать для автозагрузки
        QString postfix;
        #ifdef __linux__
            postfix = ".so";
        #elif _WIN32
            postfix = ".dll";
        #else
            qCritical() << "[CORE] Your operating system is not supported.";
        #endif
        QString terminalPath = CacheManager::getPluginsCache() + "/terminal" + postfix;
        PluginInterface *terminalInterface = (PluginInterface *)LoadPlugin(terminalPath);
        if(!terminalInterface){
           plugins.terminalLoaded = false;

        qWarning() << "[CORE] Failed to load terminal plugin. Check your directory (app-plugins).";

        } else {
            plugins.terminalLoaded = true;
            plugins.terminal = terminalInterface->GetWidget();
            QDockWidget* titleReset = (QDockWidget*)plugins.terminal;
            titleReset->setTitleBarWidget(new QWidget(plugins.terminal));
            ui->terminalLayout->addWidget(plugins.terminal);
            
            //execute
            HostAPI->execute("Terminal", "print", "Ожидание вывода с РЛС...\n");
        }

    // network setup (must be after plugins setup 4 many reasons)
    telemetryRemote = new TelemetryRemote(this);
    feedBackRemote = new FeedbackRemote(this, HostAPI);
    execdRemote = new ExecdRemote(this);
    downloader = new TCPDownloader(this);
    connect(downloader, SIGNAL(progressChanged(float)), this, SLOT(updateProgress(float)));

    // sar commands setup
    connect(SignalLinker::get(), SIGNAL(clearSARStorageSignal()), execdRemote, SLOT(executeClearCommand())); 
    connect(SignalLinker::get(), SIGNAL(formSingleImageSignal()), execdRemote, SLOT(executeFormCommand()));
    connect(SignalLinker::get(), SIGNAL(focusSignal()), execdRemote, SLOT(executeFocusCommand()));
    connect(SignalLinker::get(), SIGNAL(reformSignal()), execdRemote, SLOT(executeFormCommand()));

    // autocapture setup
    connect(RuntimeData::get(), SIGNAL(autocaptureSignal()), execdRemote, SLOT(executeFormCommand())); 
    
    // set default position and size of floating qdockwidgets
    ui->debugConsole->setEnabled(false);
    ui->debugConsole->setVisible(false);
    if(plugins.terminalLoaded) 
    {
        plugins.terminal->setEnabled(true);
        plugins.terminal->setVisible(true);
        ui->sarConsole->setEnabled(false);
        ui->sarConsole->setVisible(false);
    }

    // qss only after plugins loaded
    Theme::get()->setQWidgetsStylesheet();

    // execute any other startup code here
    RuntimeData::get()->statusPopupSet("Версия программы " +
                                        SText::colorText(SConfig::get()->getProjectVersion(), Theme::get()->color("accent")));
    RuntimeData::get()->statusPopupTriggerSet(true); //TODO: make it separate class
    RuntimeData::get()->infoWindowSet(false);
}

CoreUI::~CoreUI()
{
    qInfo() << "[CORE] Ending current session...";
    uiReady = false;
    delete ui;
    delete TilesManager::get();
    delete ImageManager::get();
    delete MarkerManager::get();
    qInfo() << "[CORE] Session ended succesfully.";
}

void* CoreUI::LoadPlugin(QString path)
{
    QPluginLoader *pluginLoader = new QPluginLoader(path);
    QObject *plugin = pluginLoader->instance();
    if(!plugin){
        pluginLoader->unload(); qCritical()<<pluginLoader->errorString();
        delete pluginLoader;
        return nullptr;
    }
    PluginInterface *pluginInterface = qobject_cast<PluginInterface*>(plugin);
    pluginInterface->Init(this, (QObject*)SConfig::get(), HostAPI);
    return pluginInterface;
}

void CoreUI::debugStreamUpdate(QString _text, int msgtype)
{
    if(Theme::get() != nullptr and QGuiApplication::instance() != nullptr and uiReady)
    {
        if (msgtype == 0) { ui->debugConsole->setTextColor(Theme::get()->color("light1")); }
        else if (msgtype == 1) { ui->debugConsole->setTextColor(Theme::get()->color("color3")); }
        else if (msgtype == 2) { ui->debugConsole->setTextColor(Theme::get()->color("yellow")); }
        else if (msgtype == 3) { ui->debugConsole->setTextColor(Theme::get()->color("red")); }
        else if (msgtype == 4) { ui->debugConsole->setTextColor(Theme::get()->color("red")); }
        QFont consoleFont = ui->debugConsole->font();
        consoleFont.setPointSize(8);
        ui->debugConsole->append(_text);
        ui->debugConsole->setTextColor(Qt::white);
        ui->debugConsole->setFont(consoleFont);
        QTextCursor m_cursor = ui->debugConsole->textCursor();
        m_cursor.movePosition(QTextCursor::End);
        ui->debugConsole->setTextCursor(m_cursor);
    }
}

void CoreUI::updateProgress(float f)
{
    if (f > 0)
    {
        RuntimeData::get()->setFormStatus("Загрузка изображения...");
    }
    if (f > 99)
    {
        execdRemote->sendCommand(ExecdCommand::StorageStatus);
        RuntimeData::get()->setFormStatus("Изображение отображено на карте");
        if(DataFormParameters::get()->getFormingContinuous())
        {
            execdRemote->sendCommand(ExecdCommand::FormImage);
        }
    }
//    ui->progressBar_loader->setValue((int)f);
}

void CoreUI::MinimizeSlot()
{ 
    showMinimized(); 
}
void CoreUI::CloseSlot()
{
    LinkerQML::callDestructor();
    QApplication::quit();
}
void CoreUI::SettingsSlot()
{
    PasswordDialog passwordDialog(this, SConfig::get()->getSudoPassword());
    if (passwordDialog.exec() == QDialog::Accepted)
    {
        if (passwordDialog.passwordCheck || SConfig::get()->getSudoPassword().isEmpty())
        {
            SettingsDialog sd(this);
            QString s = SConfig::get()->getDefaultCatalogue();
            if (sd.exec() == QDialog::Accepted)
            {
                if (s != SConfig::get()->getDefaultCatalogue())
                    DiskTools::fetchDirectory();
                else
                    qInfo() << "[CORE] Path unchanged, no further scans";
                SConfig::get()->saveSettings();
            }
            else
                SConfig::get()->loadSettings();
            RuntimeData::get()->setSARIP("(" + SConfig::get()->getNetworkType() + ") " + SConfig::get()->getDE10IP());
            RuntimeData::get()->setPCIP(SConfig::get()->getComputerIP());
            RuntimeData::get()->setTelemetryPort(SConfig::get()->getTelemetryPort());
            RuntimeData::get()->setLoaderPort(SConfig::get()->getLoaderPort());
            RuntimeData::get()->setCommandPort(SConfig::get()->getExecdPort());
            RuntimeData::get()->setListenPort(SConfig::get()->getTerminalPort());
        }
        else
        {
            RuntimeData::get()->statusPopupSet("Был введен " + SText::colorText("неверный пароль.", Theme::get()->color("red")));
            RuntimeData::get()->statusPopupTriggerSet(true);
        }
    }
}

void CoreUI::InfoSlot()
{
    RuntimeData::get()->infoWindowSet(!RuntimeData::get()->infoWindow());
    RuntimeData::get()->windowLockSet(true);
}
void CoreUI::EmulatorSlot()    
{ 
    RuntimeData::get()->setEmulatorEnabled(!RuntimeData::get()->getEmulatorEnabled()); 
    if(RuntimeData::get()->getEmulatorEnabled())
        flightEmulator->startEmulator();
    else
        flightEmulator->stopEmulator(); 
}
void CoreUI::DebugSlot()
{
    bool isEnabled = ui->debugConsole->isEnabled();
    ui->debugConsole->setEnabled(!isEnabled);
    ui->debugConsole->setVisible(!isEnabled);
}

bool CoreUI::eventFilter(QObject * obj, QEvent * event)
{
    if ( event->type() == QEvent::KeyPress ) {
        pressedKeys += (static_cast<QKeyEvent*>(event))->key();
        if(RuntimeData::get()->getEmulatorEnabled())
        {
            if ( pressedKeys.contains(Qt::Key_W) || pressedKeys.contains(1062) ) { flightEmulator->pitchChange(-1); }
            if ( pressedKeys.contains(Qt::Key_S) || pressedKeys.contains(1067)) { flightEmulator->pitchChange(1); }
            if ( pressedKeys.contains(Qt::Key_A) || pressedKeys.contains(1060)) { flightEmulator->yawChange(-1); }
            if ( pressedKeys.contains(Qt::Key_D) || pressedKeys.contains(1042)) { flightEmulator->yawChange(1); }
            if ( pressedKeys.contains(Qt::Key_Q) || pressedKeys.contains(1049)) { flightEmulator->rollChange(-1); 
                    SAROutputConsoleEmulator feedbackEmulator;
                    feedbackEmulator.sampleTest(); }
            if ( pressedKeys.contains(Qt::Key_E) || pressedKeys.contains(1059)) { flightEmulator->rollChange(1); }
            if ( pressedKeys.contains(Qt::Key_Z) || pressedKeys.contains(1071)) { flightEmulator->throttleChange(1); }
            if ( pressedKeys.contains(Qt::Key_X) || pressedKeys.contains(1063)) { flightEmulator->throttleChange(-1); }
        }
        if(static_cast<QKeyEvent*>(event)->modifiers() == Qt::ShiftModifier)
        {
            if(pressedKeys.contains(Qt::Key_Delete)) { LinkerQML::clearRoute(); pressedKeys.clear(); }
        }
        else if(static_cast<QKeyEvent*>(event)->modifiers() == Qt::AltModifier)
        {
            if(pressedKeys.contains(Qt::Key_V) || pressedKeys.contains(1052)) { DebugSlot(); pressedKeys.clear(); }
            if(pressedKeys.contains(Qt::Key_J) || pressedKeys.contains(1054)) { LinkerQML::get()->disconnect(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_O) || pressedKeys.contains(1065)) { SettingsSlot(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_Y) || pressedKeys.contains(1053)) { InfoSlot(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_U) || pressedKeys.contains(1043)) { QString pathNotNullCheck = QFileDialog::getExistingDirectory(this, 
                                                    tr("Выберите папку c выходными изображениями РЛС"), QStandardPaths::displayName(
                                                    QStandardPaths::HomeLocation)); if(pathNotNullCheck != NULL) {
                                                    SConfig::get()->setDefaultCatalogue(pathNotNullCheck); }
                                                    pressedKeys.clear(); }
        }
        else 
        {
            if(pressedKeys.contains(Qt::Key_J) || pressedKeys.contains(1054)) { LinkerQML::get()->reconnect(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_M) || pressedKeys.contains(1068)) { RuntimeData::get()->setMouseState(1); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_I) || pressedKeys.contains(1064)) { LinkerQML::panImage(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_P) || pressedKeys.contains(1047)) { LinkerQML::panGPS(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_U) || pressedKeys.contains(1043)) { DiskTools::fetchDirectory(); pressedKeys.clear(); }
            if(pressedKeys.contains(Qt::Key_Space)) { execdRemote->sendCommand(ExecdCommand::FormImage); pressedKeys.clear(); }
            if (pressedKeys.contains(Qt::Key_Escape))
            {
                RuntimeData::get()->closeAllWindows();
                if (DialogWindowBackend::get()->getShown())
                DialogWindowBackend::get()->cancel();
            }
            if (pressedKeys.contains(Qt::Key_Return))
            {
                RuntimeData::get()->closeAllWindows();
                if (DialogWindowBackend::get()->getShown())
                DialogWindowBackend::get()->accept();
            }
        }
        return 1;
    }
    else if ( event->type() == QEvent::KeyRelease ) { pressedKeys -= (static_cast<QKeyEvent*>(event))->key(); return 1; }
    else
        return QObject::eventFilter(obj, event);
    return false;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::reconnectSlot()
{
    RuntimeData::get()->setConnected(false);
    telemetryRemote->connect(SConfig::get()->getDE10IP(), SConfig::get()->getTelemetryPort().toUInt(), SConfig::get()->getTelemetryFrequency());
    feedBackRemote->connect(SConfig::get()->getComputerIP(), SConfig::get()->getTerminalPort().toUInt());
    if(SConfig::get()->getDE10IP().endsWith("48") and USE_JETSON_IP_IN_CONFIG_FOR_TELEMETRY) {
            QString correctedSarIP = SConfig::get()->getDE10IP();
            correctedSarIP.chop(1); correctedSarIP.append("7");
            execdRemote->connect(correctedSarIP, SConfig::get()->getExecdPort().toUInt());

            qWarning() << "[CORE] Sending commands to autocorrected address: " << correctedSarIP + ":" << SConfig::get()->getExecdPort();
        } else { 
            execdRemote->connect(SConfig::get()->getDE10IP(), SConfig::get()->getExecdPort().toUInt());

            qInfo() << "[CORE] Sending commands to address: " << SConfig::get()->getDE10IP() << ":" << SConfig::get()->getExecdPort();
        }
    execdRemote->sendCommand(ExecdCommand::StorageStatus);

    qInfo() << "[CORE] All remotes connected";
}
void CoreUI::disconnectSlot()
{
    telemetryRemote->disconnect();
    feedBackRemote->disconnect();
    execdRemote->disconnect();
    RuntimeData::get()->setConnected(false);

    qInfo() << "[CORE] All remotes disconnected";
}
