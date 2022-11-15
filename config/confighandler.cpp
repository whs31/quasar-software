#include "confighandler.h"

ConfigHandler::ConfigHandler()
{
    mainWindow = MainWindow::getMainWinPtr();
    config = new Config(QCoreApplication::applicationDirPath()+"/quasar.ini");
}

void ConfigHandler::loadSettings()
{
      mainWindow->C_NETWORKTYPE = config->value("network/type").toString();
      mainWindow->C_NETWORKADDRESS = config->value("network/ip").toString();
      mainWindow->C_NETWORKPORT = config->value("network/port").toString();
      mainWindow->C_UPDATETIME = config->value("network/updateTime").toFloat();
      mainWindow->C_PREDICTRANGE = config->value("map/predict_line_range").toFloat();
      mainWindow->C_CAPTURERANGE = config->value("map/diagram_length").toFloat();
      mainWindow->C_CAPTURETIME = config->value("map/capture_time").toFloat();
      mainWindow->C_AZIMUTH = config->value("map/diagram_theta_azimuth").toFloat();
      mainWindow->C_DRIFTANGLE = config->value("map/diagram_drift_angle").toFloat();
      mainWindow->C_ANTENNAPOSITION = config->value("map/antenna_position").toString();
      mainWindow->C_PATH = config->value("image/path").toString();
    qInfo()<<"[CONFIG] Config loaded. Version "<<config->value("utility/version").toString();
    auto qml = mainWindow->ui->map->rootObject();
    QMetaObject::invokeMethod(qml, "loadSettings",
            Q_ARG(QVariant, config->value("map/predict_line_range").toDouble()),
            Q_ARG(QVariant, config->value("map/diagram_length").toDouble()),
            Q_ARG(QVariant, config->value("map/capture_time").toDouble()),
            Q_ARG(QVariant, config->value("map/diagram_theta_azimuth").toDouble()),
            Q_ARG(QVariant, config->value("map/diagram_drift_angle").toDouble()),
            Q_ARG(QVariant, config->value("map/antenna_position").toString()),
            Q_ARG(QVariant, config->value("map/path").toString()));

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
