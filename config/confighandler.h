#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QObject>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "linkerqml.h"

class MainWindow;
class ConfigHandler
{
public:
    ConfigHandler(LinkerQML* linker, MainWindow *parent);
    void loadSettings();
    void saveSettings();
    void discardSettings();

    Config *config;
private:
    MainWindow *mainWindow;
    LinkerQML *linker;

};

#endif // CONFIGHANDLER_H
