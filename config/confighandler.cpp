#include "confighandler.h"

ConfigHandler::ConfigHandler(LinkerQML* linker, MainWindow* parent) : mainWindow(parent), linker(linker)
{
    config = new Config(QCoreApplication::applicationDirPath()+"/quasar.ini");
}

void ConfigHandler::loadSettings()
{
    mainWindow->getConfig(config->value("network/type").toString(),
                          config->value("network/ip").toString(),
                          config->value("network/port").toString(),
                          config->value("network/updateTime").toFloat(),
                          config->value("map/predict_line_range").toFloat(),
                          config->value("map/diagram_length").toFloat(),
                          config->value("map/capture_time").toFloat(),
                          config->value("map/diagram_theta_azimuth").toFloat(),
                          config->value("map/diagram_drift_angle").toFloat(),
                          config->value("map/antenna_position").toString(),
                          config->value("image/path").toString(),
                          config->value("startup/show_image").toBool(),
                          config->value("startup/connect").toBool(),
                          config->value("startup/debug_console").toBool());

    linker->loadSettings(config->value("map/predict_line_range").toDouble(),
                         config->value("map/diagram_length").toDouble(),
                         config->value("map/capture_time").toDouble(),
                         config->value("map/diagram_theta_azimuth").toDouble(),
                         config->value("map/diagram_drift_angle").toDouble(),
                         config->value("map/antenna_position").toString(),
                         config->value("map/path").toString());
    qInfo()<<"[CONFIG] Config loaded. Version "<<config->value("utility/version").toString();

}

void ConfigHandler::saveSettings()
{
    config->setValue("network/type", mainWindow->C_NETWORKTYPE);
    config->setValue("network/ip", mainWindow->C_NETWORKADDRESS);
    config->setValue("network/port", mainWindow->C_NETWORKPORT);
    config->setValue("network/updateTime", mainWindow->C_UPDATETIME);
    config->setValue("map/predict_line_range", mainWindow->C_PREDICTRANGE);
    config->setValue("map/diagram_length", mainWindow->C_CAPTURERANGE);
    config->setValue("map/capture_time", mainWindow->C_CAPTURETIME);
    config->setValue("map/diagram_theta_azimuth", mainWindow->C_AZIMUTH);
    config->setValue("map/diagram_drift_angle", mainWindow->C_DRIFTANGLE);
    config->setValue("map/antenna_position", mainWindow->C_ANTENNAPOSITION);
    config->setValue("image/path", mainWindow->C_PATH);
    config->setValue("startup/show_image", mainWindow->C_SHOWIMAGEONSTART);
    config->setValue("startup/connect", mainWindow->C_CONNECTONSTART);
    config->setValue("startup/debug_console", mainWindow->C_DEBUGCONSOLE);

    qInfo()<<"[CONFIG] Config saved.";
    QMessageBox notifyAboutRestart;
    notifyAboutRestart.setWindowTitle("Сохранение настроек");
    notifyAboutRestart.setIcon(QMessageBox::Information);
    notifyAboutRestart.setText("Настройки сохранены.");
    notifyAboutRestart.setStandardButtons(QMessageBox::Yes);
    notifyAboutRestart.setDefaultButton(QMessageBox::Yes);
    notifyAboutRestart.exec();
}

void ConfigHandler::discardSettings()
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
