#include "coreui.h"
#include "ui_coreui.h"

//======================================================================================MENU SLOTS============================================================================================================
//remove this in future
void CoreUI::on_formImage_triggered()                       { qDebug()<<"[CLIENT] Sending command to form SAR image"; SendRemoteCommand("$form-SAR-image");                                                  }
void CoreUI::on_openSettings_triggered() //menu slot
{
    SettingsDialog sd(this);
    QString s = SConfig::PATH;
    if(sd.exec() == QDialog::Accepted)
    {
        if(s!=SConfig::PATH)
        {
            imageProcessing->InitialScan();
        } else { qInfo()<<"[CONFIG] Path unchanged, no further scans"; }
        ui->debugConsoleDock->setEnabled(SConfig::DEBUGCONSOLE); ui->debugConsoleDock->setVisible(SConfig::DEBUGCONSOLE);

        SConfig::saveSettings();
    } else { SConfig::loadSettings(); }

    ui->label_c_sarip->setText("Адрес РЛС: "+Style::StyleText(" ("+SConfig::NETWORKTYPE+") ", Colors::MainShade800, Format::Bold)
                                            +Style::StyleText(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT, Colors::MainShade900, Format::Bold));
    ui->label_c_loaderip->setText("Адрес загрузчика: "+Style::StyleText(SConfig::LOADERIP+":"+SConfig::LOADERPORT, Colors::MainShade900, Format::Bold));
}
//============================================================================================================================================================================================================

//***************************************************************************************GUI SLOTS************************************************************************************************************
void CoreUI::on_checkBox_drawTooltip_stateChanged(int arg1) { linker->changeEnableTooltip(arg1);                                                                                                             }
void CoreUI::on_checkBox_drawTrack_stateChanged(int arg1)   { linker->changeDrawRoute(arg1);                                                                                                                 }
void CoreUI::on_checkBox_stateChanged(int arg1)             { linker->changeFollowPlane(arg1);                                                                                                               }
void CoreUI::on_pushButton_panGPS_clicked()                 { linker->panGPS();                                                                                                                              }
void CoreUI::on_pushButton_goLeft_clicked()                 { imageProcessing->goLeft(); ui->pushButton_showImage->setChecked(imageProcessing->imageChecklist[imageProcessing->getFileCounter()]);           }
void CoreUI::on_pushButton_goRight_clicked()                { imageProcessing->goRight(); ui->pushButton_showImage->setChecked(imageProcessing->imageChecklist[imageProcessing->getFileCounter()]);          }
void CoreUI::on_checkBox_autoUpdate_stateChanged(int arg1)  { autoUpdate = ui->checkBox_autoUpdate->isChecked();                                                                                             }
void CoreUI::on_pushButton_expandImageInfo_clicked()        { bool b = ui->showFullInfoContainer->isVisible(); b = !b; ui->showFullInfoContainer->setVisible(b);                                             }
void CoreUI::on_pushButton_update_clicked()                 { imageProcessing->PartialScan(); ui->pushButton_showImage->setChecked(imageProcessing->imageChecklist[imageProcessing->getFileCounter()]);      }
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
    case QMessageBox::Cancel:
        break;
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
    udpRemote->Disconnect();
    tcpRemote->Disconnect();
    Disconnected();
    if(SConfig::NETWORKTYPE == "TCP"){ tcpRemote->Connect(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT); }
    else {
        udpRemote->Connect(SConfig::NETWORKADDRESS+":"+SConfig::NETWORKPORT);
        if(SConfig::NETWORKTYPE != "UDP") { SConfig::NETWORKTYPE = "UDP"; qWarning()<<"[WARNING] Connection type string unrecognized, using UDP by default"; }
                qInfo()<<"[REMOTE] UDP client connected";
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
//************************************************************************************************************************************************************************************************************
