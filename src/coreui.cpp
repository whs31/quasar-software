#include "coreui.h"
#include "ui_coreui.h"

/*
 * 1. Класс парсер для телеметрии и тд
 * 2. Разбить cpp на два
 *
 *
*/

CoreUI* CoreUI::debugPointer;
CoreUI::CoreUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoreUI)
{
    debugPointer = this;
    InitializeUI();
    InitializeConnections();
}

CoreUI::~CoreUI()
{
    udpRemote->Disconnect();
    tcpRemote->Disconnect();
    delete ui;
}

CoreUI* CoreUI::getDebugPointer(void)                                    { return debugPointer;                                                                                                                 }
bool CoreUI::getReady(void)                                              { return uiReady;                                                                                                                      }
QQuickItem* CoreUI::getMapPointer(void)                                  { return qml;                                                                                                                          }

void CoreUI::InitializeUI()
{
            qDebug()<<"[STARTUP] Starting UI initialization...";
    ui->setupUi(this);
    ui->map->show();
    qml = ui->map->rootObject();
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    uiReady = true;
            qDebug()<<"[STARTUP] UI initialization finished";
            qInfo()<<"[STARTUP] Session started at "+localTime.toString();
    if (QSslSocket::supportsSsl())
        {
                    qInfo() << "[STARTUP] OpenSSL detected: "
                            << QSslSocket::supportsSsl()
                            << ", OpenSSL build version: "
                            << QSslSocket::sslLibraryBuildVersionString()
                            << ", OpenSSL ver.: "
                            << QSslSocket::sslLibraryVersionString();
        }
        else {
                    qCritical() << "[ERROR] OpenSSL detected: "
                                << QSslSocket::supportsSsl()
                                << ", OpenSSL build version: "
                                << QSslSocket::sslLibraryBuildVersionString()
                                << ", OpenSSL ver.: "
                                << QSslSocket::sslLibraryVersionString();
            QMessageBox openSSLDialogue;
            openSSLDialogue.setWindowTitle("Библиотека OpenSSL не обнаружена!");
            openSSLDialogue.setIcon(QMessageBox::Critical);
            openSSLDialogue.setText("Попробуйте переустановить программу.");
            openSSLDialogue.exec();
        }
}
void CoreUI::InitializeConnections()
{
            qInfo()<<"[STARTUP] Setuping connections...";
    linker = new LinkerQML(qml);
    //------------------------------------
    timer = new QTimer(this);
    udpRemote = new UDPRemote();
    tcpRemote = new TCPRemote();
    downloader = new TCPDownloader();
    new Style(true);  //false при сборке релиза
    new SConfig(qml); //вызываем конструктор только один раз, остальное все статическое
    SConfig::loadSettings();
    imageProcessing = new ImageProcessing(linker, this);

    ui->debugConsoleDock->setEnabled(SConfig::DEBUGCONSOLE);
    ui->debugConsoleDock->setVisible(SConfig::DEBUGCONSOLE);

    connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
    connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    connect(tcpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    if(SConfig::CONNECTONSTART)
    {
        if(SConfig::NETWORKTYPE == "TCP"){ tcpRemote->Connect(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT); }
        else
        {
            udpRemote->Connect(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT);
            if(SConfig::NETWORKTYPE != "UDP") { SConfig::NETWORKTYPE = "UDP"; qWarning()<<"[WARNING] Connection type string unrecognized, using UDP by default"; }
                    qInfo()<<"[REMOTE] UDP client connected";
        }
    }//---------------------------------------------< внутренности засунуть в кнопку на случай если в конфиге false;
    timer->start(500);
            qDebug()<<"[STARTUP] Connections set up successfully";

    InitialImageScan();
}

void CoreUI::debugStreamUpdate(QString _text, int msgtype)
{
    if(uiReady)
    {
        if(msgtype == 0) { ui->debugConsole->setTextColor(Qt::gray); }
        else if (msgtype == 1) { ui->debugConsole->setTextColor(Qt::white); }
        else if (msgtype == 2) { ui->debugConsole->setTextColor(Qt::yellow); }
        else if (msgtype == 3) { ui->debugConsole->setTextColor(Qt::red); }
        else if (msgtype == 4) { ui->debugConsole->setTextColor(Qt::darkRed); }
            QFont consoleFont = ui->debugConsole->font();
            consoleFont.setPointSize(7);
        ui->debugConsole->insertPlainText(_text);
        ui->debugConsole->setTextColor(Qt::white);
        ui->debugConsole->setFont(consoleFont);
        QTextCursor c = ui->debugConsole->textCursor();
        c.movePosition(QTextCursor::End);
        ui->debugConsole->setTextCursor(c);
    }
}

/*
 *  С учетом всех оптимизаций полная обработка одного РЛИ занимает 200-300 мс
 *  Это значение умножается на количество НОВЫХ изображений, которые предоставил загрузчик,
 *  либо которые были найдены в каталоге РЛИ.
 *  Метод работает в двух режимах: отображение РЛИ из пути SConfig::PATH, если загрузчик выключен/не отвечает, либо же SConfig::PATH
 *  переопределяется загрузчиком и РЛИ считываются уже с нового пути.
*/
bool CoreUI::InitialImageScan()
{
    bool n;
    if(SConfig::USELOADER) {
        n = imageProcessing->processPath(SConfig::CACHEPATH);
    } else {
        n = imageProcessing->processPath(SConfig::PATH);
    }
    if(imageProcessing->getReadyStatus()==true)
    {
        for(int i = 0; i<=imageProcessing->getVectorSize()-1; i++)
        {
            imageChecklist.append(false);
        }
        imageProcessing->showAllImages(SConfig::SHOWIMAGEONSTART);
    }
    ui->pushButton_showAllImages->setEnabled(n);
    ui->layout_imageTop_2->setEnabled(n);
    ui->layout_imageMiddle_2->setEnabled(n);
    ui->metaGBox->setEnabled(n);

    return n;
}
void CoreUI::Halftime()
{
    //$request запрашивает данные телеметрии в виде строки (ответ = строка вида ($lat@lon@speed@elv#)),
    //$form-SAR-image дает команду на формирование РЛИ (ответ = строка вида ($>>text#))
    if(SConfig::NETWORKTYPE == "TCP"){
        SendRemoteCommand("$request");
    } else {
        SendRemoteCommand("$request");
    }
}
void CoreUI::SendRemoteCommand(QString command)
{
    if(SConfig::NETWORKTYPE == "TCP"){
        tcpRemote->Send(command.toUtf8());
    } else {
        udpRemote->Send(command.toUtf8());
    }
}
void CoreUI::ReadTelemetry(QByteArray data){

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
    updateTelemetryLabels(telemetry[0], telemetry[1], telemetry[2], telemetry[3]);
    linker->getTelemetry((float)telemetry[0], (float)telemetry[1], (float)telemetry[3], (float)telemetry[2]);
}
void CoreUI::on_formImage_triggered() //menu slot (will be removed)
{
            qDebug()<<"[CLIENT] Sending command to form SAR image";
    SendRemoteCommand("$form-SAR-image");
}
void CoreUI::on_openSettings_triggered() //menu slot
{
    SettingsDialog sd(this);
    QString s = SConfig::PATH;
    if(sd.exec() == QDialog::Accepted)
    {
        if(s!=SConfig::PATH)
        {
            InitialImageScan();
        } else { qInfo()<<"[CONFIG] Path unchanged, no further scans"; }
        ui->debugConsoleDock->setEnabled(SConfig::DEBUGCONSOLE); ui->debugConsoleDock->setVisible(SConfig::DEBUGCONSOLE);

        SConfig::saveSettings();
    } else { SConfig::loadSettings(); }
}
void CoreUI::on_checkBox_drawTooltip_stateChanged(int arg1) { linker->changeEnableTooltip(arg1);                                                                                            }
void CoreUI::on_checkBox_drawTrack_stateChanged(int arg1)   { linker->changeDrawRoute(arg1);                                                                                                }
void CoreUI::on_checkBox_stateChanged(int arg1)             { linker->changeFollowPlane(arg1);                                                                                              }
void CoreUI::on_pushButton_panGPS_clicked()                 { linker->panGPS();                                                                                                             }
void CoreUI::on_pushButton_update_clicked()                 { bool b = InitialImageScan(); if(b) { ui->pushButton_showImage->setChecked(imageChecklist[imageProcessing->getFileCounter()]);}}
void CoreUI::on_pushButton_goLeft_clicked()                 { imageProcessing->goLeft(); ui->pushButton_showImage->setChecked(imageChecklist[imageProcessing->getFileCounter()]);           }
void CoreUI::on_pushButton_goRight_clicked()                { imageProcessing->goRight(); ui->pushButton_showImage->setChecked(imageChecklist[imageProcessing->getFileCounter()]);          }
void CoreUI::on_pushButton_clearTrack_clicked()
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
void CoreUI::on_pushButton_panImage_clicked()
{
    linker->panImage(imageProcessing->getFileCounter());
    ui->checkBox->setChecked(false);
    on_checkBox_stateChanged(0);
}
void CoreUI::on_pushButton_showImage_clicked()
{
    if(imageProcessing->getReadyStatus()==true)
    {
        imageChecklist[imageProcessing->getFileCounter()] = !imageChecklist[imageProcessing->getFileCounter()];
        ImageChecklistLoop();
    }
}
void CoreUI::ImageChecklistLoop()
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
void CoreUI::on_pushButton_showAllImages_clicked()
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
void CoreUI::updateTelemetryLabels(float lat, float lon, float speed, float elevation)
{
    ui->label_c_telemetrylat->setText(Style::StyleText(QString::number(lat, 'f', 7), Colors::Main, Format::Bold));
    ui->label_c_telemetrylon->setText(Style::StyleText(QString::number(lon, 'f', 7), Colors::Main, Format::Bold));
    ui->label_c_telemetryspd->setText(Style::StyleText(QString::number(speed, 'f', 1), Colors::Main, Format::Bold));
    ui->label_c_telemetryelv->setText(Style::StyleText(QString::number(elevation, 'f', 1), Colors::Main, Format::Bold));
}
void CoreUI::updateImageManagerLabels(int total, int current)
{
    ui->label_c_foundImages->setText(
                "Найдено "
                +Style::StyleText(QString::number(total), Colors::Accent, Format::Bold)
                +" изображений");
    ui->label_c_currentImage->setText(
                "Изображение "
                +Style::StyleText(QString::number(current+1), Colors::Main, Format::Bold)
                +" из "
                +Style::StyleText(QString::number(total), Colors::NoColor, Format::Bold));
}
void CoreUI::updateImageMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, QString hexSum, QString datetime, bool match)
{
    ui->label_c_metaFilename->setText(filename);
    ui->label_c_metaLat->setText(QString::number(lat));
    ui->label_c_metaLon->setText(QString::number(lon));
    ui->label_c_metaDx->setText(QString::number(dx));
    ui->label_c_metaDy->setText(QString::number(dy));
    ui->label_c_metaX0->setText(QString::number(x0));
    ui->label_c_metaY0->setText(QString::number(y0));
    ui->label_c_metaAngle->setText(QString::number(angle));
    ui->label_c_metaDAngle->setText(QString::number(driftAngle));
    ui->label_c_metaChecksum->setText(hexSum);
    ui->label_c_metaTime->setText(datetime);
    (match) ? ui->label_c_checksumSuccess->setText(Style::StyleText("да", Colors::Success)) : ui->label_c_checksumSuccess->setText(Style::StyleText("нет", Colors::Failure));
}
void CoreUI::setPushButton_goLeftEnabled(bool state)            { ui->pushButton_goLeft->setEnabled(state);                     }
void CoreUI::setPushButton_goRightEnabled(bool state)           { ui->pushButton_goRight->setEnabled(state);                    }
