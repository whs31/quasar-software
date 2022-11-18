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
                               QString cfg_path,
                               bool cfg_showImageOnStart,
                               bool cfg_connectOnStart) : QDialog(parent), uiS(new Ui::SettingsDialog),
                                                                        cfg_connectionType(cfg_connectionType),
                                                                        cfg_connectionAddress(cfg_connectionAddress),
                                                                        cfg_connectionPort(cfg_connectionPort),
                                                                        cfg_refreshTime(cfg_refreshTime),
                                                                        cfg_predictRange(cfg_predictRange),
                                                                        cfg_driftAngle(cfg_driftAngle),
                                                                        cfg_thetaAzimuth(cfg_thetaAzimuth),
                                                                        cfg_captureRange(cfg_captureRange),
                                                                        cfg_captureTime(cfg_captureTime),
                                                                        cfg_antennaPosition(cfg_antennaPosition),
                                                                        cfg_path(cfg_path),
                                                                        cfg_showImageOnStart(cfg_showImageOnStart),
                                                                        cfg_connectOnStart(cfg_connectOnStart)
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
    uiS->i_showImages->setChecked(cfg_showImageOnStart);
    uiS->i_connectOnStart->setChecked(cfg_connectOnStart);
    if(cfg_antennaPosition == "r") { uiS->i_antennaRightB->setChecked(true); uiS->i_antennaLeftB->setChecked(false); } else { uiS->i_antennaRightB->setChecked(false); uiS->i_antennaLeftB->setChecked(true); }
}

SettingsDialog::~SettingsDialog()
{
    delete uiS;
}

void SettingsDialog::on_i_networktype_editingFinished()                                { cfg_connectionType = uiS->i_networktype->text();                                                                                  }
void SettingsDialog::on_i_networkip_editingFinished()                                     { cfg_connectionAddress = uiS->i_networkip->text();                                                                                 }
void SettingsDialog::on_i_networkport_editingFinished()                                { cfg_connectionPort = uiS->i_networkport->text();                                                                                  }
void SettingsDialog::on_i_updateTime_valueChanged(double arg1)            { cfg_refreshTime = uiS->i_updateTime->value();                                                                                     }
void SettingsDialog::on_i_predictRange_valueChanged(double arg1)         { cfg_predictRange = uiS->i_predictRange->value();                                                                                  }
void SettingsDialog::on_i_driftAngle_valueChanged(double arg1)               { cfg_driftAngle = uiS->i_driftAngle->value();                                                                                      }
void SettingsDialog::on_i_captureRange_valueChanged(double arg1)        { cfg_captureRange = uiS->i_captureRange->value();                                                                                  }
void SettingsDialog::on_i_azimuth_valueChanged(double arg1)                    { cfg_thetaAzimuth = uiS->i_azimuth->value();                                                                                       }
void SettingsDialog::on_i_captureTime_valueChanged(double arg1)           { cfg_captureTime = uiS->i_captureTime->value();                                                                                    }
void SettingsDialog::on_i_antennaLeftB_clicked()                                               { cfg_antennaPosition = "l";                                                                                                        }
void SettingsDialog::on_i_antennaRightB_clicked()                                            { cfg_antennaPosition = "r";                                                                                                        }
void SettingsDialog::on_pushButton_clicked()                                                      {
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(this, tr("Выберите папку с выходными изображениями РЛС"), QStandardPaths::displayName(QStandardPaths::HomeLocation));
                                     if(pathNotNullCheck!=NULL) { cfg_path = pathNotNullCheck; }                                                                                                    }
void SettingsDialog::on_i_showImages_stateChanged(int arg1)                    { bool b = (arg1==2) ? true : false; cfg_showImageOnStart = b;                                                                      }
void SettingsDialog::on_i_connectOnStart_stateChanged(int arg1)             { bool b = (arg1==2) ? true : false; cfg_connectOnStart = b;                                                                        }
