#include "confighandler.h"

ConfigHandler::ConfigHandler()
{
    mainWindow = MainWindow::getMainWinPtr();
    config = new Config(QCoreApplication::applicationDirPath()+"/config.ini");
}

void ConfigHandler::loadSettings()
{
    QString t = config->value("telemetry/address").toString();
    double d;
    bool b;

//    b = config->value("image/show_all_images_on_init").toBool();

//    t = config->value("telemetry/port").toString();
//    mainWindow->ui->TCPPortxml->setText(t);
//    d = config->value("telemetry/updateTime").toDouble();
//    mainWindow->ui->refreshtelemetryxml->setValue(d);

    //to qml
    qInfo()<<"[CONFIG] Config loaded. Version "<<config->value("utility/version").toString();

}

void ConfigHandler::saveSettings()
{
    //config->setValue("telemetry/address", mainWindow->ui->UDPIPxml->text());
    //config->setValue("map/predict_line_range", mainWindow->ui->predictRangexml->value());
    auto qml = mainWindow->ui->map->rootObject();
    /*QMetaObject::invokeMethod(qml, "loadSettings",
            //Q_ARG(QVariant, config->value("map/map_provider").toString()),
            Q_ARG(QVariant, config->value("map/diagram_theta_azimuth").toDouble()),
            Q_ARG(QVariant, config->value("map/diagram_length").toDouble()),
            Q_ARG(QVariant, config->value("map/diagram_drift_angle").toDouble()),
            Q_ARG(QVariant, config->value("map/capture_time").toDouble()),
            Q_ARG(QVariant, config->value("map/predict_line_range").toDouble()));*/
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
