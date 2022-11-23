#include "sconfig.h"

SConfig* SConfig::pointer;
LinkerQML* SConfig::linker;
Config* SConfig::config;

QString SConfig::C_NETWORKTYPE;
QString SConfig::C_NETWORKADDRESS;
QString SConfig::C_NETWORKPORT;
float SConfig::C_UPDATETIME;
float SConfig::C_PREDICTRANGE;
float SConfig::C_CAPTURERANGE;
float SConfig::C_CAPTURETIME;
float SConfig::C_AZIMUTH;
float SConfig::C_DRIFTANGLE;
QString SConfig::C_ANTENNAPOSITION;
QString SConfig::C_PATH;
bool SConfig::C_SHOWIMAGEONSTART;
bool SConfig::C_CONNECTONSTART;
bool SConfig::C_DEBUGCONSOLE;

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
    //здесь был mainwindow->getConfig()

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
    config->setValue("network/type", C_NETWORKTYPE);
    config->setValue("network/ip", C_NETWORKADDRESS);
    config->setValue("network/port", C_NETWORKPORT);
    config->setValue("network/updateTime", C_UPDATETIME);
    config->setValue("map/predict_line_range", C_PREDICTRANGE);
    config->setValue("map/diagram_length", C_CAPTURERANGE);
    config->setValue("map/capture_time", C_CAPTURETIME);
    config->setValue("map/diagram_theta_azimuth", C_AZIMUTH);
    config->setValue("map/diagram_drift_angle", C_DRIFTANGLE);
    config->setValue("map/antenna_position", C_ANTENNAPOSITION);
    config->setValue("image/path", C_PATH);
    config->setValue("startup/show_image", C_SHOWIMAGEONSTART);
    config->setValue("startup/connect", C_CONNECTONSTART);
    config->setValue("startup/debug_console", C_DEBUGCONSOLE);

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

