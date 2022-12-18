#include "sconfig.h"

SConfig* SConfig::pointer;
Config* SConfig::config;
JsonConfig* SConfig::jsonConfig;
FStaticVariables* SConfig::fStatic;

QHash<QString, QVariant> SConfig::variantHash; 

SConfig::SConfig(FStaticVariables* fStaticVariables)
{
    pointer = this;
    config = new Config(CacheManager::getSettingsPath() + "/config2.ini");
    jsonConfig = new JsonConfig(CacheManager::getSettingsPath() + "/config.json");
    fStatic = fStaticVariables;
    Debug::Log("?[SCONFIG] QuaSAR-UI build version: "+config->value("utility/version").toString());   

    SConfig::loadSettings();
}

SConfig* SConfig::initialize(FStaticVariables* fStaticVariables)
{
    if(pointer != NULL)
        return pointer;
    pointer = new SConfig(fStaticVariables);
    return pointer;
}

void SConfig::setHashValue(QString key, QVariant value) { variantHash.insert(key, value); }
QString SConfig::getHashString(QString key) { return variantHash.value(key).toString(); }
float SConfig::getHashFloat(QString key) { return variantHash.value(key).toFloat(); }
bool SConfig::getHashBoolean(QString key) { return variantHash.value(key).toBool(); }
QVariant SConfig::get(QString key) { return variantHash.value(key); }
QHash<QString, QVariant> SConfig::getHashTable(void) { return variantHash; }
void SConfig::setHashTable(QHash<QString, QVariant> table) { variantHash = table; }

void SConfig::loadSettings()
{
    setHashValue("SudoPassword", config->value("general/sudo_password"));
    setHashValue("Mode", config->value("general/program_mode"));

    setHashValue("UseOSM", config->value("utility/use_osm_maps"));
    setHashValue("ShowProfiler", config->value("utility/display_profiler"));
    setHashValue("ShowConsole", config->value("utility/enable_debug_console"));

    setHashValue("NetworkType", config->value("network/core_type"));
    setHashValue("SarIP", config->value("network/sar_ip"));
    setHashValue("TelemetryPort", config->value("network/telemetry_port"));
    setHashValue("TelemetryFrequency", config->value("network/telemetry_update_time"));
    setHashValue("LoaderIP", config->value("network/image_loader_ip"));
    setHashValue("LoaderPort", config->value("network/image_loader_port"));
    setHashValue("DialogPort", config->value("network/dialog_port"));
    setHashValue("ListenPort", config->value("network/console_listen_port"));

    setHashValue("VelocityVectorLength", config->value("map/velocity_vector_length"));
    setHashValue("AntennaPosition", config->value("map/antenna_position"));

    setHashValue("DiagramCaptureTime", config->value("diagram/diagram_capture_time"));
    setHashValue("DiagramCaptureRange", config->value("diagram/diagram_capture_range"));
    setHashValue("DiagramThetaAzimuth", config->value("diagram/diagram_theta_azimuth"));
    setHashValue("DiagramDriftAngle", config->value("diagram/diagram_drift_angle"));

    setHashValue("AnglePredefinedCorrection", config->value("image/angle_predefined_correction"));
    setHashValue("GlobalRadians", config->value("image/angle_use_radians_globally"));
    setHashValue("SaveNonContinuous", config->value("image/save_image_only_when_loading_finished"));
    setHashValue("ViewPath", config->value("image/view_mode_default_directory"));
    setHashValue("FlightPath", CacheManager::getTcpDowloaderCache());

    setHashValue("StartupConnectToSAR", config->value("startup/connect_to_sar"));

    fStatic->setTestMode(getHashBoolean("UseOSM"));
    fStatic->setPredictRange(getHashFloat("VelocityVectorLength"));
    fStatic->setUseBase64(getHashBoolean("Base64Enabled"));

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
    config->setValue("general/sudo_password", getHashString("SudoPassword"));
    config->setValue("general/program_mode", getHashBoolean("Mode"));

    config->setValue("utility/use_osm_maps", getHashBoolean("UseOSM"));
    config->setValue("utility/display_profiler", getHashBoolean("ShowProfiler"));
    config->setValue("utility/enable_debug_console", getHashBoolean("ShowConsole"));

    config->setValue("network/core_type", getHashString("NetworkType"));
    config->setValue("network/sar_ip", getHashString("SarIP"));
    config->setValue("network/telemetry_port", getHashString("TelemetryPort"));
    config->setValue("network/telemetry_update_time", getHashFloat("TelemetryFrequency"));
    config->setValue("network/image_loader_ip", getHashString("LoaderIP"));
    config->setValue("network/image_loader_port", getHashString("LoaderPort"));
    config->setValue("network/dialog_port", getHashString("DialogPort"));
    config->setValue("network/console_listen_port", getHashString("ListenPort"));

    config->setValue("map/velocity_vector_length", getHashFloat("VelocityVectorLength"));
    config->setValue("map/antenna_position", getHashString("AntennaPosition"));

    config->setValue("diagram/diagram_capture_time", QString::number(getHashFloat("DiagramCaptureTime")));
    config->setValue("diagram/diagram_capture_range", QString::number(getHashFloat("DiagramCaptureRange")));
    config->setValue("diagram/diagram_theta_azimuth", QString::number(getHashFloat("DiagramThetaAzimuth")));
    config->setValue("diagram/diagram_drift_angle", QString::number(getHashFloat("DiagramDriftAngle")));

    config->setValue("image/angle_predefined_correction", QString::number(getHashFloat("AnglePredefinedCorrection")));
    config->setValue("image/angle_use_radians_globally", getHashBoolean("GlobalRadians"));
    config->setValue("image/use_base64_encoding_optimization", getHashBoolean("Base64Enabled"));
    config->setValue("image/save_image_only_when_loading_finished", getHashBoolean("SaveNonContinuous"));
    config->setValue("image/view_mode_default_directory", getHashString("ViewPath"));

    config->setValue("startup/display_images_when_loaded", getHashBoolean("StartupShowAll"));
    config->setValue("startup/connect_to_sar", getHashBoolean("StartupConnectToSAR"));
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