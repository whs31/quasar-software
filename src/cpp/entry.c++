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
#include "map/markermodel.h"
#include "network/network.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtQml/qqml.h>
#include <ccl/ccl_charts.h>

#include <LPVL/Math>
#include <LPVL/MatrixPlot>

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    /*! === === === === @todo list === === === ===

        Planner points
        Protractor
        Follow UAV
        Scale grid
        Diagram
        Form image button
        Focus window
        Attitude indicator

        === === === === === === === === === === ===
    */

    qDebug() << LPVL::isNaN(0.3);

    QML_EXPOSE_INSTANCE(Config::Paths, "Config", "Paths", Config::Paths::get());
    QML_EXPOSE_INSTANCE(Config::Config, "Config", "Config", Config::Config::get());
    QML_EXPOSE_INSTANCE(GUI::Theme, "Theme", "Theme", GUI::Theme::get());
    QML_EXPOSE_INSTANCE(OS::Filesystem, "Filesystem", "Filesystem", OS::Filesystem::get());
    QML_EXPOSE_INSTANCE(Network::Network, "Network", "Network", Network::Network::get());
    QML_EXPOSE_INSTANCE(Map::ImageModel, "Images", "ImagesModel", Processing::ImageProcessing::get()->model());
    QML_EXPOSE_INSTANCE(Map::MarkerModel, "Markers", "MarkersModel", Map::ClickHandler::get()->markerModel());
    QML_EXPOSE_INSTANCE(Map::ClickHandler, "ClickHandler", "ClickHandler", Map::ClickHandler::get());

    QML_EXPOSE_INSTANTIABLE(Map::Ruler, "Ruler", "RulerModel");
    QML_EXPOSE_INSTANTIABLE(Map::Route, "Route", "Route");

    connect(OS::Filesystem::get(), &OS::Filesystem::imageListCached, Processing::ImageProcessing::get(), &Processing::ImageProcessing::processList);
}
