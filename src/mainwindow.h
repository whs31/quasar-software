#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qt-includes.h"

#include "udpremote.h"
#include "tcpremote.h"
#include "confighandler.h"
#include "settingsdialog.h"
#include "imageprocessing.h"


class UDPRemote;
class TCPRemote;
class ConfigHandler;
class SettingsDialog;
class ImageProcessing;

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
    friend class SettingsDialog;
    friend class ImageProcessing;
    QQuickItem* qml;

    void SendRemoteCommand(QString command);


    double telemetry[4]; //lat, lon, speed, elevation

    //-----config values--------- //эти значения обновляются классом configHandler при вызове loadSettings и передаются в settingsDialog при инициализации окна
    QString C_NETWORKTYPE;
    QString C_NETWORKADDRESS;
    QString C_NETWORKPORT;
    float C_UPDATETIME;
    float C_PREDICTRANGE;
    float C_CAPTURERANGE;
    float C_CAPTURETIME;
    float C_AZIMUTH;
    float C_DRIFTANGLE;
    QString C_ANTENNAPOSITION;
    QString C_PATH;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------

    //colors for text
    QString HtmlColorMain = "<font color=\"#2ECC71\">";
    QString HtmlColorMainFaded = "<font color=\"#27AE60\">";
    QString HtmlColorMainAccent = "<font color=\"#F1C40F\">";
    QString HtmlColorSuccess = "<font color=\"#CDDC39\">";
    QString HtmlColorFailure = "<font color=\"#EF5350\">";
    QString HtmlColorEnd = "</font>";
    //html tags
    QString HtmlBold = "<b>";
    QString HtmlBoldEnd = "</b>";

private:
    Ui::MainWindow *ui;
    static MainWindow * pMainWindow;
    UDPRemote *udpRemote;
    TCPRemote *tcpRemote;
    ConfigHandler *config;
    QTimer *timer;
    ImageProcessing *imageProcessing;

    QVector<bool> imageChecklist;
    void ImageChecklistLoop();
    void InitializeUI();
    void InitializeConnections();
    bool InitialImageScan();

signals:


private slots:
    void ReadTelemetry(QByteArray data);
    void Halftime();

    //top menu
    void on_formImage_triggered();
    void on_openSettings_triggered();

    //user interface
    void on_checkBox_drawTooltip_stateChanged(int arg1);
    void on_checkBox_drawTrack_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_clearTrack_clicked();
    void on_pushButton_panGPS_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_goLeft_clicked();
    void on_pushButton_goRight_clicked();
    void on_pushButton_panImage_clicked();
    void on_pushButton_panImage_2_clicked();
    void on_pushButton_showImage_clicked();
    void on_pushButton_showAllImages_clicked();
};
#endif // MAINWINDOW_H
