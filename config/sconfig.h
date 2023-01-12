#ifndef SCONFIG_H
#define SCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QQuickItem>
#include <QMessageBox>
#include <QHash>
#include <QVariant>

#include "cachemanager.h"
#include "config.h"
#include "jsonconfig.h"

#include "debug.h"
#include "saroutputconsoleemulator.h"

class SConfig : public QObject
{
    Q_OBJECT
public:
    static SConfig* initialize(QObject* parent = nullptr);

    static void loadSettings();
    static void saveSettings();
    static void saveQuiet();
    static void discardSettings();

    static void setHashValue(QString key, QVariant value);
    static QString getHashString(QString key);
    static float getHashFloat(QString key);
    static bool getHashBoolean(QString key);
    static QVariant get(QString key);

    static QHash<QString, QVariant>* getHashTable(void);
    static void setHashTable(QHash<QString, QVariant>* table);

signals:

private:
    explicit SConfig(QObject* parent = nullptr);
    static SConfig* pointer;
    static Config* config;
    static JsonConfig* jsonConfig;

    static QHash<QString, QVariant> variantHash;
    static void save();
};

#endif // SCONFIG_H
