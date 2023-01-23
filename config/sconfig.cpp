#include "sconfig.h"

SConfig* SConfig::pointer = nullptr;
Config* SConfig::config;
JsonConfig* SConfig::jsonConfig;

SConfig::SConfig(QObject* parent) : QObject{parent}
{
    pointer = this;
    config = new Config(CacheManager::getSettingsPath() + "/config2.ini");
    jsonConfig = new JsonConfig(CacheManager::getSettingsPath() + "/config.json");
    Debug::Log("?[SCONFIG] QuaSAR-UI build version: "+config->value("utility/version").toString());   

    SConfig::loadSettings();
}

SConfig* SConfig::get(QObject* parent)
{
    if(pointer != NULL)
        return pointer;
    pointer = new SConfig(parent);
    return pointer;
}

void SConfig::loadSettings()
{
    setSudoPassword(config->value("general/sudo_password").toString());
    setDebugConsole(config->value("general/enable_debug_console").toBool());
    
    setNetworkType(config->value("network/protocol").toString());
    setDE10IP(config->value("network/de10_ip").toString());
    setTelemetryPort(config->value("network/telemetry_port").toString());
    setTelemetryFrequency(config->value("network/telemetry_update_time").toFloat());
    setComputerIP(config->value("network/computer_ip").toString());
    setLoaderPort(config->value("network/image_loader_port").toString());
    setExecdPort(config->value("network/execd_port").toString());
    setTerminalPort(config->value("network/terminal_port").toString());
    setUseOldExecdEndline(config->value("network/use_old_execd_endline").toBool());

    setOnlineMaps(config->value("map/use_online_maps").toBool());
    setVelocityVectorLength(config->value("map/velocity_vector_length").toFloat());
    setAntennaPosition(config->value("map/antenna_position").toString());
    setDiagramThetaAzimuth(config->value("map/diagram_theta_azimuth").toFloat());

    setAngleCorrection(config->value("image/angle_predefined_correction").toFloat());
    setGlobalRadians(config->value("image/angle_use_radians_globally").toBool());
    setUseDriftAngle(config->value("image/angle_use_drift_angle").toBool());
    setThetaAzimuthCorrection(config->value("image/angle_theta_azimuth_correction").toFloat());
    setDefaultCatalogue(config->value("image/view_mode_default_directory").toString());

    Debug::Log("?[SCONFIG] Config loaded.");
}

void SConfig::saveSettings()
{
    save();
    Debug::Log("?[CONFIG] Config saved.");
    QMessageBox notifyAboutRestart;
    notifyAboutRestart.setWindowTitle("Сохранение настроек");
    notifyAboutRestart.setIcon(QMessageBox::Information);
    notifyAboutRestart.setText("Настройки сохранены. Некоторые параметры вступят в силу только после перезапуска программы.");
    notifyAboutRestart.setStandardButtons(QMessageBox::Yes);
    notifyAboutRestart.setDefaultButton(QMessageBox::Yes);
    notifyAboutRestart.exec();
}

void SConfig::saveQuiet()
{
    save();
    Debug::Log("?[CONFIG] Config saved without dialog.");
}

void SConfig::save()
{
    config->setValue("general/sudo_password", getSudoPassword());
    config->setValue("general/enable_debug_console", getDebugConsole());
    
    config->setValue("network/protocol", getNetworkType());
    config->setValue("network/de10_ip", getDE10IP());
    config->setValue("network/telemetry_port", getTelemetryPort());
    config->setValue("network/telemetry_update_time", QString::number(getTelemetryFrequency()));
    config->setValue("network/computer_ip", getComputerIP());
    config->setValue("network/image_loader_port", getLoaderPort());
    config->setValue("network/execd_port", getExecdPort());
    config->setValue("network/terminal_port", getTerminalPort());
    config->setValue("network/use_old_execd_endline", getUseOldExecdEndline());

    config->setValue("map/use_online_maps", getOnlineMaps());
    config->setValue("map/velocity_vector_length", QString::number(getVelocityVectorLength()));
    config->setValue("map/antenna_position", getAntennaPosition());
    config->setValue("map/diagram_theta_azimuth", QString::number(getDiagramThetaAzimuth()));

    config->setValue("image/angle_predefined_correction", QString::number(getAngleCorrection()));
    config->setValue("image/angle_use_radians_globally", getGlobalRadians());
    config->setValue("image/angle_use_drift_angle", getUseDriftAngle());
    config->setValue("image/angle_theta_azimuth_correction", QString::number(getThetaAzimuthCorrection()));
    config->setValue("image/view_mode_default_directory", getDefaultCatalogue());

}

void SConfig::discardSettings()
{
    QMessageBox askForDiscardSettings;
    askForDiscardSettings.setWindowTitle("Отмена изменений");
    askForDiscardSettings.setIcon(QMessageBox::Question);
    askForDiscardSettings.setText("Вы уверены, что хотите отменить изменения настроек?");
    askForDiscardSettings.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    askForDiscardSettings.setDefaultButton(QMessageBox::Cancel);
    int ret = askForDiscardSettings.exec();
    switch (ret) {
      case QMessageBox::Yes: loadSettings();
          break;
      case QMessageBox::Cancel:
          break;
      default:
          break;
    }
}

QString SConfig::getSudoPassword() { return m_sudoPassword; }
void SConfig::setSudoPassword(QString string) { if (string == m_sudoPassword) return;
m_sudoPassword = string; emit sudoPasswordChanged(); }

bool SConfig::getDebugConsole() { return m_debugConsole; }
void SConfig::setDebugConsole(bool state) { if (state == m_debugConsole) return;
m_debugConsole = state; emit debugConsoleChanged(); }

QString SConfig::getNetworkType() { return m_networkType; }
void SConfig::setNetworkType(QString string) { if (string == m_networkType) return;
m_networkType = string; emit networkTypeChanged(); }

QString SConfig::getDE10IP() { return m_de10IP; }
void SConfig::setDE10IP(QString string) { if (string == m_de10IP) return;
m_de10IP = string; emit de10IPChanged(); }

QString SConfig::getTelemetryPort() { return m_telemetryPort; }
void SConfig::setTelemetryPort(QString string) { if (string == m_telemetryPort) return;
m_telemetryPort = string; emit telemetryPortChanged(); }

float SConfig::getTelemetryFrequency() { return m_telemetryFrequency; }
void SConfig::setTelemetryFrequency(float value) { if (value == m_telemetryFrequency) return;
m_telemetryFrequency = value; emit telemetryFrequencyChanged(); }

QString SConfig::getComputerIP() { return m_computerIP; }
void SConfig::setComputerIP(QString string) { if (string == m_computerIP) return;
m_computerIP = string; emit computerIPChanged(); }

QString SConfig::getLoaderPort() { return m_loaderPort; }
void SConfig::setLoaderPort(QString string) { if (string == m_loaderPort) return;
m_loaderPort = string; emit loaderPortChanged(); }

QString SConfig::getExecdPort() { return m_execdPort; }
void SConfig::setExecdPort(QString string) { if (string == m_execdPort) return;
m_execdPort = string; emit execdPortChanged(); }

QString SConfig::getTerminalPort() { return m_terminalPort; }
void SConfig::setTerminalPort(QString string) { if (string == m_terminalPort) return;
m_terminalPort = string; emit terminalPortChanged(); }

bool SConfig::getUseOldExecdEndline() { return m_useOldExecdEndline; }
void SConfig::setUseOldExecdEndline(bool state) { if (state == m_useOldExecdEndline) return;
m_useOldExecdEndline = state; emit useOldExecdEndlineChanged(); }

bool SConfig::getOnlineMaps() { return m_onlineMaps; }
void SConfig::setOnlineMaps(bool state) { if (state == m_onlineMaps) return;
m_onlineMaps = state; emit onlineMapsChanged(); }

float SConfig::getVelocityVectorLength() { return m_velocityVectorLength; }
void SConfig::setVelocityVectorLength(float value) { if (value == m_velocityVectorLength) return;
m_velocityVectorLength = value; emit velocityVectorLengthChanged(); }

QString SConfig::getAntennaPosition() { return m_antennaPosition; }
void SConfig::setAntennaPosition(QString string) { if (string == m_antennaPosition) return;
m_antennaPosition = string; emit antennaPositionChanged(); }

float SConfig::getDiagramThetaAzimuth() { return m_diagramThetaAzimuth; }
void SConfig::setDiagramThetaAzimuth(float value) { if (value == m_diagramThetaAzimuth) return;
m_diagramThetaAzimuth = value; emit diagramThetaAzimuthChanged(); }

float SConfig::getAngleCorrection() { return m_angleCorrection; }
void SConfig::setAngleCorrection(float value) { if (value == m_angleCorrection) return;
m_angleCorrection = value; emit angleCorrectionChanged(); }

bool SConfig::getGlobalRadians() { return m_globalRadians; }
void SConfig::setGlobalRadians(bool state) { if (state == m_globalRadians) return;
m_globalRadians = state; emit globalRadiansChanged(); }

bool SConfig::getUseDriftAngle() { return m_driftAngle; }
void SConfig::setUseDriftAngle(bool state) { if (state == m_driftAngle) return;
m_driftAngle = state; emit useDriftAngleChanged(); }

float SConfig::getThetaAzimuthCorrection() { return m_thetaAzimuthCorrection; }
void SConfig::setThetaAzimuthCorrection(float value) { if (value == m_thetaAzimuthCorrection) return;
m_thetaAzimuthCorrection = value; emit thetaAzimuthCorrectionChanged(); }

QString SConfig::getDefaultCatalogue() { return m_defaultCatalogue; }
void SConfig::setDefaultCatalogue(QString string) { if (string == m_defaultCatalogue) return;
m_defaultCatalogue = string; emit defaultCatalogueChanged(); }
