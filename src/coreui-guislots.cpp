#include "coreui.h"
#include "ui_coreui.h"
#include "buildprefs.h"

//***************************************************************************************GUI SLOTS************************************************************************************************************
void CoreUI::on_pushButton_placeMarker_clicked()
{
    RuntimeData::mouseState = MouseState::MarkerPlacement;
}
void CoreUI::reconnectSlot()
{
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    consoleListenerRemote->Disconnect();
    Disconnected();

    telemetryRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("TelemetryPort"));
    if(SConfig::getHashString("SarIP").endsWith("48") && USE_JETSON_IP_IN_CONFIG_FOR_TELEMETRY == true)
        {
            QString correctedSarIP = SConfig::getHashString("SarIP");
            correctedSarIP.chop(1); correctedSarIP.append("7");
            formRemote->Connect(correctedSarIP + ":" + SConfig::getHashString("DialogPort"));
            Debug::Log("![REMOTE] Sending commands to autocorrected address: " + correctedSarIP + ":" + SConfig::getHashString("DialogPort"));
        } else { 
            formRemote->Connect(SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("DialogPort")); 
            Debug::Log("?[REMOTE] Sending commands to address: " + SConfig::getHashString("SarIP") + ":" + SConfig::getHashString("DialogPort"));
        }
    consoleListenerRemote->Connect(SConfig::getHashString("LoaderIP") + ":" + SConfig::getHashString("ListenPort"));
    Debug::Log("?[REMOTE] Listening to SAR on " + SConfig::getHashString("LoaderIP") + ":" + SConfig::getHashString("ListenPort"));
    if (SConfig::getHashString("NetworkType") != "UDP")
    {
        SConfig::getHashString("NetworkType") = "UDP";
        Debug::Log("![WARNING] Connection type string unrecognized, using UDP by default");
    }
    Debug::Log("?[REMOTE] UDP client connected");
}
void CoreUI::disconnectSlot()
{
    telemetryRemote->Disconnect();
    formRemote->Disconnect();
    consoleListenerRemote->Disconnect();
    Disconnected();
    Debug::Log("?[REMOTE] All remotes disconnected.");
}
void CoreUI::on_pushButton_formSingleImage_clicked()
{
    QString request = MessageParser::makeFormRequest(RuntimeData::initialize()->getFormMode(), RuntimeData::initialize()->getFormLowerBound(),
                                                     RuntimeData::initialize()->getFormUpperBound(), RuntimeData::initialize()->getFormTime(),
                                                     RuntimeData::initialize()->getFormStep(), RuntimeData::initialize()->getFormStep(),
                                                     RuntimeData::initialize()->getFormOverrideGPSData(), RuntimeData::initialize()->getFormGPSHeight(),
                                                     RuntimeData::initialize()->getFormGPSVelocity());
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
    if (!plugins.terminalLoaded)
    {
        bool state = ui->sarConsoleDock->isEnabled();
        state = !state;
        ui->sarConsoleDock->setEnabled(state);
        ui->sarConsoleDock->setVisible(state);
    }
    else
    {
        bool state = plugins.terminal->isEnabled();
        state = !state;
        plugins.terminal->setEnabled(state);
        plugins.terminal->setVisible(state);
    }
}
//************************************************************************************************************************************************************************************************************
