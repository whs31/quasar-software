#ifndef SCONFIG_H
#define SCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QMessageBox>
#include <QHash>

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
    static SConfig* initialize(QQuickItem* qml, FStaticVariables* fStaticVariables);

    static void loadSettings();
    static void saveSettings();
    static void saveQuiet();
    static void discardSettings();

    static void setHashValue(QString key, QVariant value);
    static QString getHashString(QString key);
    static float getHashFloat(QString key);
    static bool getHashBoolean(QString key);

signals:

private:
    explicit SConfig(QQuickItem* qml, FStaticVariables* fStaticVariables);
    static SConfig* pointer;
    static Config* config;
    static JsonConfig* jsonConfig;
    static LinkerQML* linker;
    static FStaticVariables* fStatic;

    static QHash<QString, QVariant> variantHash;
    static void save();
};

#endif // SCONFIG_H
