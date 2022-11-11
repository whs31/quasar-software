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

MainWindow *MainWindow::getMainWinPtr()
{
    return pMainWindow;
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
    timer = new QTimer(this);
    udpRemote = new UDPRemote();
    tcpRemote = new TCPRemote();
    config = new ConfigHandler();
    config->loadSettings();

    connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
    connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    connect(tcpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    if(CONNECTION_TYPE == "tcp"){ tcpRemote->Connect(CONNECTION_ADDRESS); }
    else
    {
        udpRemote->Connect(CONNECTION_ADDRESS);
        if(CONNECTION_TYPE != "udp") { CONNECTION_TYPE = "udp"; qWarning()<<"[WARNING] Connection type string unrecognized, using UDP by default"; }
        qInfo()<<"UDP client connected";
    }
    timer->start(500);
    qInfo()<<"[STARTUP] Connections set up successfully";
}

void MainWindow::Halftime()
{
    //$request запрашивает данные телеметрии в виде строки (ответ = строка вида ($lat@lon@speed@elv#)),
    //$form-SAR-image дает команду на формирование РЛИ (ответ = строка вида ($text#))
    if(CONNECTION_TYPE == "tcp"){
        SendRemoteCommand("$request");
    } else {
        SendRemoteCommand("$request");
    }
}

void MainWindow::SendRemoteCommand(QString command)
{
    if(CONNECTION_TYPE == "tcp"){
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
            //QMetaObject::invokeMethod(qml, "getMessage", Q_ARG(QVariant, parsedMessage));
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
    ui->label_c_telemetrylat->setText(HtmlColorMain+HtmlBold+QString::number(telemetry[0], 'f', 7)+HtmlBoldEnd+HtmlColorEnd);
    ui->label_c_telemetrylon->setText(HtmlColorMain+HtmlBold+QString::number(telemetry[1], 'f', 7)+HtmlBoldEnd+HtmlColorEnd);
    ui->label_c_telemetryspd->setText(HtmlColorMain+HtmlBold+QString::number(telemetry[2], 'f', 3)+HtmlBoldEnd+HtmlColorEnd);
    ui->label_c_telemetryelv->setText(HtmlColorMain+HtmlBold+QString::number(telemetry[3], 'f', 3)+HtmlBoldEnd+HtmlColorEnd);
    QMetaObject::invokeMethod(qml, "getTelemetry", Q_ARG(QVariant, telemetry[0]), Q_ARG(QVariant, telemetry[1]), Q_ARG(QVariant, telemetry[2]), Q_ARG(QVariant, telemetry[3]));
}

void MainWindow::on_formImage_triggered()
{
    qInfo()<<"[CLIENT] Sending command to form SAR image";
    SendRemoteCommand("$form-SAR-image");
}

void MainWindow::on_checkBox_drawTooltip_stateChanged(int arg1)
{
    QMetaObject::invokeMethod(qml, "changeEnableTooltip", Q_ARG(QVariant, arg1));
}

void MainWindow::on_checkBox_drawTrack_stateChanged(int arg1)
{
    QMetaObject::invokeMethod(qml, "changeDrawRoute", Q_ARG(QVariant, arg1));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    QMetaObject::invokeMethod(qml, "changeFollowPlane", Q_ARG(QVariant, arg1));
}

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
    case QMessageBox::Yes: QMetaObject::invokeMethod(qml, "clearRoute");
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_panGPS_clicked()
{
    QMetaObject::invokeMethod(qml, "panGPS");
}
