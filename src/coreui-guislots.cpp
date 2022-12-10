#include "coreui.h"
#include "ui_coreui.h"

//***************************************************************************************GUI SLOTS************************************************************************************************************
void CoreUI::on_checkBox_drawTooltip_stateChanged(int arg1) { fDynamicVariables->setEnableTooltip(arg1 == 2 ? true : false);                                                                                 }
void CoreUI::on_checkBox_drawTrack_stateChanged(int arg1)   { fDynamicVariables->setEnableRoute(arg1 == 2 ? true : false);                                                                                   }
void CoreUI::on_checkBox_drawPredict_stateChanged(int arg1) { fDynamicVariables->setEnablePredict(arg1 == 2 ? true : false);                                                                                 }
void CoreUI::on_checkBox_drawDiagram_stateChanged(int arg1) { fDynamicVariables->setEnablePredictDiagram(arg1 == 2 ? true : false);                                                                          }
void CoreUI::on_checkBox_stateChanged(int arg1)             { fDynamicVariables->setFollowPlane(arg1 == 2 ? true : false);                                                                                   }
void CoreUI::on_pushButton_panGPS_clicked()                 { linker->panGPS();                                                                                                                              }
void CoreUI::on_pushButton_goLeft_clicked()                 { imageProcessing->goLeft(); ui->pushButton_showImage->setChecked(imageProcessing->imageChecklist[imageProcessing->getFileCounter()]);           }
void CoreUI::on_pushButton_goRight_clicked()                { imageProcessing->goRight(); ui->pushButton_showImage->setChecked(imageProcessing->imageChecklist[imageProcessing->getFileCounter()]);          }
void CoreUI::on_checkBox_autoUpdate_stateChanged(int arg1)  { autoUpdate = ui->checkBox_autoUpdate->isChecked();                                                                                             }
void CoreUI::on_pushButton_expandImageInfo_clicked()        { bool b = ui->showFullInfoContainer->isVisible(); b = !b; ui->showFullInfoContainer->setVisible(b);                                             }
void CoreUI::on_pushButton_update_clicked()                 { imageProcessing->PartialScan();
                                                              if(imageProcessing->getReadyStatus()) { ui->pushButton_showImage->setChecked(
                                                                              imageProcessing->imageChecklist[imageProcessing->getFileCounter()]); }                                                         }
void CoreUI::on_pushButton_panImage_clicked()               { linker->panImage(imageProcessing->getFileCounter()); ui->checkBox->setChecked(false); on_checkBox_stateChanged(0);                             }
void CoreUI::on_pushButton_showImage_clicked()
{
    if(imageProcessing->getReadyStatus()==true)
    {
        imageProcessing->imageChecklist[imageProcessing->getFileCounter()] = !imageProcessing->imageChecklist[imageProcessing->getFileCounter()];
        imageProcessing->imageChecklistLoop();
    }
}
void CoreUI::on_pushButton_clearTrack_clicked()
{
    QMessageBox askForClearTrack;
        askForClearTrack.setWindowTitle("Очистка трека");
        askForClearTrack.setIcon(QMessageBox::Information);
        askForClearTrack.setText("Вы уверены, что хотите полностью очистить трек?");
        askForClearTrack.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        askForClearTrack.setDefaultButton(QMessageBox::Cancel);
        short ret = askForClearTrack.exec();
    switch (ret) {
    case QMessageBox::Yes: linker->clearRoute();
        break;
    case QMessageBox::Cancel: { break; }
    default:
        break;
    }
}
void CoreUI::on_pushButton_showAllImages_clicked()
{
    if(imageProcessing->getReadyStatus()==true)
    {
        if(imageProcessing->imageChecklist[0] == false) {
            for(int i = 0; i<imageProcessing->getVectorSize(); i++)
            {
                imageProcessing->imageChecklist[i] = true;
            }
        } else {
            for(int i = 0; i<imageProcessing->getVectorSize(); i++)
            {
                imageProcessing->imageChecklist[i] = false;
            }
        }
        imageProcessing->imageChecklistLoop();
        ui->pushButton_showImage->setChecked(imageProcessing->imageChecklist[imageProcessing->getFileCounter()]);
    }
}
void CoreUI::on_pushButton_reconnect_clicked()
{
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    tcpRemote->Disconnect();
    Disconnected();
    if(SConfig::NETWORKTYPE == "TCP"){ tcpRemote->Connect(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT); }
    else {
        telemetryRemote->Connect(SConfig::NETWORKADDRESS + ":" + SConfig::NETWORKPORT);
        formRemote->Connect(SConfig::NETWORKADDRESS + ":" + SConfig::FORMIMAGEPORT);
        if(SConfig::NETWORKTYPE != "UDP") { SConfig::NETWORKTYPE = "UDP"; Debug::Log("![WARNING] Connection type string unrecognized, using UDP by default"); }
        Debug::Log("?[REMOTE] UDP client connected");
    }
}
void CoreUI::on_pushButton_clearCache_clicked()
{
    QMessageBox askForClearCache;
    askForClearCache.setWindowTitle("Очистка кэша РЛИ");
    askForClearCache.setIcon(QMessageBox::Information);
    askForClearCache.setText("Вы уверены, что хотите полностью очистить кэш радиолокационных изображений? Это действие удалит все изображения, полученные в ходе текущего полёта!");
    askForClearCache.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    askForClearCache.setDefaultButton(QMessageBox::Cancel);
    int ret = askForClearCache.exec();
    switch (ret) {
    case QMessageBox::Yes:
        imageProcessing->clearCache();
        imageProcessing->InitialScan();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
}

void CoreUI::on_pushButton_formSingleImage_clicked()
{
    QString request = MessageParser::makeFormRequest(1, 1);
    SendRemoteCommand(request);
    Debug::Log("[FORM] Sended to SAR: " + request);
    ui->label_c_formImageStatus->setText(Style::StyleText("отправлен запрос на формирование", Colors::MainShade800, Format::NoFormat));
    ui->progressBar_formImageStatus->setValue(10);
}

void CoreUI::on_pushButton_launchContinuous_clicked()
{
    formingContinuous = true;
    on_pushButton_formSingleImage_clicked();
}

void CoreUI::on_pushButton_stopContinuous_clicked()
{
    formingContinuous = false;
}

void CoreUI::on_pushButton_showDebugConsoleDock_clicked()
{
    if(SConfig::DEBUGCONSOLE)
    {
        bool state = ui->debugConsoleDock->isEnabled();
        state = !state;
        ui->debugConsoleDock->setEnabled(state);
        ui->debugConsoleDock->setVisible(state);
    } else {
        //throw password window =)
    }
}


void CoreUI::on_pushButton_showMapToolsDock_clicked()
{
    bool state = ui->mapSettingsDock->isEnabled();
    state = !state;
    ui->mapSettingsDock->setEnabled(state);
    ui->mapSettingsDock->setVisible(state);
}
//************************************************************************************************************************************************************************************************************
