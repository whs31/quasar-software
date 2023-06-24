#include "entry.h"

#include <QtCore/QCoreApplication>
#include <QtQml/qqml.h>
#include "gui/theme/include/theme.h"
#include "gui/terminal/vt100terminal.h"
#include "gui/terminal/debugconsole.h"
#include "gui/warningsmodel.h"
#include "gui/colortheme.h"
#include "config/paths.h"
#include "config/config.h"
#include "filesystem/filesystem.h"
#include "processing/imageprocessing.h"
#include "map/ruler.h"
#include "map/route.h"
#include "map/clickhandler.h"
#include "map/models/imagemodel.h"
#include "map/models/stripmodel.h"
#include "map/models/markermodel.h"
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
  qmlRegisterSingletonInstance<GUI::ColorTheme>("Theme", 1, 0, "ColorTheme", GUI::ColorTheme::get());
  QML_EXPOSE_INSTANCE(OS::Filesystem, "Filesystem", "Filesystem", OS::Filesystem::get());
  QML_EXPOSE_INSTANCE(Networking::Network, "Network", "Network", Networking::Network::get());
  qmlRegisterUncreatableType<Networking::Enums>("Network", 1, 0, "Net", "Enumeration");
  QML_EXPOSE_INSTANCE(Map::ImageModel, "Images", "ImagesModel", Processing::ImageProcessing::get()->model());
  QML_EXPOSE_INSTANCE(Map::StripModel, "Images", "StripModel", Processing::ImageProcessing::get()->stripModel());
  QML_EXPOSE_INSTANCE(Map::MarkerModel, "Markers", "MarkersModel", Map::ClickHandler::get()->markerModel());
  QML_EXPOSE_INSTANCE(Map::ClickHandler, "ClickHandler", "ClickHandler", Map::ClickHandler::get());
  QML_EXPOSE_INSTANCE(Map::OfflineTileLoader, "Offline", "TileLoader", Map::OfflineTileLoader::get());
  QML_EXPOSE_INSTANCE(Processing::ImageProcessing, "ImageProcessing", "ImageProcessing", Processing::ImageProcessing::get());

  QML_EXPOSE_INSTANTIABLE(Map::Ruler, "Ruler", "RulerModel");
  QML_EXPOSE_INSTANTIABLE(Map::Route, "Route", "Route");
  QML_EXPOSE_INSTANTIABLE(Map::Diagram, "RadarDiagram", "RadarDiagram");

  connect(OS::Filesystem::get(), &OS::Filesystem::imageListCached, Processing::ImageProcessing::get(), &Processing::ImageProcessing::processList, Qt::QueuedConnection);
  connect(Processing::ImageProcessing::get()->model(), &Map::ImageModel::markedForExport, OS::Filesystem::get(), &OS::Filesystem::exportImagesToFolder);
  connect(Config::Config::get(), &Config::Config::scheduleRestart, this, [this](){
    qWarning() << "[CORE] Requested restart, but current configuration will fail executing it.";
    qWarning() << "[CORE] Please, restart manually.";
  });

  GUI::WarningsModel::get()->append(GUI::WarningsModel::NotConnected, "Отсутствует соединение с РЛС", false);
  connect(Networking::Network::get(), &Networking::Network::connectedChanged, this, [this](){
    if(Networking::Network::get()->connected() != 2)
      GUI::WarningsModel::get()->append(GUI::WarningsModel::NotConnected, "Отсутствует соединение с РЛС", false);
    else
      GUI::WarningsModel::get()->remove(GUI::WarningsModel::NotConnected);
  });
}
