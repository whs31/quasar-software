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
                               QString cfg_antennaPosition,
                               QString cfg_path) : QDialog(parent), uiS(new Ui::SettingsDialog)
{
    uiS->setupUi(this);
    uiS->i_networktype->setText(cfg_connectionType);
    uiS->i_networkip->setText(cfg_connectionAddress);
    uiS->i_networkport->setText(cfg_connectionPort);
    uiS->i_updateTime->setValue(cfg_refreshTime);
    uiS->i_predictRange->setValue(cfg_predictRange);
    uiS->i_driftAngle->setValue(cfg_driftAngle);
    uiS->i_azimuth->setValue(cfg_thetaAzimuth);
    uiS->i_captureRange->setValue(cfg_captureRange);
    uiS->i_captureTime->setValue(cfg_captureTime);
    if(cfg_antennaPosition == "r") { uiS->i_antennaRightB->setChecked(true); uiS->i_antennaLeftB->setChecked(false); } else { uiS->i_antennaRightB->setChecked(false); uiS->i_antennaLeftB->setChecked(true); }

    r_connectionType = cfg_connectionType; r_connectionAddress = cfg_connectionAddress; r_connectionPort = cfg_connectionPort; r_refreshTime = cfg_refreshTime; r_predictRange = cfg_predictRange;
    r_driftAngle = cfg_driftAngle; r_thetaAzimuth = cfg_thetaAzimuth; r_captureRange = cfg_captureRange; r_captureTime = cfg_captureTime; r_antennaPosition = cfg_antennaPosition; r_path = cfg_path;
}

SettingsDialog::~SettingsDialog()
{
    delete uiS;
}

void SettingsDialog::on_i_networktype_editingFinished()
{
    r_connectionType = uiS->i_networktype->text();
}

void SettingsDialog::on_i_networkip_editingFinished()
{
    r_connectionAddress = uiS->i_networkip->text();
}

void SettingsDialog::on_i_networkport_editingFinished()
{
    r_connectionPort = uiS->i_networkport->text();
}

void SettingsDialog::on_i_updateTime_valueChanged(double arg1)
{
    r_refreshTime = uiS->i_updateTime->value();
}

void SettingsDialog::on_i_predictRange_valueChanged(double arg1)
{
    r_predictRange = uiS->i_predictRange->value();
}

void SettingsDialog::on_i_driftAngle_valueChanged(double arg1)
{
    r_driftAngle = uiS->i_driftAngle->value();
}

void SettingsDialog::on_i_captureRange_valueChanged(double arg1)
{
    r_captureRange = uiS->i_captureRange->value();
}

void SettingsDialog::on_i_azimuth_valueChanged(double arg1)
{
    r_thetaAzimuth = uiS->i_azimuth->value();
}

void SettingsDialog::on_i_captureTime_valueChanged(double arg1)
{
    r_captureTime = uiS->i_captureTime->value();
}

void SettingsDialog::on_i_antennaLeftB_clicked()
{
    r_antennaPosition = "l";
}

void SettingsDialog::on_i_antennaRightB_clicked()
{
    r_antennaPosition = "r";
}

void SettingsDialog::on_pushButton_clicked()
{
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(this, tr("Выберите папку с выходными изображениями РЛС"),
                                                                     QStandardPaths::displayName(QStandardPaths::HomeLocation));
    if(pathNotNullCheck!=NULL)
    {
        r_path = pathNotNullCheck;
    }
}
