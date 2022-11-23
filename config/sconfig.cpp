#include "sconfig.h"

SConfig* SConfig::pointer;
LinkerQML* SConfig::linker;
Config* SConfig::config;

QString SConfig::NETWORKTYPE;
QString SConfig::NETWORKADDRESS;
QString SConfig::NETWORKPORT;
float SConfig::UPDATETIME;
float SConfig::PREDICTRANGE;
float SConfig::CAPTURERANGE;
float SConfig::CAPTURETIME;
float SConfig::AZIMUTH;
float SConfig::DRIFTANGLE;
QString SConfig::ANTENNAPOSITION;
QString SConfig::PATH;
bool SConfig::SHOWIMAGEONSTART;
bool SConfig::CONNECTONSTART;
bool SConfig::DEBUGCONSOLE;

SConfig::SConfig(QQuickItem* qml)
{
    pointer = this;
    config = new Config(QCoreApplication::applicationDirPath()+"/settings.ini");
    linker = new LinkerQML(qml);
    qWarning()<<"[SCONFIG] Config loaded. Version "<<config->value("utility/version").toString();
}

SConfig* SConfig::init(void)            { return pointer; }

void SConfig::loadSettings()
{
    NETWORKTYPE           =           config->value("network/type").toString();
    NETWORKADDRESS        =           config->value("network/ip").toString();
    NETWORKPORT           =           config->value("network/port").toString();
    UPDATETIME            =           config->value("network/updateTime").toFloat();
    PREDICTRANGE          =           config->value("map/predict_line_range").toFloat();
    CAPTURERANGE          =           config->value("map/diagram_length").toFloat();
    CAPTURETIME           =           config->value("map/capture_time").toFloat();
    AZIMUTH               =           config->value("map/diagram_theta_azimuth").toFloat();
    DRIFTANGLE            =           config->value("map/diagram_drift_angle").toFloat();
    ANTENNAPOSITION       =           config->value("map/antenna_position").toString();
    PATH                  =           config->value("image/path").toString();
    SHOWIMAGEONSTART      =           config->value("startup/show_image").toBool();
    CONNECTONSTART        =           config->value("startup/connect").toBool();
    DEBUGCONSOLE          =           config->value("startup/debug_console").toBool();

    SConfig::linker->loadSettings(SConfig::config->value("map/predict_line_range").toDouble(),
                         config->value("map/diagram_length").toDouble(),
                         config->value("map/capture_time").toDouble(),
                         config->value("map/diagram_theta_azimuth").toDouble(),
                         config->value("map/diagram_drift_angle").toDouble(),
                         config->value("map/antenna_position").toString(),
                         config->value("map/path").toString());
    qWarning()<<"[SCONFIG] Config loaded. Version "<<config->value("utility/version").toString();

}

void SConfig::saveSettings()
{
    config->setValue("network/type", NETWORKTYPE);
    config->setValue("network/ip", NETWORKADDRESS);
    config->setValue("network/port", NETWORKPORT);
    config->setValue("network/updateTime", UPDATETIME);
    config->setValue("map/predict_line_range", PREDICTRANGE);
    config->setValue("map/diagram_length", CAPTURERANGE);
    config->setValue("map/capture_time", CAPTURETIME);
    config->setValue("map/diagram_theta_azimuth", AZIMUTH);
    config->setValue("map/diagram_drift_angle", DRIFTANGLE);
    config->setValue("map/antenna_position", ANTENNAPOSITION);
    config->setValue("image/path", PATH);
    config->setValue("startup/show_image", SHOWIMAGEONSTART);
    config->setValue("startup/connect", CONNECTONSTART);
    config->setValue("startup/debug_console", DEBUGCONSOLE);

    qInfo()<<"[CONFIG] Config saved.";
    QMessageBox notifyAboutRestart;
    notifyAboutRestart.setWindowTitle("Сохранение настроек");
    notifyAboutRestart.setIcon(QMessageBox::Information);
    notifyAboutRestart.setText("Настройки сохранены.");
    notifyAboutRestart.setStandardButtons(QMessageBox::Yes);
    notifyAboutRestart.setDefaultButton(QMessageBox::Yes);
    notifyAboutRestart.exec();
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

