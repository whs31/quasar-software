#include "entry.h"

#include <QtCore/QCoreApplication>
#include <QtQml/qqml.h>
#include "application/updatemanager.h"
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
#include "network/http/httpdownloader.h"

Entry::Entry(QObject* parent)
  : QObject(parent)
  , m_updateManager(new Application::UpdateManager(this))
  , m_httpDownloader(new Networking::HTTPDownloader(this))
{
  qmlRegisterSingletonInstance<Application::UpdateManager>("Application", 1, 0, "UpdateNotifier", m_updateManager);
  qmlRegisterSingletonInstance<Networking::HTTPDownloader>("Application", 1, 0, "UpdateLoader", m_httpDownloader);
  m_updateManager->fetch();

  qmlRegisterSingletonInstance<Config::Paths>("Config", 1, 0, "Paths", Config::Paths::get());
  qmlRegisterSingletonInstance<Config::Config>("Config", 1, 0, "Config", Config::Config::get());

  qmlRegisterSingletonInstance<GUI::VT100Terminal>("Terminals", 1, 0, "VT100Terminal", GUI::VT100Terminal::get());
  qmlRegisterSingletonInstance<GUI::DebugConsole>("Terminals", 1, 0, "DebugConsole", GUI::DebugConsole::get());
  qmlRegisterSingletonInstance<GUI::WarningsModel>("Notifications", 1, 0, "WarningsModel", GUI::WarningsModel::get());
  qmlRegisterSingletonInstance<GUI::ColorTheme>("Theme", 1, 0, "ColorTheme", GUI::ColorTheme::get());

  qmlRegisterSingletonInstance<OS::Filesystem>("Filesystem", 1, 0, "Filesystem", OS::Filesystem::get());

  qmlRegisterSingletonInstance<Networking::Network>("Network", 1, 0, "Network", Networking::Network::get());
  qmlRegisterUncreatableType<Networking::Enums>("Network", 1, 0, "Net", "Enumeration");

  qmlRegisterSingletonInstance<Map::ImageModel>("Images", 1, 0, "ImagesModel", Processing::ImageProcessing::get()->model());
  qmlRegisterSingletonInstance<Map::StripModel>("Images", 1, 0, "StripModel", Processing::ImageProcessing::get()->stripModel());
  qmlRegisterSingletonInstance<Map::MarkerModel>("Markers", 1, 0, "MarkersModel", Map::ClickHandler::get()->markerModel());
  qmlRegisterSingletonInstance<Map::ClickHandler>("ClickHandler", 1, 0, "ClickHandler", Map::ClickHandler::get());
  qmlRegisterSingletonInstance<Map::OfflineTileLoader>("Offline", 1, 0, "TileLoader", Map::OfflineTileLoader::get());
  qmlRegisterType<Map::Ruler>("Ruler", 1, 0, "RulerModel");
  qmlRegisterType<Map::Route>("Route", 1, 0, "Route");
  qmlRegisterType<Map::Diagram>("RadarDiagram", 1, 0, "RadarDiagram");

  qmlRegisterSingletonInstance<Processing::ImageProcessing>("ImageProcessing", 1, 0, "ImageProcessing", Processing::ImageProcessing::get());

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
