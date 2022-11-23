#ifndef SCONFIG_H
#define SCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QMessageBox>

#include "config.h"
#include "linkerqml.h"

class SConfig : public QObject
{
    Q_OBJECT
public:
    explicit SConfig(QQuickItem* qml);
    static SConfig* init(void);
    static void loadSettings();
    static void saveSettings();
    static void discardSettings();

    static QString C_NETWORKTYPE;
    static QString C_NETWORKADDRESS;
    static QString C_NETWORKPORT;
    static float C_UPDATETIME;
    static float C_PREDICTRANGE;
    static float C_CAPTURERANGE;
    static float C_CAPTURETIME;
    static float C_AZIMUTH;
    static float C_DRIFTANGLE;
    static QString C_ANTENNAPOSITION;
    static QString C_PATH;
    static bool C_SHOWIMAGEONSTART;
    static bool C_CONNECTONSTART;
    static bool C_DEBUGCONSOLE;

signals:

private:
    static SConfig* pointer;
    static Config* config;
    static LinkerQML* linker;
};

#endif // SCONFIG_H
