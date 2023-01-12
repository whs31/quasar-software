#include "coreui.h"
#include "ui_coreui.h"
#include "buildprefs.h"

CoreUI *CoreUI::debugPointer;
QRect CoreUI::screenResolution;
CoreUI::CoreUI(QWidget *parent) : QGoodWindow(parent),
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
    Style::initialize(this, ENABLE_CSS_UPDATE_ON_CHANGE);
    TilesManager::initialize(ENABLE_LOCALHOST_TILESERVER);
    
    // get resolution for some ui rescaling and start new log in debug
    screenResolution = QGuiApplication::screens().first()->availableGeometry();
    Debug::NewSession();

    // ui setup. do not call any unintentional code before ui is initialized (uiReady == true)
    ui->setupUi(this);

    // custom window frame setup
    setMargins(25, 0, 0, 200);
    ui->header->setTitleBarWidget(new QWidget());
    uiReady = true;
    Debug::Log("[STARTUP] Starting UI initialization...");

    // config
    SConfig::initialize(this);
    if (SConfig::getHashBoolean("UseOSM"))
        Debug::Log("![STARTUP] Program is running in test mode!");


    // qml types that require SConfig declared here
    qmlRegisterSingletonInstance<RuntimeData>("RuntimeData", 1, 0, "RuntimeData", RuntimeData::initialize(this));
    qmlRegisterType<IBackendIOHandler>("IOHandler", 1, 0, "IOHandler");
    qmlRegisterType<FlightPrediction>("FlightPrediction", 1, 0, "Predict");

    // qml base setup
    ui->map->rootContext()->setContextProperty("OsmConfigPath", CacheManager::getMapProviderCache());
    ui->map->setSource(QUrl("qrc:/qml/map.qml"));
    ui->map->show();
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
    ui->doubleSpinBox_height->setVisible(false);
    ui->doubleSpinBox_velocity->setVisible(false);

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
    downloader = new TCPDownloader(this, DowloaderMode::SaveAtDisconnect);
    connect(downloader, SIGNAL(progressChanged(float)), this, SLOT(updateProgress(float)));

    // network socket connections setup
    connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
    connect(udpTimeout, SIGNAL(timeout()), this, SLOT(Disconnected()));
    connect(telemetryRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    connect(formRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadForm(QByteArray)));
    connect(consoleListenerRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadSARConsole(QByteArray)));

    // network auto-connection on startup (deprecated)
    if (SConfig::getHashBoolean("StartupConnectToSAR"))
    {
        telemetryRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("TelemetryPort"));
        if(SConfig::getHashString("SarIP").endsWith("48") && USE_JETSON_IP_IN_CONFIG_FOR_TELEMETRY == true)
        {
            QString correctedSarIP = SConfig::getHashString("SarIP");
            correctedSarIP.chop(1); correctedSarIP.append("7");
            formRemote->Connect(correctedSarIP + ":" + SConfig::getHashString("DialogPort"));
        } else { 
            formRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("DialogPort")); 
        }
        consoleListenerRemote->Connect(SConfig::getHashString("LoaderIP") + ":" + SConfig::getHashString("ListenPort"));
        Debug::Log("?[REMOTE] Listening to SAR on " + SConfig::getHashString("LoaderIP") + ":" + SConfig::getHashString("ListenPort"));
        if (SConfig::getHashString("NetworkType") != "UDP")
        {
            SConfig::getHashString("NetworkType") = "UDP";
            Debug::Log("![WARNING] Connection type string unrecognized, using UDP by default");
        }
        Debug::Log("?[REMOTE] Connections ready.");
    }

    // ui misc initialization and assignment
    RuntimeData::initialize()->setSARIP("(" + SConfig::getHashString("NetworkType") + ") " + SConfig::getHashString("SarIP"));
    RuntimeData::initialize()->setPCIP(SConfig::getHashString("LoaderIP"));
    RuntimeData::initialize()->setTelemetryPort(SConfig::getHashString("TelemetryPort"));
    RuntimeData::initialize()->setLoaderPort(SConfig::getHashString("LoaderPort"));
    RuntimeData::initialize()->setCommandPort(SConfig::getHashString("DialogPort"));
    RuntimeData::initialize()->setListenPort(SConfig::getHashString("ListenPort"));
    RuntimeData::initialize()->setLoaderStatus("ожидание подключения");

    // timers starts here
    timer->start(SConfig::getHashFloat("TelemetryFrequency") * 1000);
    udpTimeout->start(3 * SConfig::getHashFloat("TelemetryFrequency") * 1000);

    // startup functions
    Disconnected();
    Debug::Log("[STARTUP] Connections set up successfully");

    // emulator
    this->installEventFilter(this);
    flightEmulator = new FlightEmulator(this);

    // plugin system setup
        QHash<QString, QVariant>* config = SConfig::getHashTable();
        HostAPI = new PluginHostAPI;
        QObject* runtimeData = RuntimeData::initialize();
        HostAPI->addData("Host.runtimeData", (void*) runtimeData, sizeof(runtimeData));
        // Отсюда начинается процедура добавления плагина
        // Тут можно значения из конфига передавать для автозагрузки
        QPluginLoader *terminalPluginLoader = new QPluginLoader(CacheManager::getPluginsCache()+"/libTerminal.so");
        QObject *terminalPlugin = terminalPluginLoader->instance();
        if(!terminalPlugin){
           terminalPluginLoader->unload();
           delete terminalPluginLoader;
           plugins.terminalLoaded = false;
           Debug::Log("![PLUGIN] Failed to load terminal plugin. Check your directory (app-plugins).");
        } else {
            PluginInterface *pluginInterface = qobject_cast<PluginInterface *>(terminalPlugin);
            pluginInterface->Init(this, config, HostAPI);
            this->addDockWidget(Qt::RightDockWidgetArea, (QDockWidget*) pluginInterface->GetWidget());
            plugins.terminalLoaded = true;
            plugins.terminal = pluginInterface->GetWidget();
            plugins.terminal->setWindowTitle("Терминал РЛС VT100");
            //execute
            HostAPI->execute("Terminal", "print", "Ожидание вывода с РЛС...\n");
        }

    // set default position and size of floating qdockwidgets
    InitializeDockwidgets();

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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CoreUI *CoreUI::getDebugPointer(void)   { return debugPointer; }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CoreUI::getReady(void) { return uiReady; }
QQuickItem *CoreUI::getMapPointer(void) { return qml; }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::Connected()
{
    connected = true;
    RuntimeData::initialize()->setConnected(connected);
}
void CoreUI::Disconnected()
{
    connected = false;
    RuntimeData::initialize()->setConnected(connected);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::updateProgress(float f)
{
    if (f > 0)
    {
        ui->label_c_loaderStatus->setText("Статус: " + Style::StyleText("приём данных", Colors::Accent100, Format::Italic));
        ui->label_c_formImageStatus->setText(Style::StyleText("загрузка изображения", Colors::Warning100, Format::NoFormat));
    }
    if (f > 99)
    {
        ui->label_c_loaderStatus->setText("Статус: " + Style::StyleText("изображение получено", Colors::Success100, Format::Italic));
        ui->label_c_formImageStatus->setText(Style::StyleText("изображение отображено на карте", Colors::Success100, Format::NoFormat));
        uiTimer1->start(5000);
    }
    ui->progressBar_loader->setValue((int)f);
    ui->progressBar_formImageStatus->setValue((int)(f / 2) + 50);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CoreUI::InitializeDockwidgets()
{
    ui->debugConsoleDock->setEnabled(false);
    ui->debugConsoleDock->setVisible(false);

    ui->sarConsoleDock->setEnabled(false);
    ui->sarConsoleDock->setVisible(false);

    if(plugins.terminalLoaded) 
    {
        plugins.terminal->setEnabled(false);
        plugins.terminal->setVisible(false);
    }
}

void CoreUI::SendRemoteCommand(QString command, CommandType type)
{
    if (type == CommandType::TelemetryCommand)
        telemetryRemote->Send(command.toUtf8());
    else if (type == CommandType::FormCommand)
        formRemote->Send(command.toUtf8());
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::on_minButton_clicked()     { showMinimized(); }
void CoreUI::on_minmaxButton_clicked()
{
    if (!isMaximized())
    {
        showMaximized();
        ui->minmaxButton->setIcon(QIcon(":/ui-resources/windowextension/maximize.png"));
    } // restore
    else
    {
        showNormal();
        ui->minmaxButton->setIcon(QIcon(":/ui-resources/windowextension/maximize.png"));
    }
}
void CoreUI::on_closeButton_clicked()   { QApplication::quit(); }

void CoreUI::on_settingsButton_clicked()
{
    PasswordDialog passwordDialog(this, SConfig::getHashString("SudoPassword"));
    if (passwordDialog.exec() == QDialog::Accepted)
    {
        if (passwordDialog.passwordCheck || SConfig::getHashString("SudoPassword").isEmpty())
        {
            SettingsDialog sd(this);
            QString s = SConfig::getHashString("ViewPath");
            if (sd.exec() == QDialog::Accepted)
            {
                if (s != SConfig::getHashString("ViewPath"))
                    DiskTools::fetchDirectory();
                else
                    Debug::Log("?[CONFIG] Path unchanged, no further scans");
                SConfig::saveSettings();
            }
            else
                SConfig::loadSettings();
            RuntimeData::initialize()->setSARIP("(" + SConfig::getHashString("NetworkType") + ") " + SConfig::getHashString("SarIP"));
            RuntimeData::initialize()->setPCIP(SConfig::getHashString("LoaderIP"));
            RuntimeData::initialize()->setTelemetryPort(SConfig::getHashString("TelemetryPort"));
            RuntimeData::initialize()->setLoaderPort(SConfig::getHashString("LoaderPort"));
            RuntimeData::initialize()->setCommandPort(SConfig::getHashString("DialogPort"));
            RuntimeData::initialize()->setListenPort(SConfig::getHashString("ListenPort"));
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

void CoreUI::on_infoButton_clicked()        { AboutDialog aboutDialog(this, PROJECT_VERSION); aboutDialog.exec(); }
void CoreUI::on_emulatorButton_clicked()    
{ 
    RuntimeData::initialize()->setEmulatorEnabled(!RuntimeData::initialize()->getEmulatorEnabled()); 
    if(RuntimeData::initialize()->getEmulatorEnabled())
        flightEmulator->startEmulator();
    else
        flightEmulator->stopEmulator(); 
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::ReadTelemetry(QByteArray data)
{
    udpTimeout->start(3 * SConfig::getHashFloat("TelemetryFrequency") * 1000);
    DataType dtype = MessageParser::checkReceivedDataType(data);

    switch (dtype)
    {
    case DataType::Telemetry: { //TODO: fix conckc
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
        HostAPI->execute("Terminal", "print", data);
    QString dataStr = data.data();
    dataStr.replace(QRegExp("[\r]"), "");
    QStringList dataParsed = dataStr.split(QRegExp("[\n]"), QString::SkipEmptyParts);
    for (QString str : dataParsed)
        ui->sarConsole->append(str);
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
            ui->label_c_formImageStatus->setText(Style::StyleText("получен ответ от РЛС", Colors::Accent100, Format::NoFormat));
            ui->progressBar_formImageStatus->setValue((int)40);
        }
        break;
    default:
        break;
    }
}

// вызывается раз в SConfig::UPDATETIME (обычно 0.5 сек)
// эта же функция вызывает обновление fixedUpdate в qml (только если пришел ответ от сервера телеметрии)
void CoreUI::Halftime()     { SendRemoteCommand(MessageParser::REQUEST_TELEMETRY, CommandType::TelemetryCommand); }
bool CoreUI::eventFilter(QObject * obj, QEvent * event)
{
    if ( event->type() == QEvent::KeyPress ) {
        qDebug()<<"magic printf";
        pressedKeys += (static_cast<QKeyEvent*>(event))->key();
        if ( pressedKeys.contains(Qt::Key_W) ) { flightEmulator->pitchChange(1); }
        if ( pressedKeys.contains(Qt::Key_S) ) { flightEmulator->pitchChange(-1); }
        if ( pressedKeys.contains(Qt::Key_A) ) { flightEmulator->yawChange(-1); }
        if ( pressedKeys.contains(Qt::Key_D) ) { flightEmulator->yawChange(1); }
        if ( pressedKeys.contains(Qt::Key_Q) ) { flightEmulator->rollChange(-1); }
        if ( pressedKeys.contains(Qt::Key_E) ) { flightEmulator->rollChange(1); }
        if ( pressedKeys.contains(Qt::Key_Z) ) { flightEmulator->throttleChange(1); }
        if ( pressedKeys.contains(Qt::Key_X) ) { flightEmulator->throttleChange(-1); }
        return 1;
    }
    else if ( event->type() == QEvent::KeyRelease ) { pressedKeys -= (static_cast<QKeyEvent*>(event))->key(); return 1; }
    else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CoreUI::on_spinBox_sarLowerBound_valueChanged(int arg1)
{
    RuntimeData::initialize()->setFormLowerBound(arg1);
}
void CoreUI::on_spinBox_sarUpperBound_valueChanged(int arg1)
{
    RuntimeData::initialize()->setFormUpperBound(arg1);
}
void CoreUI::on_doubleSpinBox_sarTime_valueChanged(double arg1)
{
    RuntimeData::initialize()->setFormTime(arg1);
}
void CoreUI::on_doubleSpinBox_sarDX_valueChanged(double arg1)
{
    RuntimeData::initialize()->setFormStep(arg1);
}
void CoreUI::on_checkBoxEnableManualGPS_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        ui->doubleSpinBox_height->setEnabled(true);
        ui->doubleSpinBox_velocity->setEnabled(true);
        ui->doubleSpinBox_height->setVisible(true);
        ui->doubleSpinBox_velocity->setVisible(true);
        RuntimeData::initialize()->setFormOverrideGPSData(1);
    }
    else
    {
        ui->doubleSpinBox_height->setEnabled(false);
        ui->doubleSpinBox_velocity->setEnabled(false);
        ui->doubleSpinBox_height->setVisible(false);
        ui->doubleSpinBox_velocity->setVisible(false);
        RuntimeData::initialize()->setFormOverrideGPSData(0);
    }
    SAROutputConsoleEmulator sarConsoleEmulator;
    sarConsoleEmulator.sampleTest();
}

void CoreUI::on_doubleSpinBox_height_valueChanged(double arg1)
{
    RuntimeData::initialize()->setFormGPSHeight(arg1);
}
void CoreUI::on_doubleSpinBox_velocity_valueChanged(double arg1)
{
    RuntimeData::initialize()->setFormGPSVelocity(arg1);
}
