#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QObject>
#include "qt-includes.h"


namespace Ui {
class SettingsDialog;
}
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr,
                   QString cfg_connectionType = "",
                   QString cfg_connectionAddress = "",
                   QString cfg_connectionPort = "",
                   float cfg_refreshTime = 0,
                   float cfg_predictRange = 0,
                   float cfg_driftAngle = 0,
                   float cfg_thetaAzimuth = 0,
                   float cfg_captureRange = 0,
                   float cfg_captureTime = 0,
                   QString cfg_antennaPosition = "",
                   QString cfg_path = "",
                   bool cfg_showImageOnStart = 1,
                   bool cfg_connectOnStart = 1);

    //обратная связь
    QString cfg_connectionType;
    QString cfg_connectionAddress;
    QString cfg_connectionPort;
    float cfg_refreshTime;
    float cfg_predictRange;
    float cfg_driftAngle;
    float cfg_thetaAzimuth;
    float cfg_captureRange;
    float cfg_captureTime;
    QString cfg_antennaPosition;
    QString cfg_path;
    bool cfg_showImageOnStart;
    bool cfg_connectOnStart;
    ~SettingsDialog();

signals:

private slots:
    void on_i_networktype_editingFinished();
    void on_i_networkip_editingFinished();
    void on_i_networkport_editingFinished();
    void on_i_updateTime_valueChanged(double arg1);
    void on_i_predictRange_valueChanged(double arg1);
    void on_i_driftAngle_valueChanged(double arg1);
    void on_i_captureRange_valueChanged(double arg1);
    void on_i_azimuth_valueChanged(double arg1);
    void on_i_captureTime_valueChanged(double arg1);
    void on_i_antennaLeftB_clicked();
    void on_i_antennaRightB_clicked();
    void on_pushButton_clicked();

    void on_i_showImages_stateChanged(int arg1);

    void on_i_connectOnStart_stateChanged(int arg1);

private:
    Ui::SettingsDialog *uiS;
};

#endif // SETTINGSDIALOG_H
