#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow * MainWindow::pMainWindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    pMainWindow = this;
    InitializeUI();
    InitializeConnections();
}

MainWindow::~MainWindow()
{
    udpRemote->Disconnect();
    tcpRemote->Disconnect();
    delete ui;
}

void MainWindow::InitializeUI()
{
    qInfo()<<"[STARTUP] Starting UI initialization...";
    ui->setupUi(this);
    ui->map->show();
    qml = ui->map->rootObject();
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    qInfo()<<"[STARTUP] Session started at "+localTime.toString();
    if (QSslSocket::supportsSsl())
        {
            qInfo() << "[STARTUP] OpenSSL detected: " << QSslSocket::supportsSsl() << ", OpenSSL build version: " << QSslSocket::sslLibraryBuildVersionString() << ", OpenSSL ver.: " << QSslSocket::sslLibraryVersionString();
        }
        else {
            qCritical() << "[ERROR] OpenSSL detected: " << QSslSocket::supportsSsl() << ", OpenSSL build version: " << QSslSocket::sslLibraryBuildVersionString() << ", OpenSSL ver.: " << QSslSocket::sslLibraryVersionString();
            QMessageBox openSSLDialogue;
            openSSLDialogue.setWindowTitle("Библиотека OpenSSL не обнаружена!");
            openSSLDialogue.setIcon(QMessageBox::Critical);
            openSSLDialogue.setText("Попробуйте переустановить программу.");
            openSSLDialogue.exec();
        }
    qInfo()<<"[STARTUP] UI initialization finished";
}

void MainWindow::InitializeConnections()
{
    qInfo()<<"[STARTUP] Setuping connections...";
    html = new HTMLTags();
    linker = new LinkerQML(qml);


    //------------------------------------
    timer = new QTimer(this);
    udpRemote = new UDPRemote();
    tcpRemote = new TCPRemote();
    config = new ConfigHandler();
    config->loadSettings();
    imageProcessing = new ImageProcessing(linker); //linker

    connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
    connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    connect(tcpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    if(C_NETWORKTYPE == "TCP"){ tcpRemote->Connect(C_NETWORKADDRESS+":"+C_NETWORKPORT); }
    else
    {
        udpRemote->Connect(C_NETWORKADDRESS+":"+C_NETWORKPORT);
        if(C_NETWORKTYPE != "UDP") { C_NETWORKTYPE = "UDP"; qWarning()<<"[WARNING] Connection type string unrecognized, using UDP by default"; }
        qInfo()<<"[REMOTE] UDP client connected";
    }
    timer->start(500);
    qInfo()<<"[STARTUP] Connections set up successfully";

    InitialImageScan();
}

bool MainWindow::InitialImageScan()
{
    bool n = imageProcessing->processPath(C_PATH);
    imageProcessing->updateUpperLabels();
    if(imageProcessing->getReadyStatus()==true)
    {
        for(int i = 0; i<=imageProcessing->getVectorSize()-1; i++)
        {
            imageChecklist.append(false);
        }
        imageProcessing->showAllImages();
    }
    ui->frame_3->setEnabled(n);
    ui->frame_4->setEnabled(n);
    ui->metaGBox->setEnabled(n);

    return n;
}
void MainWindow::Halftime()
{
    //$request запрашивает данные телеметрии в виде строки (ответ = строка вида ($lat@lon@speed@elv#)),
    //$form-SAR-image дает команду на формирование РЛИ (ответ = строка вида ($>>text#))
    if(C_NETWORKTYPE == "TCP"){
        SendRemoteCommand("$request");
    } else {
        SendRemoteCommand("$request");
    }
}

void MainWindow::SendRemoteCommand(QString command)
{
    if(C_NETWORKTYPE == "TCP"){
        tcpRemote->Send(command.toUtf8());
    } else {
        udpRemote->Send(command.toUtf8());
    }
}

void MainWindow::ReadTelemetry(QByteArray data){

    //qDebug()<<data.data();
    QString unparsed = data.data();
    QString parsed;
    QStringList parsedList;
    if(unparsed.endsWith("#") && unparsed.startsWith("$")) {
        if(unparsed.startsWith("$>>"))
        {
            QString parsedMessage = unparsed;
            parsedMessage.chop(1);
            parsedMessage.remove(0, 3);
            qInfo()<<"[SERVER] Server responds with: "<<parsedMessage;
        }
        else
        {
            parsed = unparsed;
            parsed.chop(1);
            parsed.remove(0, 1);
            parsedList = parsed.split("@");
            for(int i = 0; i<=3; i++)
            {
                telemetry[i] = parsedList[i].toDouble();
            }
        }
    }
    ui->label_c_telemetrylat->setText(html->HtmlColorMain+html->HtmlBold+QString::number(telemetry[0], 'f', 7)+html->HtmlBoldEnd+html->HtmlColorEnd);
    ui->label_c_telemetrylon->setText(html->HtmlColorMain+html->HtmlBold+QString::number(telemetry[1], 'f', 7)+html->HtmlBoldEnd+html->HtmlColorEnd);
    ui->label_c_telemetryspd->setText(html->HtmlColorMain+html->HtmlBold+QString::number(telemetry[2], 'f', 1)+html->HtmlBoldEnd+html->HtmlColorEnd);
    ui->label_c_telemetryelv->setText(html->HtmlColorMain+html->HtmlBold+QString::number(telemetry[3], 'f', 1)+html->HtmlBoldEnd+html->HtmlColorEnd);
    linker->getTelemetry((float)telemetry[0], (float)telemetry[1], (float)telemetry[3], (float)telemetry[2]);
}

void MainWindow::on_formImage_triggered() //menu slot (will be removed)
{
    qInfo()<<"[CLIENT] Sending command to form SAR image";
    SendRemoteCommand("$form-SAR-image");
}

void MainWindow::on_openSettings_triggered() //menu slot
{
    SettingsDialog sd(this,
                      C_NETWORKTYPE,
                      C_NETWORKADDRESS,
                      C_NETWORKPORT,
                      C_UPDATETIME,
                      C_PREDICTRANGE,
                      C_DRIFTANGLE,
                      C_AZIMUTH,
                      C_CAPTURERANGE,
                      C_CAPTURETIME,
                      C_ANTENNAPOSITION,
                      C_PATH);
    if(sd.exec() == QDialog::Accepted)
    {
        C_NETWORKTYPE = sd.r_connectionType;
        C_NETWORKADDRESS = sd.r_connectionAddress;
        C_NETWORKPORT = sd.r_connectionPort;
        C_UPDATETIME = sd.r_refreshTime;
        C_PREDICTRANGE = sd.r_predictRange;
        C_DRIFTANGLE = sd.r_driftAngle;
        C_AZIMUTH = sd.r_thetaAzimuth;
        C_CAPTURERANGE = sd.r_captureRange;
        C_CAPTURETIME = sd.r_captureTime;
        C_ANTENNAPOSITION = sd.r_antennaPosition;
        if(C_PATH!=sd.r_path) { C_PATH = sd.r_path; InitialImageScan(); } else { qDebug()<<"[CONFIG] Path unchanged, no further scans"; }

        config->saveSettings();
    } else { config->loadSettings(); }
}

MainWindow *MainWindow::getMainWinPtr()                         { return pMainWindow;                                                                                                           }
void MainWindow::on_checkBox_drawTooltip_stateChanged(int arg1) { linker->changeEnableTooltip(arg1);                                                                                            }
void MainWindow::on_checkBox_drawTrack_stateChanged(int arg1)   { linker->changeDrawRoute(arg1);                                                                                                }
void MainWindow::on_checkBox_stateChanged(int arg1)             { linker->changeFollowPlane(arg1);                                                                                              }
void MainWindow::on_pushButton_panGPS_clicked()                 { linker->panGPS();                                                                                                             }
void MainWindow::on_pushButton_panImage_2_clicked()             { on_pushButton_panImage_clicked();                                                                                             }
void MainWindow::on_pushButton_update_clicked()                 { bool b = InitialImageScan(); if(b) { ui->pushButton_showImage->setChecked(imageChecklist[imageProcessing->getFileCounter()]);}}
void MainWindow::on_pushButton_goLeft_clicked()                 { imageProcessing->goLeft(); ui->pushButton_showImage->setChecked(imageChecklist[imageProcessing->getFileCounter()]);           }
void MainWindow::on_pushButton_goRight_clicked()                { imageProcessing->goRight(); ui->pushButton_showImage->setChecked(imageChecklist[imageProcessing->getFileCounter()]);          }

void MainWindow::on_pushButton_clearTrack_clicked()
{
    QMessageBox askForClearTrack;
    askForClearTrack.setWindowTitle("Очистка трека");
    askForClearTrack.setIcon(QMessageBox::Information);
    askForClearTrack.setText("Вы уверены, что хотите полностью очистить трек?");
    askForClearTrack.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    askForClearTrack.setDefaultButton(QMessageBox::Cancel);
    int ret = askForClearTrack.exec();
    switch (ret) {
    case QMessageBox::Yes: linker->clearRoute();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}



void MainWindow::on_pushButton_panImage_clicked()
{
    linker->panImage(imageProcessing->getFileCounter());
    ui->checkBox->setChecked(false);
    on_checkBox_stateChanged(0);
}



void MainWindow::on_pushButton_showImage_clicked()
{
    if(imageProcessing->getReadyStatus()==true)
    {
        imageChecklist[imageProcessing->getFileCounter()] = !imageChecklist[imageProcessing->getFileCounter()];
        ImageChecklistLoop();
    }
}

void MainWindow::ImageChecklistLoop()
{
    if(imageProcessing->getReadyStatus()==true)
    {
        for(int i = 0; i<imageProcessing->getVectorSize(); i++)
        {
            if(imageChecklist[i]==true)
            {
                linker->showImage(i);
            } else {
                linker->hideImage(i);
            }
        }
    }
}

void MainWindow::on_pushButton_showAllImages_clicked()
{
    if(imageProcessing->getReadyStatus()==true)
    {
        if(imageChecklist[0] == false) {
            for(int i = 0; i<imageProcessing->getVectorSize(); i++)
            {
                imageChecklist[i] = true;
            }
        } else {
            for(int i = 0; i<imageProcessing->getVectorSize(); i++)
            {
                imageChecklist[i] = false;
            }
        }
        ImageChecklistLoop();
        ui->pushButton_showImage->setChecked(imageChecklist[imageProcessing->getFileCounter()]);
    }
}
