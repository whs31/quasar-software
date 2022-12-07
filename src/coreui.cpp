#include "coreui.h"
#include "ui_coreui.h"

//qml types
#include "backend/ftelemetry.h"

CoreUI* CoreUI::debugPointer;
QRect CoreUI::screenResolution;
CoreUI::CoreUI(QWidget *parent)
    : QGoodWindow(parent)
    , ui(new Ui::CoreUI)
{
    debugPointer = this;
    screenResolution = QApplication::desktop()->availableGeometry();
    //log clear
    for(short i = 0; i < 25; i++)
    {
        qDebug()<<" ";
    }
    qDebug()<<"=================================NEW SESSION=========================================";
    InitializeUI();
    InitializeConnections();
}

CoreUI::~CoreUI()
{
    udpRemote->Disconnect();
    tcpRemote->Disconnect();
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
        if(msgtype == 0) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::ConsoleTextColor, true)); }
        else if (msgtype == 1) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Info, true)); }
        else if (msgtype == 2) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Warning, true)); }
        else if (msgtype == 3) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::Failure, true)); }
        else if (msgtype == 4) { ui->debugConsole->setTextColor(UXManager::GetColor(Colors::CriticalFailure, true)); }
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
    ui->label_c_connectionstatus->setText(Style::StyleText("Соединение с РЛС установлено", Colors::Success, Format::Bold));
}
void CoreUI::Disconnected()
{
    connected = false;
    ui->label_c_connectionstatus->setText(Style::StyleText("Соединение с РЛС не установлено", Colors::Failure, Format::Bold));
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::setPushButton_goLeftEnabled(bool state)        { ui->pushButton_goLeft->setEnabled(state);                                                                                                      }
void CoreUI::setPushButton_goRightEnabled(bool state)       { ui->pushButton_goRight->setEnabled(state);                                                                                                     }
void CoreUI::updateLoaderLabel(void)
{
    ui->label_c_loaderStatus->setText("Статус: "+Style::StyleText("ожидание подключения", Colors::Main, Format::Italic));
    uiTimer1->stop();
    ui->progressBar_loader->setValue(0);
}
void CoreUI::updateDirectory(void)                          { if(autoUpdate) { imageProcessing->PartialScan(); linker->panImage(imageProcessing->getFileCounter()); }                                        }
void CoreUI::updateImageManagerLabels(int total, int current)
{
    ui->label_c_foundImages->setText("Найдено "
                                     +Style::StyleText(QString::number(total), Colors::Accent, Format::Bold)
                                     +" изображений");
    ui->label_c_currentImage->setText("Изображение "
                                      +Style::StyleText(QString::number(current+1), Colors::Main, Format::Bold)
                                      +" из "
                                      +Style::StyleText(QString::number(total), Colors::NoColor, Format::Bold));
}
void CoreUI::updateImageMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, float lx, float ly, float divAngle, QString hexSum, QString datetime, bool match)
{
    ui->label_c_metaFilename->setText(filename);
    ui->label_c_metaLat->setText(QString::number(lat, 'f', 6));
    ui->label_c_metaLon->setText(QString::number(lon, 'f', 6));
    ui->label_c_metaDx->setText(QString::number(dx));
    ui->label_c_metaDy->setText(QString::number(dy));
    ui->label_c_metaX0->setText(QString::number(x0));
    ui->label_c_metaY0->setText(QString::number(y0));
    ui->label_c_metaAngle->setText(QString::number(angle));
    ui->label_c_metaDAngle->setText(QString::number(driftAngle));
    ui->label_c_metaLX->setText(QString::number(lx));
    ui->label_c_metaLY->setText(QString::number(ly));
    ui->label_c_metaDiv->setText(QString::number(divAngle));
    ui->label_c_metaChecksum->setText(hexSum);
    ui->label_c_metaTime->setText(datetime);
    (match) ? ui->label_c_checksumSuccess->setText(Style::StyleText("совпадает", Colors::Success)) : ui->label_c_checksumSuccess->setText(Style::StyleText("не совпадает", Colors::Failure));
}
void CoreUI::enableImageBar(bool b)
{
    ui->pushButton_showAllImages->setEnabled(b);
    ui->pushButton_showImage->setChecked(b);
    ui->layout_imageTop_2->setEnabled(b);
    ui->layout_imageMiddle_2->setEnabled(b);
    ui->metaGBox->setEnabled(b);
}
void CoreUI::updateProgress(float f)
{
    if(f>0) { ui->label_c_loaderStatus->setText("Статус: "+Style::StyleText("приём данных", Colors::Accent, Format::Italic)); }
    if(f>99) {
        ui->label_c_loaderStatus->setText("Статус: "+Style::StyleText("изображение получено", Colors::Success, Format::Italic));
        uiTimer1->start(5000);
    }
    ui->progressBar_loader->setValue((int)f);
}
void CoreUI::updateTelemetryLabels(float lat, float lon, float speed, float elevation, int satcount)
{
    ui->label_c_satcount->setText("Спутники: "+Style::StyleText(QString::number(satcount), Colors::Accent, Format::Bold));
}
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
    ui->map->rootContext()->setContextProperty("ApplicationDirPath", QString(QCoreApplication::applicationDirPath()));
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

}

void CoreUI::InitializeConnections()
{
    //core
    //(!) do not touch it.
    Debug::Log("?[STARTUP] Setuping connections...");
        timer = new QTimer(this);
        udpTimeout = new QTimer(this);
        uiTimer1 = new QTimer(this);
    linker = new LinkerQML(qml);
    new SConfig(qml);
    if(SConfig::TESTMODE)
        Debug::Log("![STARTUP] Program is running in test mode!");

    //qml types declaration
    QScopedPointer<FTelemetry> fTelemetry(new FTelemetry);
    qmlRegisterSingletonInstance("FModel", 1, 0, "Telemetry", fTelemetry.get());

    //network setup
    udpRemote = new UDPRemote();
    tcpRemote = new TCPRemote();
    downloader = new TCPDownloader(this, DowloaderMode::SaveAtDisconnect);
        connect(downloader, SIGNAL(receivingFinished()), this, SLOT(updateDirectory()));
        connect(downloader, SIGNAL(progressChanged(float)), this, SLOT(updateProgress(float)));

    //sar image alghorithms setup
    imageProcessing = new ImageProcessing(linker);
        connect(imageProcessing, SIGNAL(setLeftButton(bool)), this, SLOT(setPushButton_goLeftEnabled(bool)));
        connect(imageProcessing, SIGNAL(setRightButton(bool)), this, SLOT(setPushButton_goRightEnabled(bool)));
        connect(imageProcessing, SIGNAL(updateTopLabels(int,int)), this, SLOT(updateImageManagerLabels(int,int)));
        connect(imageProcessing, SIGNAL(updateMetaLabels(QString,float,float,float,float,float,float,float,float,float,float,float,QString,QString,bool)),
                           this, SLOT(updateImageMetaLabels(QString,float,float,float,float,float,float,float,float,float,float,float,QString,QString,bool)));
        connect(imageProcessing, SIGNAL(enableImageBar(bool)), this, SLOT(enableImageBar(bool)));
        connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
        connect(udpTimeout, SIGNAL(timeout()), this, SLOT(Disconnected()));
        connect(uiTimer1, SIGNAL(timeout()), this, SLOT(updateLoaderLabel()));
        connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadUDPData(QByteArray)));
        connect(tcpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadUDPData(QByteArray)));

    //network connection
    if(SConfig::CONNECTONSTART)
    {
        if(SConfig::NETWORKTYPE == "TCP") { tcpRemote->Connect(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT); }
        else
        {
            udpRemote->Connect(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT);
            if(SConfig::NETWORKTYPE != "UDP") { SConfig::NETWORKTYPE = "UDP"; Debug::Log("![WARNING] Connection type string unrecognized, using UDP by default"); }
            Debug::Log("?[REMOTE] UDP client connected");
        }
    }

    //ui misc initialization and assignment
    ui->label_c_sarip->setText("Адрес РЛС: "+Style::StyleText(" ("+SConfig::NETWORKTYPE+") ", Colors::MainShade800, Format::Bold)
                                            +Style::StyleText(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT, Colors::MainShade900, Format::Bold));
    ui->label_c_loaderip->setText("Адрес загрузчика: "+Style::StyleText(SConfig::LOADERIP+":"+SConfig::LOADERPORT, Colors::MainShade900, Format::Bold));
    ui->label_c_loaderStatus->setText("Статус: "+Style::StyleText("ожидание подключения", Colors::Main, Format::Italic));

    //timers starts here
    timer->start(SConfig::UPDATETIME*1000);
    udpTimeout->start(3*SConfig::UPDATETIME*1000);

    //startup functions
    Disconnected();
    imageProcessing->InitialScan();
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
    
    ui->mapSettingsDock->setEnabled(true);
    ui->mapSettingsDock->setVisible(true);
    ui->mapSettingsDock->adjustSize();
    ui->mapSettingsDock->move(screenResolution.width()/2, screenResolution.height()/4);
    ui->mapSettingsDock->setEnabled(false);
    ui->mapSettingsDock->setVisible(false);
}

void CoreUI::SendRemoteCommand(QString command)
{
    if(SConfig::NETWORKTYPE == "TCP"){
        tcpRemote->Send(command.toUtf8());
    } else {
        udpRemote->Send(command.toUtf8());
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::on_minButton_clicked()
{
    showMinimized();
}


void CoreUI::on_minmaxButton_clicked()
{
    if(!isMaximized())
        {
            showMaximized();
            ui->minmaxButton->setIcon(QIcon(":/ui-resources/windowextension/maximize.png")); //restore
        }
        else
        {
            showNormal();
            ui->minmaxButton->setIcon(QIcon(":/ui-resources/windowextension/maximize.png"));
        }
}


void CoreUI::on_closeButton_clicked()
{
    QApplication::quit();
}

void CoreUI::on_settingsButton_clicked()
{
    SettingsDialog sd(this);
    QString s = SConfig::PATH;
    if(sd.exec() == QDialog::Accepted)
    {
        if(s!=SConfig::PATH)
        {
            imageProcessing->InitialScan();
        } else { Debug::Log("?[CONFIG] Path unchanged, no further scans"); }

        SConfig::saveSettings();
    } else { SConfig::loadSettings(); }

    ui->label_c_sarip->setText("Адрес РЛС: "+Style::StyleText(" ("+SConfig::NETWORKTYPE+") ", Colors::MainShade800, Format::Bold)
                                            +Style::StyleText(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT, Colors::MainShade900, Format::Bold));
    ui->label_c_loaderip->setText("Адрес загрузчика: "+Style::StyleText(SConfig::LOADERIP+":"+SConfig::LOADERPORT, Colors::MainShade900, Format::Bold));
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CoreUI::ReadUDPData(QByteArray data)
{
    udpTimeout->start(3*SConfig::UPDATETIME*1000);
    DataType dtype = MessageParser::checkReceivedDataType(data);
    switch (dtype) {
    case DataType::Telemetry:
        telemetry[4] = (double)0;
        telemetry = MessageParser::parseTelemetry(data);
        break;
    default:
        break;
    }
    if((int)telemetry[4] != 0 || _conckc != telemetry[0])
    {
        Connected();
    } else { Disconnected(); }
    _conckc = telemetry[0];
    updateTelemetryLabels(telemetry[0], telemetry[1], telemetry[2], telemetry[3], (int)telemetry[4]);
    linker->getTelemetry((float)telemetry[0], (float)telemetry[1], (float)telemetry[3], (float)telemetry[2]);
}

void CoreUI::Halftime() //вызывается раз в SConfig::UPDATETIME (обычно 0.5 сек)
{
    SendRemoteCommand(MessageParser::REQUEST_TELEMETRY);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



