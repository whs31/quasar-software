#include "entry.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <QtQml/qqml.h>

#include "gui/theme/include/theme.h"
#include "gui/terminal/vt100terminal.h"
#include "gui/terminal/debugconsole.h"
#include "gui/warningsmodel.h"
#include "config/paths.h"
#include "config/config.h"
#include "filesystem/filesystem.h"
#include "processing/imageprocessing.h"
#include "map/ruler.h"
#include "map/route.h"
#include "map/clickhandler.h"
#include "map/imagemodel.h"
#include "map/markermodel.h"
#include "map/entities/diagram.h"
#include "map/tools/offlinetileloader.h"
#include "network/network.h"

Entry::Entry(QObject *parent)
    : QObject{parent}
{
    QML_EXPOSE_INSTANCE(Config::Paths, "Config", "Paths", Config::Paths::get());
    QML_EXPOSE_INSTANCE(Config::Config, "Config", "Config", Config::Config::get());
    QML_EXPOSE_INSTANCE(GUI::Theme, "Theme", "Theme", GUI::Theme::get());
    QML_EXPOSE_INSTANCE(GUI::VT100Terminal, "Terminals", "VT100Terminal", GUI::VT100Terminal::get());
    QML_EXPOSE_INSTANCE(GUI::DebugConsole, "Terminals", "DebugConsole", GUI::DebugConsole::get());
    QML_EXPOSE_INSTANCE(GUI::WarningsModel, "Notifications", "WarningsModel", GUI::WarningsModel::get());
    QML_EXPOSE_INSTANCE(OS::Filesystem, "Filesystem", "Filesystem", OS::Filesystem::get());
    QML_EXPOSE_INSTANCE(Network::Network, "Network", "Network", Network::Network::get());
    QML_EXPOSE_INSTANCE(Map::ImageModel, "Images", "ImagesModel", Processing::ImageProcessing::get()->model());
    QML_EXPOSE_INSTANCE(Map::MarkerModel, "Markers", "MarkersModel", Map::ClickHandler::get()->markerModel());
    QML_EXPOSE_INSTANCE(Map::ClickHandler, "ClickHandler", "ClickHandler", Map::ClickHandler::get());
    QML_EXPOSE_INSTANCE(Map::OfflineTileLoader, "Offline", "TileLoader", Map::OfflineTileLoader::get());
    QML_EXPOSE_INSTANCE(Processing::ImageProcessing, "ImageProcessing", "ImageProcessing", Processing::ImageProcessing::get());

    QML_EXPOSE_INSTANTIABLE(Map::Ruler, "Ruler", "RulerModel");
    QML_EXPOSE_INSTANTIABLE(Map::Route, "Route", "Route");
    QML_EXPOSE_INSTANTIABLE(Map::Diagram, "RadarDiagram", "RadarDiagram");

    connect(OS::Filesystem::get(), &OS::Filesystem::imageListCached, Processing::ImageProcessing::get(), &Processing::ImageProcessing::processList);
    connect(Processing::ImageProcessing::get()->model(), &Map::ImageModel::markedForExport, OS::Filesystem::get(), &OS::Filesystem::exportImagesToFolder);
    connect(Config::Config::get(), &Config::Config::scheduleRestart, this, [this](){
        qWarning() << "[CORE] Requested restart, but current configuration will fail executing it.";
        qWarning() << "[CORE] Please, restart manually.";
//        QCoreApplication::instance()->quit();
//        QProcess::startDetached(QCoreApplication::instance()->arguments()[0],
//                                QCoreApplication ::instance()->arguments());
    });
    connect(Config::Config::get(), &Config::Config::tcpLFSPortChanged, this, [this](){
        Network::Network::get()->setArgument("--remote", QString(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort)), Network::Network::Form);
        Network::Network::get()->setArgument("--remote", QString(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort)), Network::Network::Focus);
        Network::Network::get()->setArgument("--remote", QString(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort)), Network::Network::Reform);
    });

    Network::Network::get()->setArgument("--remote", QString(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort)), Network::Network::Form);
    Network::Network::get()->setArgument("--remote", QString(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort)), Network::Network::Focus);
    Network::Network::get()->setArgument("--remote", QString(CONFIG(localIP) + ":" + CONFIG(tcpLFSPort)), Network::Network::Reform);

    GUI::WarningsModel::get()->append("Отсутствует соединение с РЛС", false);
    connect(Network::Network::get(), &Network::Network::connectedChanged, this, [this](){
        if(Network::Network::get()->connected() != 2)
            GUI::WarningsModel::get()->append("Отсутствует соединение с РЛС", false);
        else
            GUI::WarningsModel::get()->removeAt("Отсутствует соединение с РЛС");
    });
}
