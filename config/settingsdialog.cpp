#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), uiS(new Ui::SettingsDialog)
{
    uiS->setupUi(this);

    uiS->password->setText(SConfig::getHashString("SudoPassword"));
    uiS->networkType->setText(SConfig::getHashString("NetworkType"));
    uiS->sarIP->setText(SConfig::getHashString("SarIP"));
    uiS->telPort->setText(SConfig::getHashString("TelemetryPort"));
    uiS->telUpdateTime->setValue(SConfig::getHashFloat("TelemetryFrequency"));
    uiS->vectorLength->setValue(SConfig::getHashFloat("VelocityVectorLength"));
    uiS->azimuth->setValue(SConfig::getHashFloat("DiagramThetaAzimuth"));
    uiS->useConsole->setChecked(SConfig::getHashBoolean("ShowConsole"));
    if(SConfig::getHashBoolean("Mode")) { on_flightMode_clicked(); } else { on_viewMode_clicked(); }
    uiS->saveAtEnd->setChecked(SConfig::getHashBoolean("SaveNonContinuous"));
    uiS->loaderIP->setText(SConfig::getHashString("LoaderIP"));
    uiS->loaderPort->setText(SConfig::getHashString("LoaderPort"));
    uiS->useBase64->setChecked(SConfig::getHashBoolean("Base64Enabled"));
    uiS->commandPort->setText(SConfig::getHashString("DialogPort"));
    uiS->consolePort->setText(SConfig::getHashString("ListenPort"));
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
    SConfig::setHashValue("NetworkType", uiS->networkType->text());
    SConfig::setHashValue("SudoPassword", uiS->password->text());
    SConfig::setHashValue("SarIP", uiS->sarIP->text());
    SConfig::setHashValue("TelemetryPort", uiS->telPort->text());
    SConfig::setHashValue("DialogPort", uiS->commandPort->text());
    SConfig::setHashValue("ListenPort", uiS->consolePort->text());
    SConfig::setHashValue("LoaderIP", uiS->loaderIP->text());
    SConfig::setHashValue("LoaderPort", uiS->loaderPort->text());
    SConfig::setHashValue("TelemetryFrequency", uiS->telUpdateTime->value());
    SConfig::setHashValue("VelocityVectorLength", uiS->vectorLength->value());
    SConfig::setHashValue("DiagramThetaAzimuth", uiS->azimuth->value());
    SConfig::setHashValue("AntennaPosition", (uiS->antennaLeft->isChecked()) ? "l" : "r");
    SConfig::setHashValue("Base64Enabled", uiS->useBase64->isChecked());
    SConfig::setHashValue("ShowConsole", uiS->useConsole->isChecked());
    SConfig::setHashValue("Mode", mode);
    SConfig::setHashValue("SaveNonContinuous", uiS->saveAtEnd->isChecked());
    accept();
}

void SettingsDialog::on_flightMode_clicked()
{
    uiS->viewMode->setStyleSheet("");
    uiS->flightMode->setStyleSheet("background-color: rgb(170, 170, 255);");
    mode = true;
}

void SettingsDialog::on_viewMode_clicked()
{
    uiS->flightMode->setStyleSheet("");
    uiS->viewMode->setStyleSheet("background-color: rgb(255, 170, 127);");
    mode = false;
}
