#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>

#include <QTimer>

#include "udpremote.h"
#include "tcpremote.h"

class UDPRemote;
class TCPRemote;

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
    QQuickItem* qml;

    QString CONNECTION_TYPE = "udp"; //"tcp"
    QString CONNECTION_ADDRESS = "127.0.0.1:25565";

    void SendRemoteCommand(QString command);


    double telemetry[3]; //lat, lon, speed, elevation

private:
    Ui::MainWindow *ui;
    static MainWindow * pMainWindow;
    UDPRemote *udpRemote;
    TCPRemote *tcpRemote;
    QTimer *timer;

signals:

private slots:
    void ReadTelemetry(QByteArray data);
    void Halftime();

};
#endif // MAINWINDOW_H
