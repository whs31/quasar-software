/**
  * \class QuasarSDK::QuasarAPI CQuasarAPI.h <QuasarSDK/API>
  * \brief Публичный интерфейс для работы с сетевой составляющей РЛС "Квазар".
  * \details Представляет из себя класс-синглтон, содержащий набор
  * функций для взаимодействия с РЛС "Квазар".
  * Большая часть функций и свойств доступна в движке QML.
  *
  * Класс автоматически регистрирует себя и QuasarSDK::Enums в QML при первом вызове
  * функции get().
  * \todo Дополнить документацию
  * \extends QObject
  */

#include "CQuasarAPI.h"
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include "CConfig.h"
#include "CTelemetrySocket.h"
#include "CExecdSocket.h"
#include "CExecdArgumentParser.h"
#include "COutputSocket.h"
#include "CTCPServer.h"
#include "CStripSocket.h"
#include "CPingTester.h"
#include "COutputRedirectServer.h"

#ifdef QT_QML_LIB
#include <QtQml/qqml.h>
#endif

namespace QuasarSDK
{
  /**
   * \brief Возвращает указатель на уникальный экземпляр класса QuasarAPI.
   * \return Указатель на экземпляр QuasarAPI.
   */
  QuasarAPI* QuasarAPI::get()
  {
    static QuasarAPI instance;
    return &instance;
  }

  QuasarAPI::QuasarAPI(QObject* parent)
      : QObject(parent)
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
      , m_telemetrySocket(new TelemetrySocket(this, m_telemetry))
      , m_execdSocket(new ExecdSocket(this))
      , m_outputSocket(new OutputSocket(this))
      , m_tcpServer(new TCPServer(this))
      , m_stripSocket(new StripSocket(this))
      , m_remote_address_list({"127.0.0.1:25565", "127.0.0.1:25560"})
      , m_ping_address_list({"127.0.0.1", "127.0.0.1", "127.0.0.1", "127.0.0.1", "127.0.0.1"})
      , m_redirect(false)
      , m_redirectAddress("127.0.0.1:10338")
  {
    qDebug() << "$ [QUASAR] Beginning network setup";

    // registration
    #ifdef QT_QML_LIB
    qmlRegisterSingletonInstance<QuasarAPI>("QuaSAR.API", 1, 0, "NetworkAPI", this);
    qmlRegisterUncreatableType<QuasarSDK::Enums>("QuaSAR.API", 1, 0, "Net", "Enumeration");
    #endif

    // delay handling
    m_networkDelayTimer->start(100);
    connect(m_networkDelayTimer, &QTimer::timeout, this, [this](){ setCurrentNetworkDelay(currentNetworkDelay() + .1f); });

    // telemetry
    connect(telemetrySocket(), &TelemetrySocket::ping, this, &QuasarAPI::reset_delay);
    connect(telemetrySocket(), &TelemetrySocket::metrics, this, &QuasarAPI::telemetrySocketMetrics);
    connect(telemetry(), &Telemetry::seaLevelChanged, this, [this](){
      setArgument("--e0", telemetry()->seaLevel(), Enums::Form);
      setArgument("--e0", telemetry()->seaLevel(), Enums::Reform);
      setArgument("--e0", telemetry()->seaLevel(), Enums::Focus);
    });

    telemetrySocket()->setCheckCRC(false);

    // execd
    connect(execdSocket(), &ExecdSocket::ping, this, &QuasarAPI::reset_delay);
    connect(execdSocket(), &ExecdSocket::metrics, this, &QuasarAPI::execdSocketMetrics);
    connect(outputSocket(), &OutputSocket::received, this, &QuasarAPI::processFeedback);
    connect(outputSocket(), &OutputSocket::diskSpaceReceived, this, [this](long free, long total){
      float space(static_cast<float>(free) / static_cast<float>(total));
      remote()->setStorageSpace(space * 100);
    });

    // tcp
    connect(tcpServer(), &TCPServer::received, this, &QuasarAPI::tcpDataReceived);
    connect(tcpServer(), &TCPServer::received, this, [this](){ execute(Enums::RemoteStorageStatus); });
    connect(tcpServer(), &TCPServer::metrics, this, &QuasarAPI::lfsSocketMetrics);
    connect(tcpServer(), &TCPServer::progressChanged, this, [this](float progress){
      remote()->setDownloadProgress(progress);
    });

    // strip socket
    connect(stripSocket(), &StripSocket::receivedChunk, this, &QuasarAPI::udpDataReceived);
    connect(stripSocket(), &StripSocket::metrics, this, &QuasarAPI::stripSocketMetrics);

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
   * \property QuasarAPI::telemetry
   * \brief Предоставляет доступ к текущей телеметрии БПЛА.
   * \details Свойство доступно только для чтения.
   * \see QuasarSDK::Telemetry
   */
  Telemetry* QuasarAPI::telemetry() const { return m_telemetry; }

  /**
   * \property QuasarAPI::remote
   * \brief Предоставляет доступ к набору состояний, связанных с РЛС.
   * \details Свойство доступно только для чтения.
   * \see QuasarSDK::RemoteData
   */
  RemoteData* QuasarAPI::remote() const { return m_remoteData; }

  /**
   * \property QuasarAPI::isConnected
   * \brief Предоставляет текущее состояния подключения к РЛС.
   * \details Свойство доступно для чтения и записи.
   */
  bool QuasarAPI::isConnected() const { return m_connected; }
  void QuasarAPI::setConnected(bool o)
  {
    if(m_connected == o)
      return;
    m_connected = o;
    emit connectedChanged();
  }

  /**
   * \property QuasarAPI::currentNetworkDelay
   * \brief Предоставляет текущее значение задержки между пакетами РЛС.
   * \details Свойство доступно для чтения и записи.
   */
  float QuasarAPI::currentNetworkDelay() const { return m_currentNetworkDelay; }
  void QuasarAPI::setCurrentNetworkDelay(float o)
  {
    if(m_currentNetworkDelay == o)
      return;
    m_currentNetworkDelay = o;
    emit currentNetworkDelayChanged();

    if(m_currentNetworkDelay > Config::get()->value<float>("NETWORK_DELAY_THRESHOLD_DISCONNECT"))
      setConnected(false);
    else
      setConnected(true);
  }

  /**
   * \brief Возвращает указатель на сокет телеметрии.
   * \return Ненулевой указатель на TelemetrySocket.
   */
  TelemetrySocket* QuasarAPI::telemetrySocket() { return m_telemetrySocket; }

  /**
   * \brief Возвращает указатель на сокет \c execd.
   * \return Ненулевой указатель на ExecdSocket.
   */
  ExecdSocket* QuasarAPI::execdSocket() { return m_execdSocket; }

  /**
   * \brief Возвращает указатель на сокет обратной связи.
   * \return Ненулевой указатель на OutputSocket.
   */
  OutputSocket* QuasarAPI::outputSocket() { return m_outputSocket; }

  /**
   * \brief Возвращает указатель на сервер TCP-IP для сервиса \c fsend.
   * \return Ненулевой указатель на TCPServer.
   */
  TCPServer* QuasarAPI::tcpServer() { return m_tcpServer; }

  /**
   * \brief Возвращает указатель на сокет для полосовых изображений (UDP).
   * \return Ненулевой указатель на StripSocket.
   */
  StripSocket* QuasarAPI::stripSocket() { return m_stripSocket; }

  /**
   * \brief Производит попытку подключения к РЛС по указанным адресам.
   * \details Функция запускает все дочерние сокеты с выбранными
   * параметрами и адресами.
   * \param telemetry_request_address - IP-адрес для запросов телеметрии в формате <tt>192.168.1.0:5555</tt>.
   * \param telemetry_receive_address - IP-адрес для получения телеметрии.
   * \param telemetry_frequency - интервал в секундах между пакетами телеметрии.
   * \param execd_address - IP-адрес для команд в сервис \b execd на РЛС.
   * \param feedback_address - IP-адрес для приема потока \b stdout с РЛС.
   * \param tcp_lfs_address - IP-адрес для сервера TCP-IP.
   * \param udp_lfs_address - IP-адрес для сокета полосовых изображений.
   * \note Может быть вызвана из QML через мета-объектную систему.
   * \see stop
   * \see startPings
   */
  void QuasarAPI::start(const QString& telemetry_request_address, const QString& telemetry_receive_address,
                        float telemetry_frequency, const QString& execd_address, const QString& feedback_address,
                        const QString& tcp_lfs_address, const QString& udp_lfs_address) noexcept
  {
    telemetrySocket()->setFrequency(telemetry_frequency);
    telemetrySocket()->start2way(telemetry_request_address, telemetry_receive_address);
    execdSocket()->start(execd_address);
    outputSocket()->start(feedback_address);
    tcpServer()->start(tcp_lfs_address);
    stripSocket()->start(udp_lfs_address);

    if(m_redirect)
      m_redirectServer->start(m_redirectAddress);
  }

  /**
   * \brief Начинает проверку 5-ти выбранных адресов на доступность.
   * \details После вызова этой функции будут запущены 5 хостов консоли
   * с командой \c ping, которые будут проверять на доступность адреса,
   * заданные функцией setPingAddressList.
   * \note Может быть вызвана из QML через мета-объектную систему.
   * \warning Эта функция должна быть вызвана после того, как будут
   * заданы адреса для проверки.
   * \see setPingAddressList
   */
  void QuasarAPI::startPings() noexcept
  {
    qDebug() << "$ [QUASAR] Starting pings at" << m_ping_address_list[0] << "|"
                                               << m_ping_address_list[1] << "|"
                                               << m_ping_address_list[2] << "|"
                                               << m_ping_address_list[3] << "|"
                                               << m_ping_address_list[4];
    m_de10PingTester->start(m_ping_address_list[0]);
    m_jetson0PingTester->start(m_ping_address_list[1]);
    m_navPingTester->start(m_ping_address_list[2]);
    m_com1PingTester->start(m_ping_address_list[3]);
    m_com2PingTester->start(m_ping_address_list[4]);
  }

  /**
    * \brief Производит отключение от РЛС.
    * \details Функция останавливает все дочерние сокеты и устанавливает
    * состояние подключения и задержку.
    * \note Может быть вызвана из QML через мета-объектную систему.
    * \see start
    */
  void QuasarAPI::stop() noexcept
  {
    telemetrySocket()->stop2way();
    execdSocket()->stop();
    outputSocket()->stop();
    tcpServer()->stop();
    stripSocket()->stop();
    m_redirectServer->stop();

    this->setCurrentNetworkDelay(100);
  }

  /**
    * \brief Выполняет встроенную команду сервиса \b execd.
    * \details Функция посылает в сервис \b execd выбранную встроенную
    * команду из списка команд (см. QuasarSDK::Enums). Если команда
    * требует дополнительных аргументов, то они будут добавлены автоматически.
    * \param command - выбранная команда.
    * \note Может быть вызвана из QML через мета-объектную систему.
    */
  void QuasarAPI::execute(QuasarSDK::Enums::NetworkCommand command) noexcept
  {
    switch(command)
    {
      case Enums::FormImage:
      case Enums::SimpleStrip:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Form);
        break;
      case Enums::FocusImage:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Focus);
        break;
      case Enums::ReformImage:
        this->setArgument("--remote", m_remote_address_list[0], Enums::Reform);
        break;
      case Enums::StartStrip:
      case Enums::StopStrip:
        this->setArgument("--remote", m_remote_address_list[1], Enums::Form);
        break;
      default: break;
    }

    execdSocket()->execute(command);
  }

  /**
    * \brief Выполняет произвольную команду сервиса \b execd.
    * \details Функция конвертирует выбранную строку в команду
    * сервиса \b execd и отправляет ее на РЛС. Если команда валидна,
    * то она будет выполнена.
    * \param command - строка для выполнения.
    * \note Может быть вызвана из QML через мета-объектную систему.
    * \todo Интеграция с терминалом VT100.
    */
  void QuasarAPI::execute(const QString& command) noexcept
  {
    //GUI::VT100Terminal::get()->append("% Выполняется " + string);
    execdSocket()->execute(command);
  }

  /**
    * \brief Возвращает аргумент из списка сервиса \b execd.
    * \details Функция возвращает константный аргумент по заданному ключу
    * и категории аргументов.
    * \param key - ключ (например, <tt>"--x0"</tt>).
    * \param category - категория аргумента (см. QuasarSDK::Enums::ArgumentCategory).
    * \note Может быть вызвана из QML через мета-объектную систему.
    * \see setArgument
    */
  QString QuasarAPI::argument(const QString& key, QuasarSDK::Enums::ArgumentCategory category) noexcept
  {
    switch (category)
    {
      case Enums::Form: return execdSocket()->parser()->formArgumentList[key].value;
      case Enums::Focus: return execdSocket()->parser()->focusArgumentList[key].value;
      case Enums::Reform: return execdSocket()->parser()->reformArgumentList[key].value;
      default: return "Argument Category Error"; break;
    }
  }

  /**
    * \brief Устанавливает аргумент из списка сервиса \b execd.
    * \details Функция устанавливает выбранный аргумент в приватный список
    * аргументов сервиса \b execd и выбранную категорию. Значение аргумента
    * будет автоматически приведено к корректному виду (\c int, \c float, \c string).
    * \param key - ключ (например, <tt>"--x0"</tt>).
    * \param value - новое значение аргумента.
    * \param category - категория аргумента (см. QuasarSDK::Enums::ArgumentCategory).
    * \note Может быть вызвана из QML через мета-объектную систему.
    * \see argument
    */
  void QuasarAPI::setArgument(const QString& key, const QVariant& value,
                              QuasarSDK::Enums::ArgumentCategory category) noexcept
  {
    switch (category)
    {
      case Enums::Form: execdSocket()->parser()->formArgumentList[key].set(value); break;
      case Enums::Focus: execdSocket()->parser()->focusArgumentList[key].set(value); break;
      case Enums::Reform: execdSocket()->parser()->reformArgumentList[key].set(value); break;
      default: qCritical() << "[NETWORK] Invalid category for argument provided"; break;
    }
  }

  /**
    * \brief Конвертирует IP-адрес и порт в общую строку.
    * \param ip - IP-адрес (например, <tt>"192.168.1.10"</tt>).
    * \param port - порт в виде строки (например, <tt>"9955"</tt>).
    * \return Строка с IP-адресом и портом (например, <tt>"192.168.1.10:9955"</tt>).
    * \note Может быть вызвана из QML через мета-объектную систему.
    */
  QString QuasarAPI::stringify(const QString& ip, const QString& port) { return QString(ip + ":" + port); }

  /// \todo Интеграция с терминалом VT100.
  void QuasarAPI::processFeedback(QByteArray data) noexcept
  {
    if(m_redirect)
      m_redirectServer->push(data);
    //GUI::VT100Terminal::get()->print(data);
  }

  void QuasarAPI::reset_delay() { this->setCurrentNetworkDelay(0); }

  /**
   * \brief Задает адреса для обратной связи сервиса \c fsend.
   * \details Порядок адресов следующий:
   *    - TCP-IP сервер (например, <tt>192.168.1.10:10000</tt>
   *    - UDP сокет для полосовых изображений (например, <tt>192.168.1.10:48455</tt>
   * \param list - массив из двух адресов.
   * \warning Функция должна быть вызвана перед вызовом метода start.
   */
  void QuasarAPI::setRemoteAddressList(const std::array<QString, 2>& list) noexcept
  {
    m_remote_address_list = list;
  }

  /**
   * \brief Задает список адресов для проверки на доступность.
   * \details Порядок адресов следующий:
   *    - IP-адрес DE10-NANO
   *    - IP-адрес NVidia Jetson
   *    - IP-адрес бортовой навигации
   *    - IP-адрес коммутатора антенн
   *    - IP-адрес коммутатора питания
   * Адреса должны предоставляться без портов (напр. <tt>127.0.0.1</tt>).
   * \param list - массив из пяти адресов.
   * \warning Функция должна быть вызвана перед вызовом метода startPings.
   * \see startPings
   */
  void QuasarAPI::setPingAddressList(const std::array<QString, 5>& list) noexcept
  {
    m_ping_address_list = list;
  }

  /**
   * \brief Включает перенаправление вывода РЛС на указанный адрес.
   * \param address - IPv4-адрес и порт для перенаправления.
   */
  void QuasarAPI::enableRedirect(const QString& address) noexcept
  {
    m_redirect = true;
    m_redirectAddress = address;
  }

  /// \brief Выключает перенаправление вывода РЛС.
  void QuasarAPI::disableRedirect() noexcept
  {
    m_redirect = false;
    m_redirectAddress.clear();
  }
} // QuasarSDK
