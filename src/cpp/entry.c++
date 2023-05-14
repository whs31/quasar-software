#include "entry.h"
#include "gui/theme/include/theme.h"
#include "config/paths.h"
#include "config/config.h"
#include "filesystem/filesystem.h"
#include "processing/imageprocessing.h"
#include "map/ruler.h"
#include "map/route.h"
#include "map/clickhandler.h"
#include "map/imagemodel.h"
#include "scenegraph/cpu/statusindicator.h"
#include "scenegraph/cpu/progressbar.h"
#include "network/network.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtQml/qqml.h>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    /*! === === === === @todo list === === === ===

        Cursor coords
        Markers
        Planner points
        Image dialog window
        Protractor
        Follow UAV
        Scale grid
        Diagram
        Dialog confirmation
        Expose Project version to QML
        Clear cache
        Form image button
        Focus window
        Graphs
        Network graph
        Concurrent run
        Attitude indicator

        === === === === === === === === === === ===
    */

    QML_EXPOSE_INSTANCE(Config::Paths, "Config", "Paths", Config::Paths::get());
    QML_EXPOSE_INSTANCE(Config::Config, "Config", "Config", Config::Config::get());
    QML_EXPOSE_INSTANCE(GUI::Theme, "Theme", "Theme", GUI::Theme::get());
    QML_EXPOSE_INSTANCE(OS::Filesystem, "Filesystem", "Filesystem", OS::Filesystem::get());
    QML_EXPOSE_INSTANCE(Network::Network, "Network", "Network", Network::Network::get());
    QML_EXPOSE_INSTANCE(Map::ImageModel, "Images", "ImagesModel", Processing::ImageProcessing::get()->model());
    QML_EXPOSE_INSTANCE(Map::ClickHandler, "ClickHandler", "ClickHandler", Map::ClickHandler::get());

    QML_EXPOSE_INSTANTIABLE(Map::Ruler, "Ruler", "RulerModel");
    QML_EXPOSE_INSTANTIABLE(Map::Route, "Route", "Route");
    QML_EXPOSE_INSTANTIABLE(ProgressBar, "Widgets.Status", "ProgressBar");
    QML_EXPOSE_INSTANTIABLE(StatusIndicator, "Widgets.Status", "StatusIndicator");

    connect(OS::Filesystem::get(), &OS::Filesystem::imageCached, Processing::ImageProcessing::get(), &Processing::ImageProcessing::processImage);
}
