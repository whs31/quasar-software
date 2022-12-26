#include "coreui.h"
#include "ui_coreui.h"

//***************************************************************************************GUI SLOTS************************************************************************************************************
void CoreUI::on_pushButton_placeMarker_clicked()
{
    RuntimeData::mouseState = MouseState::MarkerPlacement;
}
void CoreUI::on_pushButton_reconnect_clicked()
{
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    Disconnected();

    telemetryRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("TelemetryPort"));
    formRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("DialogPort"));
    consoleListenerRemote->Connect(SConfig::getHashString("LoaderIP") + ":" + SConfig::getHashString("ListenPort"));
    qCritical() << SConfig::getHashString("LoaderIP") << ":" << SConfig::getHashString("ListenPort");
    if (SConfig::getHashString("NetworkType") != "UDP")
    {
        SConfig::getHashString("NetworkType") = "UDP";
        Debug::Log("![WARNING] Connection type string unrecognized, using UDP by default");
    }
    Debug::Log("?[REMOTE] UDP client connected");
}
void CoreUI::on_pushButton_formSingleImage_clicked()
{
    QString request = MessageParser::makeFormRequest(sar_mode, sar_lowerbound, sar_upperbound, sar_time, sar_dx, sar_dx, sar_override_gps, sar_gps_height, sar_gps_velocity);
    SendRemoteCommand(request, CommandType::FormCommand);
    Debug::Log("[FORM] Sended to SAR: " + request);
    ui->label_c_formImageStatus->setText(Style::StyleText("отправлен запрос на формирование", Colors::Info300, Format::NoFormat));
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
    if (SConfig::getHashBoolean("ShowConsole"))
    {
        bool state = ui->debugConsoleDock->isEnabled();
        state = !state;
        ui->debugConsoleDock->setEnabled(state);
        ui->debugConsoleDock->setVisible(state);
    }
    else
    {
        // throw password window =)
    }
}
void CoreUI::on_pushButton_showSARConsole_clicked()
{
    if (SConfig::getHashBoolean("ShowConsole"))
    {
        bool state = ui->sarConsoleDock->isEnabled();
        state = !state;
        ui->sarConsoleDock->setEnabled(state);
        ui->sarConsoleDock->setVisible(state);
    }
    else
    {
        // throw password window =)
    }
}
//************************************************************************************************************************************************************************************************************
