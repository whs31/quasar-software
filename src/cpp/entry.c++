#include "entry.h++"
#include "gui/theme/include/theme.h++"
#include "config/paths.h++"
#include "config/config.h++"
#include "map/ruler.h++"
#include "scenegraph/cpu/statusindicator.h++"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtQml/qqml.h>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    qmlRegisterSingletonInstance<Config::Paths>("Paths", 1, 0, "Paths", Config::Paths::get(this));
    qmlRegisterSingletonInstance<GUI::Theme>("Theme", 1, 0, "Theme", GUI::Theme::get(this));
    qmlRegisterSingletonInstance<Config::Config>("Config", 1, 0, "Config", Config::Config::get(this));

    qmlRegisterType<Map::Ruler>("RulerModel", 1, 0, "RulerModel");
    qmlRegisterType<StatusIndicator>("StatusIndicator", 1, 0, "StatusIndicator");
}
