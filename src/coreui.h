#ifndef COREUI_H
#define COREUI_H

#include <QMainWindow>
#include <QSslSocket>
#include <QTimer>

#include "udpremote.h"
#include "tcpremote.h"
#include "settingsdialog.h"
#include "imageprocessing.h"

#include "style.h"
#include "linkerqml.h"
#include "sconfig.h"
#include "tcpdownloader.h"

//классы, имеющие обратную связь с мейнвиндоу в виде вызова функции без системы сигнал-слот
//это надо фиксить =)
class ConfigHandler;
class ImageProcessing;
//--------

QT_BEGIN_NAMESPACE
namespace Ui { class CoreUI; }
QT_END_NAMESPACE

class CoreUI : public QMainWindow
{
    Q_OBJECT

public:
    CoreUI(QWidget *parent = nullptr);
    ~CoreUI();
    static CoreUI* getDebugPointer(void);
    QQuickItem* qml;

    void SendRemoteCommand(QString command);
    void debugStreamUpdate(QString _text, int msgtype);
    double telemetry[4]; //lat, lon, speed, elevation

    //ui setters
    void updateTelemetryLabels(float lat, float lon, float speed, float elevation);
    void updateImageManagerLabels(int total, int current);
    void updateImageMetaLabels(QString filename, float lat, float lon, float dx, float dy, float x0, float y0, float angle, float driftAngle, QString hexSum, QString datetime, bool match);
    void setPushButton_goLeftEnabled(bool state);
    void setPushButton_goRightEnabled(bool state);
    //getters
    void getConfig(QString s1, QString s2, QString s3, float f1, float f2, float f3, float f4, float f5, float f6, QString s4, QString s5, bool b1, bool b2, bool b3);
    bool getReady(void);
    QQuickItem* getMapPointer(void);



private:
    Ui::CoreUI *ui;
    static CoreUI* debugPointer;
    UDPRemote *udpRemote;
    TCPRemote *tcpRemote;
    ConfigHandler *config;
    QTimer *timer;
    ImageProcessing *imageProcessing;
    LinkerQML *linker;
    TCPDownloader *downloader;

    bool uiReady = false;

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
    void on_pushButton_showImage_clicked();
    void on_pushButton_showAllImages_clicked();
};
#endif // COREUI_H
