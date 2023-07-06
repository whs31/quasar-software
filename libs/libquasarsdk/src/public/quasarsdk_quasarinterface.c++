//
// Created by whs31 on 04.07.23.
//

#include "quasarsdk_quasarinterface.h"
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include "public/quasarsdk_config.h"
#include "public/navd2/quasarsdk_telemetrysocket.h"
#include "public/navd2/quasarsdk_telemetry.h"
#include "public/execd/quasarsdk_execdsocket.h"
#include "public/execd/quasarsdk_outputsocket.h"
#include "public/execd/quasarsdk_remotedata.h"
#include "public/fsend/quasarsdk_tcpserver.h"
#include "public/fsend/quasarsdk_stripsocket.h"
#include "public/utl/quasarsdk_pingtester.h"
#include "public/utl/quasarsdk_outputredirectserver.h"

namespace QuasarSDK
{
  /**
   * \brief Возвращает указатель на уникальный экземпляр класса QuasarInterface.
   * \return Указатель на экземпляр QuasarInterface.
   */
  QuasarInterface* QuasarInterface::get()
  {
    static QuasarInterface instance;
    return &instance;
  }

  QuasarInterface::QuasarInterface(QObject* parent)
      :
      QObject(parent)
      , m_telemetry(new Telemetry(this))
      , m_remoteData(new RemoteData(this))
      , m_connected(false)
      , m_currentNetworkDelay(Config::get()->value<float>("NETWORK_DELAY_THRESHOLD_DISCONNECT") + .1f)
      , m_networkDelayTimer(new QTimer(this))
      , m_de10PingTester(new PingTester(this))
      , m_jetson0PingTester(new PingTester(this))
      , m_navPingTester(new PingTester(this))
      , m_com1PingTester(new PingTester(this))
      , m_com2PingTester(new PingTester(this))
      , m_redirectServer(new OutputRedirectServer(this))
      , m_telemetrySocket(new TelemetrySocket(this))
      , m_execdSocket(new ExecdSocket(this))
      , m_outputSocket(new OutputSocket(this))
      , m_tcpServer(new TCPServer(this))
      , m_stripSocket(new StripSocket(this))
      , m_remote_address_list({"127.0.0.1:25565", "127.0.0.1:25560"})
      , m_ping_address_list({"127.0.0.1", "127.0.0.1", "127.0.0.1", "127.0.0.1", "127.0.0.1"})
      , m_redirect(false)
  {
    qDebug() << "$ [QUASAR] Beginning network setup";

    // delay handling
    m_networkDelayTimer->start(100);
    connect(m_networkDelayTimer, &QTimer::timeout, this, [this](){ setCurrentNetworkDelay(currentNetworkDelay() + .1f); });

    // telemetry
    connect(telemetrySocket(), &TelemetrySocket::ping, this, &QuasarInterface::reset_delay);
    connect(telemetrySocket(), &TelemetrySocket::metrics, this, &QuasarInterface::telemetrySocketMetrics);
    connect(telemetry(), &Telemetry::seaLevelChanged, this, [this](){
      setArgument("--e0", telemetry()->seaLevel(), Enums::Form);
      setArgument("--e0", telemetry()->seaLevel(), Enums::Reform);
      setArgument("--e0", telemetry()->seaLevel(), Enums::Focus);
    });

    // execd
    connect(execdSocket(), &ExecdSocket::ping, this, &QuasarInterface::reset_delay);
    connect(execdSocket(), &ExecdSocket::metrics, this, &QuasarInterface::execdSocketMetrics);
    connect(outputSocket(), &OutputSocket::received, this, &QuasarInterface::processFeedback);
    connect(outputSocket(), &OutputSocket::diskSpaceReceived, this, [this](long free, long total){
      float space(static_cast<float>(free) / static_cast<float>(total));
      remote()->setStorageSpace(space * 100);
    });

    // tcp
    connect(tcpServer(), &TCPServer::received, this, &QuasarInterface::tcpDataReceived);
    connect(tcpServer(), &TCPServer::received, this, [this](){ execute(Enums::RemoteStorageStatus); });
    connect(tcpServer(), &TCPServer::metrics, this, &QuasarInterface::lfsSocketMetrics);
    connect(tcpServer(), &TCPServer::progressChanged, this, [this](float progress){
      remote()->setDownloadProgress(progress);
    });

    // strip socket
    connect(stripSocket(), &StripSocket::receivedChunk, this, &QuasarInterface::udpDataReceived);
    connect(stripSocket(), &StripSocket::metrics, this, &QuasarInterface::stripSocketMetrics);

    // ping testers
    QObject::connect(m_de10PingTester, &PingTester::result, this, [this](Enums::PingStatus result){
      auto list = remote()->pings();
      list[0] = result;
      remote()->setPings(list);
    });
    QObject::connect(m_jetson0PingTester, &PingTester::result, this, [this](Enums::PingStatus result){
      auto list = remote()->pings();
      list[1] = result;
      remote()->setPings(list);
    });
    QObject::connect(m_navPingTester, &PingTester::result, this, [this](Enums::PingStatus result){
      auto list = remote()->pings();
      list[2] = result;
      remote()->setPings(list);
    });
    QObject::connect(m_com1PingTester, &PingTester::result, this, [this](Enums::PingStatus result){
      auto list = remote()->pings();
      list[3] = result;
      remote()->setPings(list);
    });
    QObject::connect(m_com2PingTester, &PingTester::result, this, [this](Enums::PingStatus result){
      auto list = remote()->pings();
      list[4] = result;
      remote()->setPings(list);
    });
  }

  /**
   * \property QuasarInterface::telemetry
   * \brief
   */
  Telemetry* QuasarInterface::telemetry() const { return m_telemetry; }

  RemoteData* QuasarInterface::remote() const
  {
    return nullptr;
  }

  bool QuasarInterface::isConnected() const
  {
    return false;
  }

  void QuasarInterface::setConnected(bool)
  {

  }

  float QuasarInterface::currentNetworkDelay() const
  {
    return 0;
  }

  void QuasarInterface::setCurrentNetworkDelay(float)
  {

  }

  TelemetrySocket* QuasarInterface::telemetrySocket()
  {
    return nullptr;
  }

  ExecdSocket* QuasarInterface::execdSocket()
  {
    return nullptr;
  }

  OutputSocket* QuasarInterface::outputSocket()
  {
    return nullptr;
  }

  TCPServer* QuasarInterface::tcpServer()
  {
    return nullptr;
  }

  StripSocket* QuasarInterface::stripSocket()
  {
    return nullptr;
  }

  void QuasarInterface::start(const QString& telemetry_request_address, const QString& telemetry_receive_address,
                              float telemetry_frequency, const QString& execd_address, const QString& feedback_address,
                              const QString& tcp_lfs_address, const QString& udp_lfs_address) noexcept
  {

  }

  void QuasarInterface::startPings() noexcept
  {

  }

  void QuasarInterface::stop() noexcept
  {

  }

  void QuasarInterface::execute(QuasarSDK::Enums::NetworkCommand command) noexcept
  {

  }

  void QuasarInterface::execute(const QString& command) noexcept
  {

  }

  QString QuasarInterface::argument(const QString& key, QuasarSDK::Enums::ArgumentCategory category) const noexcept
  {
    return QString();
  }

  void QuasarInterface::setArgument(const QString& key, const QVariant& value,
                                    QuasarSDK::Enums::ArgumentCategory category) noexcept
  {

  }

  QString QuasarInterface::stringify(const QString& ip, const QString& port)
  {
    return QString();
  }

  void QuasarInterface::processFeedback(QByteArray) noexcept
  {

  }

  void QuasarInterface::reset_delay() { this->setCurrentNetworkDelay(0); }

  void QuasarInterface::setRemoteAddressList(const std::array<QString, 2>& list) noexcept
  {
    m_remote_address_list = list;
  }

  void QuasarInterface::setPingAddressList(const std::array<QString, 5>& list) noexcept
  {
    m_ping_address_list = list;
  }

  void QuasarInterface::enableRedirect() noexcept { m_redirect = false; }

  void QuasarInterface::disableRedirect() noexcept { m_redirect = true; }
} // QuasarSDK