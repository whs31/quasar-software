#include "sconfig.h"
#include "theme/include/theme.hpp"
#include "func/stext.h"
#include "network/modules/execd/argumentlist.h"

SConfig* SConfig::pointer = nullptr;
Config* SConfig::config;

SConfig::SConfig(QObject* parent) : QObject{parent}
{
    pointer = this;
    config = new Config(CacheManager::getSettingsPath() + "/config2.ini");
    setProjectVersion(PROJECT_VERSION);

    qInfo() << "[SCONFIG] QuaSAR-UI build version: " + getProjectVersion();


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
    // main config
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
    
    qDebug() << "[SCONFIG] Main config loaded.";

    // plugin config
    config->setValue("Terminal/rect_color", Theme::get()->color("dark1"));
    config->setValue("Terminal/font_color", Theme::get()->color("light1"));
    config->setValue("Terminal/cursor_color", Theme::get()->color("color3"));

    qInfo() << "[SCONFIG] Plugin config loaded.";

    m_previousSessionLatitude =  config->value("map/previous_session_latitude").toFloat();
    m_previousSessionLongitude = config->value("map/previous_session_longitude").toFloat();
    m_previousSessionZoom = config->value("map/previous_session_zoom").toFloat();

    qDebug() << "[SCONFIG] Previous latitude: " << getPreviousSessionLatitude() << ", longitude: " << getPreviousSessionLongitude();
    qInfo() << "[SCONFIG] Previous session restored.";
    ArgumentList::get(this)->remote->setValue(getComputerIP() + ":" + getLoaderPort());
}

void SConfig::saveSettings()
{
    save();
    qInfo() << "[SCONFIG] Config saved.";
    RuntimeData::get()->statusPopupSet("Настройки сохранены. Некоторые параметры вступят в силу " +
                                       SText::colorText("только после перезапуска.", Theme::get()->color("yellow")));
    RuntimeData::get()->statusPopupTriggerSet(true);
}

void SConfig::saveQuiet()
{
    save();
    qInfo() << "[SCONFIG] Config saved without dialog.";
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

QString SConfig::getProjectVersion() { return m_projectVersion; }
void SConfig::setProjectVersion(QString string) { if (string == m_projectVersion) return;
m_projectVersion = string; emit projectVersionChanged(); }

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

qreal SConfig::getPreviousSessionLatitude() { return m_previousSessionLatitude; }
void SConfig::setPreviousSessionLatitude(qreal value) { m_previousSessionLatitude = value; 
config->setValue("map/previous_session_latitude", QString::number(value)); qInfo() << "[CONFIG] Set session latitude to " << value;
config->sync();
}
 
qreal SConfig::getPreviousSessionLongitude() { return m_previousSessionLongitude; }
void SConfig::setPreviousSessionLongitude(qreal value) { m_previousSessionLongitude = value; 
config->setValue("map/previous_session_longitude", QString::number(value)); qInfo() << "[CONFIG] Set session longitude to " << value;
config->sync();
}

qreal SConfig::getPreviousSessionZoom() { return m_previousSessionZoom; }
void SConfig::setPreviousSessionZoom(qreal value) { m_previousSessionZoom = value; 
config->setValue("map/previous_session_zoom", QString::number(value)); qInfo() << "[CONFIG] Set session zoom to " << value;
config->sync();
}

QString SConfig::getDefaultCatalogue() { return m_defaultCatalogue; }
void SConfig::setDefaultCatalogue(QString string) { if (string == m_defaultCatalogue) return;
m_defaultCatalogue = string; emit defaultCatalogueChanged(); }
