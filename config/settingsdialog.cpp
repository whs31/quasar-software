#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), uiS(new Ui::SettingsDialog)
{
    uiS->setupUi(this);

    uiS->i_networktype->setText(SConfig::getHashString("NetworkType"));
    uiS->i_networkip->setText(SConfig::getHashString("SarIP"));
    uiS->i_networkport->setText(SConfig::getHashString("TelemetryPort"));
    uiS->i_updateTime->setValue(SConfig::getHashFloat("TelemetryFrequency"));
    uiS->i_predictRange->setValue(SConfig::getHashFloat("VelocityVectorLength"));
    uiS->i_driftAngle->setValue(SConfig::getHashFloat("DiagramDriftAngle"));
    uiS->i_azimuth->setValue(SConfig::getHashFloat("DiagramThetaAzimuth"));
    uiS->i_captureRange->setValue(SConfig::getHashFloat("DiagramCaptureRange"));
    uiS->i_captureTime->setValue(SConfig::getHashFloat("DiagramCaptureTime"));
    uiS->i_showImages->setChecked(SConfig::getHashBoolean("StartupShowAll"));
    uiS->i_connectOnStart->setChecked(SConfig::getHashBoolean("StartupConnectToSAR"));
    uiS->i_debugConsole->setChecked(SConfig::getHashBoolean("ShowConsole"));
    uiS->i_useLoader->setChecked(SConfig::getHashBoolean("Mode"));
    uiS->i_saveOnlyAtEnd->setChecked(SConfig::getHashBoolean("SaveNonContinuous"));
    uiS->i_loaderIp->setText(SConfig::getHashString("LoaderIP"));
    uiS->i_loaderPort->setText(SConfig::getHashString("LoaderPort"));
    uiS->i_usebase64->setChecked(SConfig::getHashBoolean("Base64Enabled"));
    uiS->i_formImagePort->setText(SConfig::getHashString("DialogPort"));
}

SettingsDialog::~SettingsDialog() { delete uiS; }
void SettingsDialog::on_pushButton_clicked() {
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(this,
                                                                tr("Выберите папку с выходными изображениями РЛС"),
                                                                QStandardPaths::displayName(QStandardPaths::HomeLocation));
    if(pathNotNullCheck!=NULL) { SConfig::setHashValue("ViewPath", pathNotNullCheck); }
}
void SettingsDialog::on_buttonBox_rejected() { reject(); }

void SettingsDialog::on_buttonBox_accepted()
{
    SConfig::setHashValue("NetworkType", uiS->i_networktype->text());
    SConfig::setHashValue("SarIP", uiS->i_networkip->text());
    SConfig::setHashValue("TelemetryPort", uiS->i_networkport->text());
    SConfig::setHashValue("DialogPort", uiS->i_formImagePort->text());
    SConfig::setHashValue("LoaderIP", uiS->i_loaderIp->text());
    SConfig::setHashValue("LoaderPort", uiS->i_loaderPort->text());
    SConfig::setHashValue("TelemetryFrequency", uiS->i_updateTime->value());
    SConfig::setHashValue("VelocityVectorLength", uiS->i_predictRange->value());
    SConfig::setHashValue("DiagramDriftAngle", uiS->i_driftAngle->value());
    SConfig::setHashValue("DiagramCaptureRange", uiS->i_captureRange->value());
    SConfig::setHashValue("DiagramThetaAzimuth", uiS->i_azimuth->value());
    SConfig::setHashValue("DiagramCaptureTime", uiS->i_captureTime->value());
    //SConfig::setHashValue("AntennaPosition", uiS->i_antennaLeftB->isChecked());
    SConfig::setHashValue("StartupShowAll", uiS->i_showImages->isChecked());
    SConfig::setHashValue("StartupConnectToSAR", uiS->i_connectOnStart->isChecked());
    SConfig::setHashValue("Base64Enabled", uiS->i_usebase64->isChecked());
    SConfig::setHashValue("ShowConsole", uiS->i_debugConsole->isChecked());
    SConfig::setHashValue("Mode", uiS->i_useLoader->isChecked());
    SConfig::setHashValue("SaveNonContinuous", uiS->i_saveOnlyAtEnd->isChecked());
    accept();
}


