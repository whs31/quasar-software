#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSslSocket>
#include <QTimer>

#include "udpremote.h"
#include "tcpremote.h"
#include "confighandler.h"
#include "settingsdialog.h"
#include "imageprocessing.h"

#include "htmltags.h"
#include "linkerqml.h"

//классы, имеющие обратную связь с мейнвиндоу в виде вызова функции без системы сигнал-слот
//это надо фиксить =)
class ConfigHandler;
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
    //static MainWindow * getMainWinPtr();

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
    bool C_SHOWIMAGEONSTART;
    bool C_CONNECTONSTART;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------

    //ui setters
    void updateTelemetryLabels(float lat, float lon, float speed, float elevation);
    void updateImageManagerLabels(int total, int current);
    void updateImageMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, QString hexSum, QString datetime, bool match);
    void setPushButton_goLeftEnabled(bool state);
    void setPushButton_goRightEnabled(bool state);
    //getters
    void getConfig(QString s1, QString s2, QString s3, float f1, float f2, float f3, float f4, float f5, float f6, QString s4, QString s5, bool b1, bool b2);



private:
    Ui::MainWindow *ui;
    //static MainWindow * pMainWindow;
    HTMLTags *html;
    UDPRemote *udpRemote;
    TCPRemote *tcpRemote;
    ConfigHandler *config;
    QTimer *timer;
    ImageProcessing *imageProcessing;
    LinkerQML *linker;

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
