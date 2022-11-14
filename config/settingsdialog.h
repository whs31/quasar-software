#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QObject>
#include <QInputDialog>

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
                   QString cfg_antennaPosition = "");

    //обратная связь
    QString r_connectionType;
    QString r_connectionAddress;
    QString r_connectionPort;
    float r_refreshTime;
    float r_predictRange;
    float r_driftAngle;
    float r_thetaAzimuth;
    float r_captureRange;
    float r_captureTime;
    QString r_antennaPosition;
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

private:
    Ui::SettingsDialog *uiS;
};

#endif // SETTINGSDIALOG_H
