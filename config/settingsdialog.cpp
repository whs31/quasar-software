#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent, QString cfg_connectionType,
                               QString cfg_connectionAddress,
                               QString cfg_connectionPort,
                               float cfg_refreshTime,
                               float cfg_predictRange,
                               float cfg_driftAngle,
                               float cfg_thetaAzimuth,
                               float cfg_captureRange,
                               float cfg_captureTime,
                               QString cfg_antennaPosition) : QDialog(parent), uiS(new Ui::SettingsDialog)
{
    uiS->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete uiS;
}
