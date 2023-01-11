#ifndef PLUGIN_LIB_H
#define PLUGIN_LIB_H


#if defined MAKE_PLUGIN_LIB
    #define PLUGIN_LIB_EXPORT Q_DECL_EXPORT
#else
    #define PLUGIN_LIB_EXPORT Q_DECL_IMPORT
#endif

#include <QDebug>
#include <QWidget>
#include <QString>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QVariant>
#include <QDockWidget>

#include <pluginDataTypes.h>
#include <pluginHostAPI.h>
#include <pluginInterface.h>
#include <pluginHead.h>


#endif // PLUGIN_LIB_H
