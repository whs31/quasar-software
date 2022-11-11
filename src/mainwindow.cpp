#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow * MainWindow::pMainWindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    pMainWindow = this;
    ui->setupUi(this);

    ui->map->show();
    qml = ui->map->rootObject();

    timer = new QTimer(this);
    udpRemote = new UDPRemote();
    tcpRemote = new TCPRemote();

    connect(timer, SIGNAL(timeout()), this, SLOT(Halftime()));
    connect(udpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    connect(tcpRemote, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));
    if(CONNECTION_TYPE == "tcp"){
        tcpRemote->Connect(CONNECTION_ADDRESS);

    } else {
        udpRemote->Connect(CONNECTION_ADDRESS);
        if(CONNECTION_TYPE != "udp") { CONNECTION_TYPE = "udp"; qWarning()<<"Connection type string unrecognized, using UDP by default"; }
        qInfo()<<"UDP client connected";
    }
    timer->start(500);
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

void MainWindow::Halftime()
{
    //$request запрашивает данные телеметрии в виде строки (ответ = строка вида ($lat@lon@speed@elv#)),
    //$form-SAR-image дает команду на формирование РЛИ (ответ = строка вида ($text#))
    if(CONNECTION_TYPE == "tcp"){
        tcpRemote->Send("$request");
    } else {
        udpRemote->Send("$request");
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
            QMetaObject::invokeMethod(qml, "getMessage", Q_ARG(QVariant, parsedMessage));
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
