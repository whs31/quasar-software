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

    static QString NETWORKTYPE;
    static QString NETWORKADDRESS;
    static QString NETWORKPORT;
    static float UPDATETIME;
    static float PREDICTRANGE;
    static float CAPTURERANGE;
    static float CAPTURETIME;
    static float AZIMUTH;
    static float DRIFTANGLE;
    static QString ANTENNAPOSITION;
    static QString PATH;
    static bool SHOWIMAGEONSTART;
    static bool CONNECTONSTART;
    static bool DEBUGCONSOLE;
    static QString CACHEPATH;
    static bool USELOADER;
    static bool SAVEATEND;
    static QString LOADERIP;
    static QString LOADERPORT;

signals:

private:
    static SConfig* pointer;
    static Config* config;
    static LinkerQML* linker;
};

#endif // SCONFIG_H
