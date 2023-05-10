#include "entry.h++"
#include "gui/theme/include/theme.h++"
#include "config/paths.h++"
#include "config/config.h++"
#include "filesystem/filesystem.h++"
#include "map/ruler.h++"
#include "map/route.h++"
#include "map/clickhandler.h++"
#include "scenegraph/cpu/statusindicator.h++"
#include "scenegraph/cpu/progressbar.h++"
#include "network/network.h++"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtQml/qqml.h>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    qmlRegisterSingletonInstance<Config::Paths>("Paths", 1, 0, "Paths", Config::Paths::get(this));
    qmlRegisterSingletonInstance<Config::Config>("Config", 1, 0, "Config", Config::Config::get(this));
    qmlRegisterSingletonInstance<GUI::Theme>("Theme", 1, 0, "Theme", GUI::Theme::get(this));
    qmlRegisterSingletonInstance<OS::Filesystem>("Filesystem", 1, 0, "Filesystem", OS::Filesystem::get(this));
    qmlRegisterSingletonInstance<Network::Network>("Network", 1, 0, "Network", Network::Network::get(this));
    qmlRegisterSingletonInstance<Map::ClickHandler>("ClickHandler", 1, 0, "ClickHandler", Map::ClickHandler::get(this));

    qmlRegisterType<Map::Ruler>("RulerModel", 1, 0, "RulerModel");
    qmlRegisterType<Map::Route>("Route", 1, 0, "Route");
    qmlRegisterType<ProgressBar>("Widgets.Status", 1, 0, "ProgressBar");
    qmlRegisterType<StatusIndicator>("Widgets.Status", 1, 0, "StatusIndicator");
}
