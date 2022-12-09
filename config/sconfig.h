#ifndef SCONFIG_H
#define SCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QMessageBox>

#include "cachemanager.h"
#include "config.h"
#include "jsonconfig.h"

#include "linkerqml.h"
#include "backend/fstaticvariables.h"
#include "debug.h"

class SConfig : public QObject
{
    Q_OBJECT
public:
    explicit SConfig(QQuickItem* qml, FStaticVariables* fStaticVariables);
    static SConfig* init(void);
    static void loadSettings();
    static void saveSettings();
    static void saveQuiet();
    static void discardSettings();

    static QString BUILDVERSION;
    static QString PASSWORD;
    static bool TESTMODE;
    static bool USEPROFILER;
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
    static bool USEBASE64;
    static bool METAANGLEINRADIANS;
    static float METAANGLECORRECTION;

signals:

private:
    static SConfig* pointer;
    static Config* config;
    static JsonConfig* jsonConfig;
    static LinkerQML* linker;
    static FStaticVariables* fStatic;

    static void save();
};

#endif // SCONFIG_H
