#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QObject>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

class MainWindow;
class ConfigHandler
{
public:
    ConfigHandler();
    void loadSettings();
    void saveSettings();
    void discardSettings();

    Config *config;
private:
    MainWindow *mainWindow;

};

#endif // CONFIGHANDLER_H
