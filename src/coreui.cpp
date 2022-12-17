#include "coreui.h"
#include "ui_coreui.h"

CoreUI* CoreUI::debugPointer;
QRect CoreUI::screenResolution;
CoreUI::CoreUI(QWidget *parent)
    : QGoodWindow(parent)
    , ui(new Ui::CoreUI)
{
    debugPointer = this;
    screenResolution = QGuiApplication::screens().first()->availableGeometry();
    Debug::NewSession();
    InitializeUI();
    InitializeConnections();
}

CoreUI::~CoreUI()
{
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    consoleListenerRemote->Disconnect();
    //tcpRemote->Disconnect();
    delete ui;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CoreUI* CoreUI::getDebugPointer(void)                       { return debugPointer;                                                                                                                           }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::debugStreamUpdate(QString _text, int msgtype)
{
    if(uiReady)
    {
        if(msgtype == 0) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Text100, true)); }
        else if (msgtype == 1) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Info200, true)); }
        else if (msgtype == 2) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Warning100, true)); }
        else if (msgtype == 3) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Error200, true)); }
        else if (msgtype == 4) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Error100, true)); }
            QFont consoleFont = ui->debugConsole->font();
            consoleFont.setPointSize(8);
        ui->debugConsole->insertPlainText(_text);
        ui->debugConsole->setTextColor(Qt::white);
        ui->debugConsole->setFont(consoleFont);
        QTextCursor c = ui->debugConsole->textCursor();
        c.movePosition(QTextCursor::End);
        ui->debugConsole->setTextCursor(c);
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CoreUI::getReady(void)                                 { return uiReady;                                                                                                                                }
QQuickItem* CoreUI::getMapPointer(void)                     { return qml;                                                                                                                                    }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::Connected()
{
    connected = true;
    ui->label_c_connectionstatus->setText(Style::StyleText("Соединение с РЛС установлено", Colors::Success100, Format::Bold));
}
void CoreUI::Disconnected()
{
    connected = false;
    ui->label_c_connectionstatus->setText(Style::StyleText("Соединение с РЛС не установлено", Colors::Error200, Format::Bold));
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::updateProgress(float f)
{
    if(f>0)
    {
        ui->label_c_loaderStatus->setText("Статус: "+Style::StyleText("приём данных", Colors::Accent100, Format::Italic));
        ui->label_c_formImageStatus->setText(Style::StyleText("загрузка изображения", Colors::Warning100, Format::NoFormat));

    }
    if(f>99) {
        ui->label_c_loaderStatus->setText("Статус: "+Style::StyleText("изображение получено", Colors::Success100, Format::Italic));
        ui->label_c_formImageStatus->setText(Style::StyleText("изображение отображено на карте", Colors::Success100, Format::NoFormat));
        uiTimer1->start(5000);
    }
    ui->progressBar_loader->setValue((int)f);
    ui->progressBar_formImageStatus->setValue((int)(f / 2) + 50);
}
void CoreUI::updateTelemetryLabels(int satcount)    { ui->label_c_satcount->setText("Спутники: "+Style::StyleText(QString::number(satcount), Colors::Accent100, Format::Bold));                                 }
void CoreUI::setCheckboxState(bool b)               { ui->checkBox->setChecked(b);                                                                                                                           }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::InitializeUI()
{
    //ui setup. do not call any unintentional code before ui is initialized (uiReady == true)
    ui->setupUi(this);

    //custom window frame setup
    setMargins(25, 0, 0, 170);
    ui->header->setTitleBarWidget(new QWidget());
    uiReady = true;
    Debug::Log("[STARTUP] Starting UI initialization...");

    //qml base setup
    ui->map->rootContext()->setContextProperty("OsmConfigPath", CacheManager::getMapProviderCache());
    ui->map->setSource(QUrl("qrc:/qml/map.qml"));
    ui->map->show();
    qml = ui->map->rootObject();

    //debug logging misc code
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    Debug::Log("[STARTUP] UI initialization finished");
    Debug::Log("?[STARTUP] Session started at "+localTime.toString());

    //openssl check
    bool b_ssl1 = QSslSocket::supportsSsl();
    QString ssl1 = b_ssl1 ? "true" : "false";
    if (QSslSocket::supportsSsl())
        {
            Debug::Log("?[STARTUP] OpenSSL detected: "
                            + ssl1
                            + ", OpenSSL build version: "
                            + QSslSocket::sslLibraryBuildVersionString()
                            + ", OpenSSL ver.: "
                            + QSslSocket::sslLibraryVersionString());
        }
        else {
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

    //set default position and size of floating qdockwidgets
    InitializeDockwidgets();

    //any other ui startup code here!
    ui->doubleSpinBox_height->setVisible(false);
    ui->doubleSpinBox_velocity->setVisible(false);

}

void CoreUI::InitializeConnections()
{
    //core
    //(!) do not touch it.
    Debug::Log("?[STARTUP] Setuping connections...");
        timer = new QTimer(this);
        udpTimeout = new QTimer(this);
        uiTimer1 = new QTimer(this);
    LinkerQML::initialize(qml);

    //qml types declaration
    fTelemetry = new FTelemetry();                                ui->map->rootContext()->setContextProperty("FTelemetry", fTelemetry);
    fDynamicVariables = new FDynamicVariables();                  ui->map->rootContext()->setContextProperty("FDynamicVariables", fDynamicVariables);
        connect(fDynamicVariables, SIGNAL(followPlaneChanged(bool)), this, SLOT(setCheckboxState(bool)));
    fStaticVariables = new FStaticVariables();                    ui->map->rootContext()->setContextProperty("FStaticVariables", fStaticVariables);

    //config
    SConfig::initialize(fStaticVariables);
    if(SConfig::getHashBoolean("UseOSM"))
        Debug::Log("![STARTUP] Program is running in test mode!");
    QMetaObject::invokeMethod(qml, "qmlBackendStart");

    //network setup
    telemetryRemote = new UDPRemote();
    formRemote = new UDPRemote();
    consoleListenerRemote = new UDPRemote();
    //tcpRemote = new TCPRemote();
    downloader = new TCPDownloader(this, DowloaderMode::SaveAtDisconnect);
        connect(downloader, SIGNAL(progressChanged(float)), this, SLOT(updateProgress(float)));

    //sar connections setup
        connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
        connect(udpTimeout, SIGNAL(timeout()), this, SLOT(Disconnected()));
        //connect(uiTimer1, SIGNAL(timeout()), this, SLOT(updateLoaderLabel()));
        connect(telemetryRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
        connect(formRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadForm(QByteArray)));
        connect(consoleListenerRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadSARConsole(QByteArray)));
        //connect(tcpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));

    //image-processing setup
    DiskTools::fetchDirectory();

    //network connection
    if(SConfig::getHashBoolean("StartupConnectToSAR"))
    {
        if(SConfig::getHashString("NetworkType") == "TCP") { qCritical()<<"TCP usage in telemetry"; }
        else
        {
            telemetryRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("TelemetryPort"));
            formRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("DialogPort"));
            consoleListenerRemote->Connect(SConfig::getHashString("LoaderIP") + ":" + SConfig::getHashString("ListenPort"));
            qCritical()<<SConfig::getHashString("LoaderIP")<<":"<<SConfig::getHashString("ListenPort");
            if(SConfig::getHashString("NetworkType") != "UDP") { SConfig::getHashString("NetworkType") = "UDP"; Debug::Log("![WARNING] Connection type string unrecognized, using UDP by default"); }
            Debug::Log("?[REMOTE] UDP client connected");
        }
    }

    //ui misc initialization and assignment
    ui->label_c_sarip->setText("Адрес РЛС: "+Style::StyleText(" ("+SConfig::getHashString("NetworkType")+") ", Colors::Info300, Format::Bold)
                                            +Style::StyleText(SConfig::getHashString("SarIP")+":"+SConfig::getHashString("TelemetryPort"), Colors::Info200, Format::Bold));
    ui->label_c_loaderip->setText("Адрес загрузчика: "+Style::StyleText(SConfig::getHashString("LoaderIP")+":"+SConfig::getHashString("LoaderPort"), Colors::Info200, Format::Bold));
    ui->label_c_loaderStatus->setText("Статус: "+Style::StyleText("ожидание подключения", Colors::Info100, Format::Italic));

    //timers starts here
    timer->start(SConfig::getHashFloat("TelemetryFrequency") * 1000);
    udpTimeout->start(3*SConfig::getHashFloat("TelemetryFrequency") * 1000);

    //startup functions
    Disconnected();
    Debug::Log("[STARTUP] Connections set up successfully");

    //execute any other startup code here

}

void CoreUI::InitializeDockwidgets()
{
    //чтобы все работало, надо их показать и тут же скрыть.
    ui->debugConsoleDock->setEnabled(true);
    ui->debugConsoleDock->setVisible(true);
    ui->debugConsoleDock->adjustSize();
    ui->debugConsoleDock->move(screenResolution.width()/4, screenResolution.height()/3);
    ui->debugConsoleDock->setEnabled(false);
    ui->debugConsoleDock->setVisible(false);

    ui->sarConsoleDock->setEnabled(true);
    ui->sarConsoleDock->setVisible(true);
    ui->sarConsoleDock->adjustSize();
    ui->sarConsoleDock->move(screenResolution.width()/1.5, screenResolution.height()/3);
    ui->sarConsoleDock->setEnabled(false);
    ui->sarConsoleDock->setVisible(false);
    
    ui->mapSettingsDock->setEnabled(true);
    ui->mapSettingsDock->setVisible(true);
    ui->mapSettingsDock->adjustSize();
    ui->mapSettingsDock->move(screenResolution.width()/2, screenResolution.height()/4);
    ui->mapSettingsDock->setEnabled(false);
    ui->mapSettingsDock->setVisible(false);
}

void CoreUI::SendRemoteCommand(QString command, CommandType type)
{
    if(SConfig::getHashString("NetworkType") == "TCP"){
        //tcpRemote->Send(command.toUtf8());
    } else {
        if(type == CommandType::TelemetryCommand)
        {
            telemetryRemote->Send(command.toUtf8());
        } else if (type == CommandType::FormCommand)
        {
            formRemote->Send(command.toUtf8());
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::on_minButton_clicked() {showMinimized();}
void CoreUI::on_minmaxButton_clicked()
{
    if(!isMaximized()) { showMaximized(); ui->minmaxButton->setIcon(QIcon(":/ui-resources/windowextension/maximize.png")); } //restore
    else { showNormal(); ui->minmaxButton->setIcon(QIcon(":/ui-resources/windowextension/maximize.png")); }
}
void CoreUI::on_closeButton_clicked() { QApplication::quit(); }

void CoreUI::on_settingsButton_clicked()
{
    PasswordDialog passwordDialog(this, SConfig::getHashString("SudoPassword"));
    if(passwordDialog.exec() == QDialog::Accepted)
    {
        if(passwordDialog.passwordCheck || SConfig::getHashString("SudoPassword").isEmpty())
        {
            SettingsDialog sd(this);
            QString s = SConfig::getHashString("ViewPath");
            if(sd.exec() == QDialog::Accepted)
            {
                if(s!=SConfig::getHashString("ViewPath"))
                {

                } else { Debug::Log("?[CONFIG] Path unchanged, no further scans"); }
                SConfig::saveSettings();
            } else { SConfig::loadSettings(); }
            ui->label_c_sarip->setText("Адрес РЛС: "+Style::StyleText(" ("+SConfig::getHashString("NetworkType")+") ", Colors::Info300, Format::Bold)
                                                    +Style::StyleText(SConfig::getHashString("SarIP")+":"+SConfig::getHashString("TelemetryPort"), Colors::Info200, Format::Bold));
            ui->label_c_loaderip->setText("Адрес загрузчика: "+Style::StyleText(SConfig::getHashString("LoaderIP")+":"+SConfig::getHashString("LoaderPort"), Colors::Info200, Format::Bold));
        } else {
            QMessageBox passwordWarning;
            passwordWarning.setWindowTitle("Ошибка");
            passwordWarning.setIcon(QMessageBox::Critical);
            passwordWarning.setText("Неверный пароль.");
            passwordWarning.setStandardButtons(QMessageBox::Yes);
            passwordWarning.setDefaultButton(QMessageBox::Yes);
            passwordWarning.exec();
        }
    } else {
        // do nothing
    }
}

void CoreUI::on_infoButton_clicked() { AboutDialog aboutDialog(this, PROJECT_VERSION); aboutDialog.exec(); }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::ReadTelemetry(QByteArray data)
{
    udpTimeout->start(3 * SConfig::getHashFloat("TelemetryFrequency")*1000);
    DataType dtype = MessageParser::checkReceivedDataType(data);

    switch (dtype) {
    case DataType::Telemetry:
        std::array<double, 6> telemetry; //lat, lon, speed, elevation, sats
        telemetry[4] = (double)0;
        telemetry = MessageParser::parseTelemetry(data);
        _conckc = telemetry[0];
        fTelemetry->setLatitude((float)telemetry[0]);
        fTelemetry->setLongitude((float)telemetry[1]);
        fTelemetry->setSpeed((float)telemetry[2]);
        fTelemetry->setElevation((float)telemetry[3]);
        fTelemetry->setSats((short)telemetry[4]);
        //direction
        updateTelemetryLabels((int)telemetry[4]);

        linker->fixedUpdate();

        if((int)telemetry[4] != 0 || _conckc != telemetry[0])
        {
            Connected();
        } else { Disconnected(); }
        break;
    case DataType::FormResponse:
        std::array<int, 4> responseList;
        responseList = MessageParser::parseFormResponse(data);

        //temp
        if(!responseList.empty())
        {
            QString checksumCheck = (responseList[3] == 1) ? "success" : "failure";
            Debug::Log("?[FORM] SAR responds with: pid "
                       + QString::number(responseList[0])
                       + ", hexlen "
                       + QString::number(responseList[1])
                       + ", code"
                       + QString::number(responseList[2])
                       + " with checksum check " +
                       checksumCheck);
        }
        break;
    default:
        break;
    }
}

void CoreUI::ReadSARConsole(QByteArray data)
{
    QString dataStr = data.data();
    dataStr.replace(QRegExp("[\r]"), "");
    QStringList dataParsed = dataStr.split(QRegExp("[\n]"),QString::SkipEmptyParts);
    for(QString str : dataParsed)
    {
        ui->sarConsole->append(str);
    }
    //qCritical()<<dataStr; //rework in future
}

void CoreUI::ReadForm(QByteArray data)
{
    DataType dtype = MessageParser::checkReceivedDataType(data);
    switch (dtype) {
    case DataType::Telemetry:
    {
        break;
    }
    case DataType::FormResponse:
        std::array<int, 4> responseList;
        responseList = MessageParser::parseFormResponse(data);

        //temp
        if(!responseList.empty())
        {
            QString checksumCheck = (responseList[3] == 1) ? "success" : "failure";
            Debug::Log("?[FORM] SAR responds with: pid "
                       + QString::number(responseList[0])
                       + ", hexlen "
                       + QString::number(responseList[1])
                       + ", code"
                       + QString::number(responseList[2])
                       + " with checksum check " +
                       checksumCheck);
            ui->label_c_formImageStatus->setText(Style::StyleText("получен ответ от РЛС", Colors::Accent100, Format::NoFormat));
            ui->progressBar_formImageStatus->setValue((int)40);
        }
        break;
    default:
        break;
    }
}

//вызывается раз в SConfig::UPDATETIME (обычно 0.5 сек)
//эта же функция вызывает обновление fixedUpdate в qml (только если пришел ответ от сервера телеметрии)
void CoreUI::Halftime()
{
    SendRemoteCommand(MessageParser::REQUEST_TELEMETRY, CommandType::TelemetryCommand);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CoreUI::on_spinBox_sarLowerBound_valueChanged(int arg1)
{
    sar_lowerbound = arg1;
}
void CoreUI::on_spinBox_sarUpperBound_valueChanged(int arg1)
{
    sar_upperbound = arg1;
}
void CoreUI::on_doubleSpinBox_sarTime_valueChanged(double arg1)
{
    sar_time = arg1;
}
void CoreUI::on_doubleSpinBox_sarDX_valueChanged(double arg1)
{
    sar_dx = arg1;
}
void CoreUI::on_checkBoxEnableManualGPS_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->doubleSpinBox_height->setEnabled(true);
        ui->doubleSpinBox_velocity->setEnabled(true);
        ui->doubleSpinBox_height->setVisible(true);
        ui->doubleSpinBox_velocity->setVisible(true);
        sar_override_gps = 1;
    } else {
        ui->doubleSpinBox_height->setEnabled(false);
        ui->doubleSpinBox_velocity->setEnabled(false);
        ui->doubleSpinBox_height->setVisible(false);
        ui->doubleSpinBox_velocity->setVisible(false);
        sar_override_gps = 0;
    }

}
void CoreUI::on_doubleSpinBox_height_valueChanged(double arg1)
{
    sar_gps_height = arg1;
}
void CoreUI::on_doubleSpinBox_velocity_valueChanged(double arg1)
{
    sar_gps_velocity = arg1;
}
