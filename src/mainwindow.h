#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>

#include <QTimer>
#include <QSslSocket>
#include <QDialog>
#include <QMessageBox>

#include "udpremote.h"
#include "tcpremote.h"
#include "confighandler.h"

class UDPRemote;
class TCPRemote;
class ConfigHandler;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow * getMainWinPtr();
    friend class UDPRemote;
    friend class TCPRemote;
    friend class ConfigHandler;
    QQuickItem* qml;

    QString CONNECTION_TYPE = "udp"; //"tcp"
    QString CONNECTION_ADDRESS = "127.0.0.1:25565";

    void SendRemoteCommand(QString command);


    double telemetry[4]; //lat, lon, speed, elevation

private:
    Ui::MainWindow *ui;
    static MainWindow * pMainWindow;
    UDPRemote *udpRemote;
    TCPRemote *tcpRemote;
    ConfigHandler *config;
    QTimer *timer;
    void InitializeUI();
    void InitializeConnections();

    //colors for text
    QString HtmlColorMain = "<font color=\"#2ECC71\">";
    QString HtmlColorMainFaded = "<font color=\"#27AE60\">";
    QString HtmlColorMainAccent = "<font color=\"#F1C40F\">";
    QString HtmlColorEnd = "</font>";
    //html tags
    QString HtmlBold = "<b>";
    QString HtmlBoldEnd = "</b>";

signals:


private slots:
    void ReadTelemetry(QByteArray data);
    void Halftime();

    void on_formImage_triggered();
    void on_checkBox_drawTooltip_stateChanged(int arg1);
    void on_checkBox_drawTrack_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_clearTrack_clicked();
    void on_pushButton_panGPS_clicked();
};
#endif // MAINWINDOW_H
