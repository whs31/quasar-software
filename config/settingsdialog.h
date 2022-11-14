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
    ~SettingsDialog();

signals:

private:
    Ui::SettingsDialog *uiS;
};

#endif // SETTINGSDIALOG_H
