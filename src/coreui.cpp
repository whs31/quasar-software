#include "coreui.h"
#include "ui_coreui.h"
#include "buildprefs.h"

CoreUI *CoreUI::debugPointer;
QRect CoreUI::screenResolution;
CoreUI::CoreUI(QWidget *parent) : QMainWindow(parent),
                                  ui(new Ui::CoreUI)
{
    debugPointer = this;
    // cache setup
    CacheManager::initializeCache(this);

    // qml registration here
    qmlRegisterType<SMath>("SMath", 1, 0, "SMath");
    qmlRegisterType<FMouseKeyHandler>("MouseKeyHandler", 1, 0, "MouseKeyHandler");
    qmlRegisterSingletonInstance<MarkerManager>("MarkerManager", 1, 0, "MarkerManager", MarkerManager::initialize());
    qmlRegisterSingletonInstance<ImageManager>("ImageManager", 1, 0, "ImageManager", ImageManager::initialize(this));
    qmlRegisterSingletonInstance<DiskTools>("DiskManager", 1, 0, "DiskManager", DiskTools::initialize(this));
    
    // ux and tiles must be called before ui initialization
    UXManager::initialize(this, CacheManager::getSettingsPath());
    TilesManager::initialize(   );
    ThemeManager::get(this, THEME_SETTING_ON_BUILD);
    
    // get resolution for some ui rescaling and start new log in debug
    screenResolution = QGuiApplication::primaryScreen()->availableGeometry();
    Debug::NewSession();

    // ui setup. do not call any unintentional code before ui is initialized (uiReady == true)
    ui->setupUi(this);
    uiReady = true;
    Debug::Log("[STARTUP] Starting UI initialization...");

    // config
    qmlRegisterSingletonInstance("Config", 1, 0, "Config", SConfig::get());
    if (SConfig::get()->getOnlineMaps())
        Debug::Log("[STARTUP] Using ONLINE map tileserver");
    else
        Debug::Log("[STARTUP] Using OFFLINE map tileserver");

    // qml types that require SConfig declared here
    qmlRegisterSingletonInstance<RuntimeData>("RuntimeData", 1, 0, "RuntimeData", RuntimeData::initialize(this));
    qmlRegisterType<RecallHandler>("RecallHandler", 1, 0, "RecallHandler");
    qmlRegisterType<FlightPrediction>("FlightPrediction", 1, 0, "Predict");
    
    // signal linker setup
    qmlRegisterSingletonInstance<SignalLinker>("SignalLinker", 1, 0, "SignalLinker", SignalLinker::get(this));
    connect(SignalLinker::get(), SIGNAL(closeSignal()), this, SLOT(CloseSlot()));
    connect(SignalLinker::get(), SIGNAL(minimizeSignal()), this, SLOT(MinimizeSlot()));
    connect(SignalLinker::get(), SIGNAL(logSignal()), this, SLOT(DebugSlot()));
    connect(SignalLinker::get(), SIGNAL(settingsSignal()), this, SLOT(SettingsSlot()));
    connect(SignalLinker::get(), SIGNAL(infoSignal()), this, SLOT(InfoSlot()));
    connect(SignalLinker::get(), SIGNAL(emulatorSignal()), this, SLOT(EmulatorSlot()));
    connect(SignalLinker::get(), SIGNAL(formSingleImageSignal()), this, SLOT(FormSingleImage()));
    //connect(RuntimeData::initialize(), SIGNAL(formContinuousSignal()), this, SLOT(FormContinuousImages()));

    // qml ux/ui setup
    qmlRegisterSingletonInstance<ThemeManager>("UX", 1, 0, "UX", ThemeManager::get());

    // qml base setup
    ui->map->rootContext()->setContextProperty("OsmConfigPath", CacheManager::getMapProviderCache());
    ui->map->setSource(QUrl("qrc:/qml/map.qml"));
    ui->map->show();

    // declare only-header qml types here
    qmlRegisterType<ApplicationHeader>("ApplicationHeader", 1, 0, "ApplicationHeader");

    // qml header setup
    ui->applicationHeader->setSource(QUrl("qrc:/qml/application-header/ApplicationHeader.qml")); //https://forum.qt.io/topic/71942/connect-two-qquickwidgets/2
    ui->applicationHeader->show();
    qml = ui->map->rootObject();
    QMetaObject::invokeMethod(qml, "qmlBackendStart");

    // debug logging misc code
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    Debug::Log("[STARTUP] UI initialization finished");
    Debug::Log("?[STARTUP] Session started at " + localTime.toString());

    // openssl check
    QString ssl1 = QSslSocket::supportsSsl() ? "true" : "false";
    if (QSslSocket::supportsSsl())
    {
        Debug::Log("?[STARTUP] OpenSSL detected: " 
                    + ssl1 
                    + ", OpenSSL build version: " 
                    + QSslSocket::sslLibraryBuildVersionString() 
                    + ", OpenSSL ver.: " 
                    + QSslSocket::sslLibraryVersionString());
    }
    else
    {
        Debug::Log("!!![STARTUP] OpenSSL detected: " 
                    + ssl1 
                    + ", OpenSSL build version: " 
                    + QSslSocket::sslLibraryBuildVersionString() 
                    + ", OpenSSL ver.: " 
                    + QSslSocket::sslLibraryVersionString());
        QMessageBox openSSLDialogue;
        openSSLDialogue.setWindowTitle("Библиотека OpenSSL не обнаружена!");
        openSSLDialogue.setIcon(QMessageBox::Critical);
        openSSLDialogue.setText("Попробуйте переустановить программу.");
        openSSLDialogue.exec();
    }

    // any other ui-related startup code here!

    // core
    // (!) do not touch it.
    Debug::Log("?[STARTUP] Setuping connections...");
    timer = new QTimer(this);
    udpTimeout = new QTimer(this);
    uiTimer1 = new QTimer(this);
    LinkerQML::initialize(qml);
    connect(LinkerQML::initialize(), SIGNAL(signalReconnect()), this, SLOT(reconnectSlot()));
    connect(LinkerQML::initialize(), SIGNAL(signalDisconnect()), this, SLOT(disconnectSlot()));

    // network setup
    telemetryRemote = new UDPRemote();
    formRemote = new UDPRemote();
    consoleListenerRemote = new UDPRemote();
    downloader = new TCPDownloader(this);
    connect(downloader, SIGNAL(progressChanged(float)), this, SLOT(updateProgress(float)));

    // network socket connections setup
    connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
    connect(udpTimeout, SIGNAL(timeout()), this, SLOT(Disconnected()));
    connect(telemetryRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    connect(formRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadForm(QByteArray)));
    connect(consoleListenerRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadSARConsole(QByteArray)));

    // sar commands setup
    connect(RuntimeData::initialize(), SIGNAL(clearSARDiskSignal()), this, SLOT(SendClearCommand()));

    // ui misc initialization and assignment
    RuntimeData::initialize()->setSARIP("(" + SConfig::get()->getNetworkType() + ") " + SConfig::get()->getDE10IP());
    RuntimeData::initialize()->setPCIP(SConfig::get()->getComputerIP());
    RuntimeData::initialize()->setTelemetryPort(SConfig::get()->getTelemetryPort());
    RuntimeData::initialize()->setLoaderPort(SConfig::get()->getLoaderPort());
    RuntimeData::initialize()->setCommandPort(SConfig::get()->getExecdPort());
    RuntimeData::initialize()->setListenPort(SConfig::get()->getTerminalPort());
    RuntimeData::initialize()->setLoaderStatus("Oжидание подключения...");
    RuntimeData::initialize()->setFormStatus("Oжидание подключения...");

    // autocapture setup
    connect(RuntimeData::initialize(), SIGNAL(autocaptureSignal()), this, SLOT(FormSingleImage()));

    // timers starts here
    timer->start(SConfig::get()->getTelemetryFrequency() * 1000);
    udpTimeout->start(3 * SConfig::get()->getTelemetryFrequency() * 1000);

    // startup functions
    Disconnected();
    Debug::Log("[STARTUP] Connections set up successfully");

    // emulator
    this->installEventFilter(this);
    flightEmulator = new FlightEmulator(this);

    // plugin system setup
        HostAPI = new PluginHostAPI;
        QObject* runtimeData = RuntimeData::initialize();
        HostAPI->addData("Host.runtimeData", (void*) runtimeData, sizeof(runtimeData));
        // Отсюда начинается процедура добавления плагина
        // Тут можно значения из конфига передавать для автозагрузки
        QString postfix;
        #ifdef __linux__
            postfix = ".so";
        #elif _WIN32
            postfix = ".dll";
        #else
            Debug::Log("!![PLUGIN] Your operating system is not supported.");
        #endif
        QString terminalPath = CacheManager::getPluginsCache()+"/terminal" + postfix;
        PluginInterface *terminalInterface = (PluginInterface *)LoadPlugin(terminalPath); qCritical()<<terminalPath;
        if(!terminalInterface){
           plugins.terminalLoaded = false;
           Debug::Log("![PLUGIN] Failed to load terminal plugin. Check your directory (app-plugins).");
        } else {
            plugins.terminalLoaded = true;
            plugins.terminal = terminalInterface->GetWidget();
            QDockWidget* titleReset = (QDockWidget*)plugins.terminal;
            titleReset->setTitleBarWidget(new QWidget(plugins.terminal));
            ui->terminalLayout->addWidget(plugins.terminal);
            
            //execute
            HostAPI->execute("Terminal", "print", "Ожидание вывода с РЛС...\n");
        }

    // set default position and size of floating qdockwidgets
    ui->debugConsole->setEnabled(false);
    ui->debugConsole->setVisible(false);
    if(plugins.terminalLoaded) 
    {
        plugins.terminal->setEnabled(true);
        plugins.terminal->setVisible(true);
        ui->sarConsole->setEnabled(false);
        ui->sarConsole->setVisible(false);
        plugins.terminal->setStyleSheet("QFrame { \nbackground-color: #121617;\n  color: #121617;\n  border: 1px solid #121617;\n}");
    }

    // qss only after plugins loaded
    Style::initialize(this, ENABLE_CSS_UPDATE_ON_CHANGE);

    // execute any other startup code here
}

CoreUI::~CoreUI()
{
    uiReady = false;
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    consoleListenerRemote->Disconnect();

    delete ui;
    delete telemetryRemote;
    delete formRemote;
    delete consoleListenerRemote;
    delete qml;
    delete TilesManager::initialize();
    delete ImageManager::initialize();
    delete MarkerManager::initialize();
    delete Style::initialize();
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
    PluginInterface *pluginInterface = qobject_cast<PluginInterface *>(plugin);
    pluginInterface->Init(this, (QObject*)SConfig::get(), HostAPI);
    return pluginInterface;
}

CoreUI *CoreUI::getDebugPointer(void)   { return debugPointer; }
void CoreUI::debugStreamUpdate(QString _text, int msgtype)
{
    if (!uiReady)
        return;
    if (msgtype == 0) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Text100, true)); }
    else if (msgtype == 1) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Info200, true)); }
    else if (msgtype == 2) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Warning100, true)); }
    else if (msgtype == 3) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Error200, true)); }
    else if (msgtype == 4) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Error100, true)); }
    QFont consoleFont = ui->debugConsole->font();
    consoleFont.setPointSize(8);
    ui->debugConsole->insertPlainText(_text);
    ui->debugConsole->setTextColor(Qt::white);
    ui->debugConsole->setFont(consoleFont);
    QTextCursor m_cursor = ui->debugConsole->textCursor();
    m_cursor.movePosition(QTextCursor::End);
    ui->debugConsole->setTextCursor(m_cursor);
}

bool CoreUI::getReady(void)             { return uiReady; }
QQuickItem *CoreUI::getMapPointer(void) { return qml; }
void CoreUI::Connected()                { RuntimeData::initialize()->setConnected(true); }
void CoreUI::Disconnected()             { RuntimeData::initialize()->setConnected(false); }
void CoreUI::updateProgress(float f)
{
    if (f > 0)
    {
        RuntimeData::initialize()->setFormStatus("Загрузка изображения...");
    }
    if (f > 99)
    {
        RuntimeData::initialize()->setFormStatus("Изображение отображено на карте");
        if(RuntimeData::initialize()->getFormingContinuous())
        {
            FormSingleImage();
            QString request = MessageParser::makeCommand(Command::StorageStatus);
            SendRemoteCommand(request, CommandType::FormCommand);
            Debug::Log("[FORM] Sended to SAR: " + request);
        }
    }
//    ui->progressBar_loader->setValue((int)f);
}

void CoreUI::SendRemoteCommand(QString command, CommandType type)
{
    if (type == CommandType::TelemetryCommand)
        telemetryRemote->Send(command.toUtf8());
    else if (type == CommandType::FormCommand)
        formRemote->Send(command.toUtf8());
}

void CoreUI::MinimizeSlot()     { showMinimized(); }
void CoreUI::CloseSlot()   { QApplication::quit(); }
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
                    Debug::Log("?[CONFIG] Path unchanged, no further scans");
                SConfig::get()->saveSettings();
            }
            else
                SConfig::get()->loadSettings();
            RuntimeData::initialize()->setSARIP("(" + SConfig::get()->getNetworkType() + ") " + SConfig::get()->getDE10IP());
            RuntimeData::initialize()->setPCIP(SConfig::get()->getComputerIP());
            RuntimeData::initialize()->setTelemetryPort(SConfig::get()->getTelemetryPort());
            RuntimeData::initialize()->setLoaderPort(SConfig::get()->getLoaderPort());
            RuntimeData::initialize()->setCommandPort(SConfig::get()->getExecdPort());
            RuntimeData::initialize()->setListenPort(SConfig::get()->getTerminalPort());
        }
        else
        {
            QMessageBox passwordWarning;
            passwordWarning.setWindowTitle("Ошибка");
            passwordWarning.setIcon(QMessageBox::Critical);
            passwordWarning.setText("Неверный пароль.");
            passwordWarning.setStandardButtons(QMessageBox::Yes);
            passwordWarning.setDefaultButton(QMessageBox::Yes);
            passwordWarning.exec();
        }
    }
}

void CoreUI::InfoSlot()        { AboutDialog aboutDialog(this, PROJECT_VERSION); aboutDialog.exec(); }
void CoreUI::EmulatorSlot()    
{ 
    RuntimeData::initialize()->setEmulatorEnabled(!RuntimeData::initialize()->getEmulatorEnabled()); 
    if(RuntimeData::initialize()->getEmulatorEnabled())
        flightEmulator->startEmulator();
    else
        flightEmulator->stopEmulator(); 
}
void CoreUI::DebugSlot()
{
    bool state = ui->debugConsole->isEnabled();
    state = !state;
    ui->debugConsole->setEnabled(state);
    ui->debugConsole->setVisible(state);
}

void CoreUI::ReadTelemetry(QByteArray data)
{
    udpTimeout->start(3 * SConfig::get()->getTelemetryFrequency() * 1000);
    DataType dtype = MessageParser::checkReceivedDataType(data);
    switch (dtype)
    {
    case DataType::Telemetry: {
        short _conckc2 = (short)0;
        QPair<qreal, qint16> pair = MessageParser::parseTelemetry(data);
        _conckc = pair.first;
        _conckc2 = pair.second;
        linker->fixedUpdate();
        if ((short)_conckc2 != 0 || _conckc != pair.first)
            Connected();
        else 
            Disconnected();
        break;
    }
    case DataType::FormResponse: {
        std::array<int, 4> responseList;
        responseList = MessageParser::parseFormResponse(data);
        if (!responseList.empty())
        {
            QString checksumCheck = (responseList[3] == 1) ? "success" : "failure";
            Debug::Log("?[FORM] SAR responds with: pid " + QString::number(responseList[0]) + ", hexlen " + QString::number(responseList[1]) + ", code" + QString::number(responseList[2]) + " with checksum check " +
                       checksumCheck);
        }
        break;
    }
    default: { break; }
    }
}

void CoreUI::ReadSARConsole(QByteArray data)
{
    if(plugins.terminalLoaded)
    {
        HostAPI->execute("Terminal", "print", data);
    } else {
    QString dataStr = data.data();
    dataStr.replace(QRegExp("[\r]"), "");
    QStringList dataParsed = dataStr.split(QRegExp("[\n]"));
    for (QString str : dataParsed)
        ui->sarConsole->append(str);
    }
    DataType dtype = MessageParser::checkReceivedDataType(data);
    if(dtype == DataType::CommandResponse_FreeDiskSpace)
    {
        Debug::Log("[SAR] SAR responds with: " + data);
        QStringList _split;
        QString dataStr = data.data();
        dataStr.remove("FREE_DISK_SPACE ");
        _split = dataStr.split(' ', Qt::SkipEmptyParts);
        qCritical()<<_split;
        RuntimeData::initialize()->setFreeDiskSpace(_split.first().toInt());
        RuntimeData::initialize()->setTotalDiskSpace(_split.last().toInt());
    }
}

void CoreUI::ReadForm(QByteArray data)
{
    DataType dtype = MessageParser::checkReceivedDataType(data);
    switch (dtype)
    {
    case DataType::Telemetry: { break; }
    case DataType::FormResponse:
        std::array<int, 4> responseList;
        responseList = MessageParser::parseFormResponse(data);
        if (!responseList.empty())
        {
            QString checksumCheck = (responseList[3] == 1) ? "success" : "failure";
            Debug::Log("?[FORM] SAR responds with: pid " + QString::number(responseList[0]) + ", hexlen " 
                        + QString::number(responseList[1]) + ", code" + QString::number(responseList[2]) 
                        + " with checksum check " + checksumCheck);
            RuntimeData::initialize()->setFormStatus("Получен ответ от РЛС");
        }
        break;
    default: 
    {
        break;
    }
    }
}

// вызывается раз в SConfig::UPDATETIME (обычно 0.5 сек)
// эта же функция вызывает обновление fixedUpdate в qml (только если пришел ответ от сервера телеметрии)
void CoreUI::Halftime()     { SendRemoteCommand(MessageParser::REQUEST_TELEMETRY, CommandType::TelemetryCommand); }
bool CoreUI::eventFilter(QObject * obj, QEvent * event)
{
    if ( event->type() == QEvent::KeyPress ) {
        pressedKeys += (static_cast<QKeyEvent*>(event))->key();
        if(RuntimeData::initialize()->getEmulatorEnabled())
        {
            if ( pressedKeys.contains(Qt::Key_W) || pressedKeys.contains(1062) ) { flightEmulator->pitchChange(-1); }
            if ( pressedKeys.contains(Qt::Key_S) || pressedKeys.contains(1067)) { flightEmulator->pitchChange(1); }
            if ( pressedKeys.contains(Qt::Key_A) || pressedKeys.contains(1060)) { flightEmulator->yawChange(-1); }
            if ( pressedKeys.contains(Qt::Key_D) || pressedKeys.contains(1042)) { flightEmulator->yawChange(1); }
            if ( pressedKeys.contains(Qt::Key_Q) || pressedKeys.contains(1049)) { flightEmulator->rollChange(-1); }
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
            if(pressedKeys.contains(Qt::Key_J) || pressedKeys.contains(1054)) { LinkerQML::initialize()->disconnect(); pressedKeys.clear();}
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
            if(pressedKeys.contains(Qt::Key_J) || pressedKeys.contains(1054)) { LinkerQML::initialize()->reconnect(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_M) || pressedKeys.contains(1068)) { RuntimeData::mouseState = MouseState::MarkerPlacement;pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_I) || pressedKeys.contains(1064)) { LinkerQML::panImage(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_P) || pressedKeys.contains(1047)) { LinkerQML::panGPS(); pressedKeys.clear();}
            if(pressedKeys.contains(Qt::Key_U) || pressedKeys.contains(1043)) { DiskTools::fetchDirectory(); pressedKeys.clear(); }
            if(pressedKeys.contains(Qt::Key_Space)) { FormSingleImage(); pressedKeys.clear();}
        }
        return 1;
    }
    else if ( event->type() == QEvent::KeyRelease ) { pressedKeys -= (static_cast<QKeyEvent*>(event))->key(); return 1; }
    else
        return QObject::eventFilter(obj, event);
    return false;
}

void CoreUI::SendClearCommand(void)
{
    Debug::Log("?[SAR] Clearing SAR storage...");
    QString request = MessageParser::makeCommand(Command::CacheClear);
            SendRemoteCommand(request, CommandType::FormCommand);
            Debug::Log("[FORM] Sended to SAR: " + request);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::reconnectSlot()
{
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    consoleListenerRemote->Disconnect();
    Disconnected();
    telemetryRemote->Connect(SConfig::get()->getDE10IP() + ":" + SConfig::get()->getTelemetryPort());
    if(SConfig::get()->getDE10IP().endsWith("48") && USE_JETSON_IP_IN_CONFIG_FOR_TELEMETRY == true) {
            QString correctedSarIP = SConfig::get()->getDE10IP();
            correctedSarIP.chop(1); correctedSarIP.append("7");
            formRemote->Connect(correctedSarIP + ":" + SConfig::get()->getExecdPort());
            Debug::Log("![REMOTE] Sending commands to autocorrected address: " + correctedSarIP + ":" + SConfig::get()->getExecdPort());
        } else { 
            formRemote->Connect(SConfig::get()->getDE10IP() + ":" + SConfig::get()->getExecdPort());
            Debug::Log("?[REMOTE] Sending commands to address: " + SConfig::get()->getDE10IP() + ":" + SConfig::get()->getExecdPort());
        }
    consoleListenerRemote->Connect(SConfig::get()->getComputerIP() + ":" + SConfig::get()->getTerminalPort());
    Debug::Log("?[REMOTE] Listening to SAR on " + SConfig::get()->getComputerIP() + ":" + SConfig::get()->getTerminalPort());
    if (SConfig::get()->getNetworkType() != "UDP")
    {
        SConfig::get()->getNetworkType() = "UDP";
        Debug::Log("![WARNING] Connection type string unrecognized, using UDP by default");
    }
    Debug::Log("?[REMOTE] UDP client connected");
    QString request = MessageParser::makeCommand(Command::StorageStatus);
            SendRemoteCommand(request, CommandType::FormCommand);
            Debug::Log("[FORM] Sended to SAR: " + request);
}
void CoreUI::disconnectSlot()
{
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    consoleListenerRemote->Disconnect();
    Disconnected();
    Debug::Log("?[REMOTE] All remotes disconnected.");
}
void CoreUI::FormSingleImage()
{
    QString request = MessageParser::makeFormRequest(RuntimeData::initialize()->getFormMode(), RuntimeData::initialize()->getFormLowerBound(),
                                                     RuntimeData::initialize()->getFormUpperBound(), RuntimeData::initialize()->getFormTime(),
                                                     RuntimeData::initialize()->getFormStep(), RuntimeData::initialize()->getFormStep(),
                                                     RuntimeData::initialize()->getFormOverrideGPSData(), RuntimeData::initialize()->getFormGPSHeight(),
                                                     RuntimeData::initialize()->getFormGPSVelocity());
    SendRemoteCommand(request, CommandType::FormCommand);
    Debug::Log("[FORM] Sended to SAR: " + request);
    RuntimeData::initialize()->setFormStatus("Отправлен запрос на формирование №" +
                                                               QString::number(MessageParser::getMessageID()));
}


//    Debug::Log("?[SAR] Sending custom command!");
//    QString request = MessageParser::makeCommand(ui->lineEdit_customCommand->text());
//    SendRemoteCommand(request, CommandType::FormCommand);
//    Debug::Log("[FORM] Sended to SAR: " + request);

