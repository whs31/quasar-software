#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), uiS(new Ui::SettingsDialog)
{
    uiS->setupUi(this);

    uiS->password->setText(SConfig::get()->getSudoPassword());
    uiS->networkType->setText(SConfig::get()->getNetworkType());
    uiS->sarIP->setText(SConfig::get()->getDE10IP());
    uiS->telPort->setText(SConfig::get()->getTelemetryPort());
    uiS->telUpdateTime->setValue(SConfig::get()->getTelemetryFrequency());
    uiS->vectorLength->setValue(SConfig::get()->getVelocityVectorLength());
    uiS->azimuth->setValue(SConfig::get()->getDiagramThetaAzimuth());
    uiS->useConsole->setChecked(SConfig::get()->getDebugConsole());
    uiS->loaderIP->setText(SConfig::get()->getComputerIP());
    uiS->loaderPort->setText(SConfig::get()->getLoaderPort());
    uiS->commandPort->setText(SConfig::get()->getExecdPort());
    uiS->consolePort->setText(SConfig::get()->getTerminalPort());

    uiS->useOSM->setChecked(SConfig::get()->getOnlineMaps());
    uiS->metaInRadians->setChecked(SConfig::get()->getGlobalRadians());
    uiS->angleCorrection->setValue(SConfig::get()->getAngleCorrection());
    uiS->globalDriftAngle->setChecked(SConfig::get()->getUseDriftAngle());
    uiS->thetaAzimuthCorrection->setValue(SConfig::get()->getThetaAzimuthCorrection());
}

SettingsDialog::~SettingsDialog() { delete uiS; }
void SettingsDialog::on_pushButton_clicked() {
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(this,
                                                                tr("Выберите папку с выходными изображениями РЛС"),
                                                                QStandardPaths::displayName(QStandardPaths::HomeLocation));
    if(pathNotNullCheck != NULL) { SConfig::get()->setDefaultCatalogue(pathNotNullCheck); }
}
void SettingsDialog::on_buttonBox_rejected() { reject(); }

void SettingsDialog::on_buttonBox_accepted()
{
    SConfig::get()->setNetworkType(uiS->networkType->text());
    SConfig::get()->setSudoPassword(uiS->password->text());
    SConfig::get()->setDE10IP(uiS->sarIP->text());
    SConfig::get()->setTelemetryPort(uiS->telPort->text());
    SConfig::get()->setExecdPort(uiS->commandPort->text());
    SConfig::get()->setTerminalPort(uiS->consolePort->text());
    SConfig::get()->setComputerIP(uiS->loaderIP->text());
    SConfig::get()->setLoaderPort(uiS->loaderPort->text());
    SConfig::get()->setTelemetryFrequency(uiS->telUpdateTime->value());
    SConfig::get()->setVelocityVectorLength(uiS->vectorLength->value());
    SConfig::get()->setDiagramThetaAzimuth(uiS->azimuth->value());
    SConfig::get()->setAntennaPosition((uiS->antennaLeft->isChecked()) ? "left" : "right");
    SConfig::get()->setDebugConsole(uiS->useConsole->isChecked());
    SConfig::get()->setOnlineMaps(uiS->useOSM->isChecked());
    SConfig::get()->setGlobalRadians(uiS->metaInRadians->isChecked());
    SConfig::get()->setAngleCorrection(uiS->angleCorrection->value());
    SConfig::get()->setUseDriftAngle(uiS->globalDriftAngle->isChecked());
    SConfig::get()->setThetaAzimuthCorrection(uiS->thetaAzimuthCorrection->value());
    accept();
}
