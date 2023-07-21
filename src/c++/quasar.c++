#include "quasar.h"
#include <QtCore/QProcess>
#include <QtCore/QTimer>
#include <QtQml/qqml.h>
#include <SDK/RealtimeLinePlot>
#include <SDK/MatrixPlot>
#include <SDK/Gizmos>
#include <QuasarSDK/API>
#include <QuasarSDK/Register>
#include "application/updatemanager.h"
#include "application/quickutils.h"
#include "gui/terminal/debugconsole.h"
#include "gui/colortheme.h"
#include "gui/notificationsmodel.h"
#include "config/paths.h"
#include "config/settings.h"
#include "filesystem/filesystem.h"
#include "processing/imageprocessing.h"
#include "processing/streamprocessor.h"
#include "map/ruler.h"
#include "map/route.h"
#include "map/clickhandler.h"
#include "map/models/imagemodel.h"
#include "map/models/streamsegmentmodel.h"
#include "map/models/geomarkermodel.h"
#include "map/models/trackeventmodel.h"
#include "map/entities/diagram.h"
#include "map/tools/offlinetileloader.h"
#include "network/http/httpdownloader.h"

using QuasarSDK::QuasarAPI;
using QuasarSDK::Enums;
using GUI::NotificationsModel;
using std::array;

QuaSAR::QuaSAR(QObject* parent)
  : QObject(parent)
  , m_updateManager(new Application::UpdateManager(this))
  , m_httpDownloader(new Networking::HTTPDownloader(this))
  , m_quickUtils(new Application::QuickUtils(this))
  , m_stream_processor(new Processing::StreamProcessor(this))
{
  QuasarSDK::registerQMLTypes();

  qmlRegisterModule("Charts", 1, 0);
  qmlRegisterType<SDK::Quick::RealtimeLinePlot>("Charts", 1, 0, "RealtimeLinePlot");
  qmlRegisterType<SDK::Quick::MatrixPlot>("Charts", 1, 0, "MatrixPlot");

  qmlRegisterModule("Application", 1, 0);
  qmlRegisterSingletonInstance<Application::UpdateManager>("Application", 1, 0, "UpdateNotifier", m_updateManager);
  qmlRegisterSingletonInstance<Networking::HTTPDownloader>("Application", 1, 0, "UpdateLoader", m_httpDownloader);
  qmlRegisterSingletonInstance<Application::QuickUtils>("Application", 1, 0, "Utils", m_quickUtils);

  qmlRegisterModule("Config", 1, 0);
  qmlRegisterSingletonInstance<Config::Paths>("Config", 1, 0, "Paths", Config::Paths::get());
  qmlRegisterSingletonInstance<Config::Settings>("Config", 1, 0, "Settings", Config::Settings::get());

  qmlRegisterModule("Terminals", 1, 0);
  qmlRegisterSingletonInstance<GUI::DebugConsole>("Terminals", 1, 0, "DebugConsole", GUI::DebugConsole::get());

  qmlRegisterModule("Notifications", 1, 0);
  qmlRegisterSingletonInstance<GUI::NotificationsModel>("Notifications", 1, 0, "NotificationsModel", GUI::NotificationsModel::get());

  qmlRegisterModule("Theme", 1, 0);
  qmlRegisterSingletonInstance<GUI::ColorTheme>("Theme", 1, 0, "ColorTheme", GUI::ColorTheme::get());

  qmlRegisterModule("Filesystem", 1, 0);
  qmlRegisterSingletonInstance<OS::Filesystem>("Filesystem", 1, 0, "Filesystem", OS::Filesystem::get());

  QuasarAPI::get()->setCompatibilityMode(Config::Settings::get()->value<bool>("misc/compatibility"));
  connect(Config::Settings::get(), &Config::Settings::compatibilityChanged, this, [this](){
    QuasarAPI::get()->setCompatibilityMode(Config::Settings::get()->value<bool>("misc/compatibility"));
  });
  QuasarAPI::get()->setPingAddressList({
    Config::Settings::get()->value<QString>("ip/de10"),
    Config::Settings::get()->value<QString>("ip/jetson"),
    Config::Settings::get()->value<QString>("ip/navigation"),
    Config::Settings::get()->value<QString>("ip/com1"),
    Config::Settings::get()->value<QString>("ip/com2")
  });
  QuasarAPI::get()->setRemoteAddressList({
    QuasarAPI::stringify(Config::Settings::get()->value<QString>("ip/computer"), Config::Settings::get()->value<QString>("port/tcp")),
    QuasarAPI::stringify(Config::Settings::get()->value<QString>("ip/de10"), Config::Settings::get()->value<QString>("port/strip"))
  });

  QuasarAPI::get()->startPings();

  qmlRegisterModule("Images", 1, 0);
  qmlRegisterSingletonInstance<Map::ImageModel>("Images", 1, 0, "ImagesModel", Processing::ImageProcessing::get()->model());
  qmlRegisterSingletonInstance<Map::StreamSegmentModel>("Images", 1, 0, "StreamSegmentModel", m_stream_processor->model());
  qmlRegisterSingletonInstance<Processing::ImageProcessing>("Images", 1, 0, "ImageProcessing", Processing::ImageProcessing::get());
  qmlRegisterSingletonInstance<Processing::StreamProcessor>("Images", 1, 0, "StreamProcessor", m_stream_processor);

  qmlRegisterModule("Markers", 1, 0);
  qmlRegisterSingletonInstance<Map::GeoMarkerModel>("Markers", 1, 0, "MarkersModel", Map::ClickHandler::get()->geoMarkerModel());

  qmlRegisterModule("ClickHandler", 1, 0);
  qmlRegisterSingletonInstance<Map::ClickHandler>("ClickHandler", 1, 0, "ClickHandler", Map::ClickHandler::get());

  qmlRegisterModule("Offline", 1, 0);
  qmlRegisterSingletonInstance<Map::OfflineTileLoader>("Offline", 1, 0, "TileLoader", Map::OfflineTileLoader::get());

  qmlRegisterModule("Ruler", 1, 0);
  qmlRegisterType<Map::Ruler>("Ruler", 1, 0, "RulerModel");

  qmlRegisterModule("Route", 1, 0);
  qmlRegisterType<Map::Route>("Route", 1, 0, "Route");
  qmlRegisterType<Map::TrackEventModel>("Route", 1, 0, "TrackEventModel");
  qmlRegisterType<Map::Diagram>("Route", 1, 0, "RadarDiagram");

  connect(OS::Filesystem::get(), &OS::Filesystem::imageListCached, Processing::ImageProcessing::get(), &Processing::ImageProcessing::processList, Qt::QueuedConnection);
  connect(Processing::ImageProcessing::get()->model(), &Map::ImageModel::markedForExport, OS::Filesystem::get(), &OS::Filesystem::exportImagesToFolder);

  connect(QuasarAPI::get(), &QuasarAPI::tcpDataReceived, this, &QuaSAR::passTCPData);
  connect(QuasarAPI::get(), &QuasarAPI::udpDataReceived, this, &QuaSAR::passUDPData);

  NotificationsModel::get()->add(NotificationsModel::NotConnected, NotificationsModel::Warn);
  connect(QuasarAPI::get(), &QuasarAPI::connectedChanged, this, [this](){
    if(not QuasarAPI::get()->isConnected())
      NotificationsModel::get()->add(NotificationsModel::NotConnected, NotificationsModel::Warn);
    else
      NotificationsModel::get()->remove(NotificationsModel::NotConnected);
  });

  m_updateManager->fetch();
  connect(this, &QuaSAR::scheduleClose, this, &QuaSAR::closeApplication);
  connect(m_httpDownloader, &Networking::HTTPDownloader::downloadFinished, this, [this](){
    #ifdef Q_OS_WIN
    QProcess::startDetached(Config::Paths::root() + "/updateservice.exe", {});
    #endif
    QTimer::singleShot(1000, this, &QuaSAR::closeApplication);
    qDebug() << "Launching" << QString(Config::Paths::root() + "/updateservice.exe");
  });
}

void QuaSAR::closeApplication() noexcept { qApp->quit(); }

void QuaSAR::passTCPData(const QByteArray& data, const QString& name) noexcept
{
  QFile file(Config::Paths::tcp() + "/" + name);
  if(not file.open(QIODevice::WriteOnly))
  {
    qCritical() << "[ENTRY] Failed to save result";
    return;
  }

  file.write(data);
  file.close();

  OS::Filesystem::get()->fetchTCPCache();
}

void QuaSAR::passUDPData(const QByteArray& data) noexcept { m_stream_processor->process(data); }
