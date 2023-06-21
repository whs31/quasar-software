#pragma once

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#define CONFIG(x) Config::Config::get()->x()

class QSettings;

//! @brief Пространство имен для данных, сохраняемых между сессиями.
namespace Config
{
    /*! 
     *  @brief Класс-синглтон для работы с локальными настройками приложения, сохранямыми на диске.
     *  @details Класс предоставляет доступ к чтению и записи настроек конфигурационного
     *  .ini файла приложения. Автоматически загружает настройки по умолчанию на чистой
     *  установке приложения. Основное предназначение класса - обёртка над экземпляром класса
     *  \b QSettings, предоставляющая глобально доступные функции и свойства (в том числе для
     *  QML).
     *
     *  Класс Config также предоставляет полезный макрос для доступа к его свойствам и функциям из
     *  других классов и пространств имён в С++:
     *  \code {.cpp}
     *  CONFIG(property_name);
     *  \endcode
     *
     *  Пример доступа к конфигурационному файлу приложения из С++:
     *  \code {.cpp}
     *  Network::startTelemetrySocket(CONFIG(remoteIP) + ":" + CONFIG(telemetryPort), CONFIG(telemetryFrequency));
     *  \endcode
     *  
     *  Пример доступа к конфигурационному файлу приложения из QML^
     *  \code {.js}
     *  Network.startTelemetrySocket(Config.remoteIP + ":" + Config.telemetryPort, Config.telemetryFrequency);
     *  \endcode
     *
     *  @note Класс необходимо зарегистрировать как \c singletonInstance для доступа к нему из QML.
     */
    class Config : public QObject
    {
        Q_OBJECT

        /*! 
         *  @property remoteIP
         *  @brief IPv4-адрес РЛС (DE10-NANO).
         *  @details Это свойство используется для сокета телеметрии и сокета \b Execd.
         *  По умолчанию, свойство возвращает \c 127.0.0.1 (localhost).
         *  @par %remoteIP(), setRemoteIP(), remoteIPChanged()
         */
        Q_PROPERTY(QString remoteIP READ remoteIP WRITE setRemoteIP NOTIFY remoteIPChanged)
        
        /*! 
         *  @property localIP
         *  @brief IPv4-адрес компьютера, на котором установлео приложение.
         *  @details Это свойство используется для сокета обратной связи, \b TCP-IP LFS
         *  сокета и \b UDP LFS сокета.
         *  По умолчанию, свойство возвращает \c 127.0.0.1 (localhost).
         *  @par %localIP(), setLocalIP(), localIPChanged()
         */
        Q_PROPERTY(QString localIP READ localIP WRITE setLocalIP NOTIFY localIPChanged)
        
        /*! 
         *  @property jetsonIP
         *  @brief IPv4-адрес вычислителя Jetson Xavier.
         *  @details В настоящее время это свойство используется только для проверки
         *  доступности соединения с вычислителем.
         *  По умолчанию, свойство возвращает \c 192.168.1.48.
         *  @par %jetsonIP(), setJetsonIP(), jetsonIPChanged()
         */
        Q_PROPERTY(QString jetsonIP READ jetsonIP WRITE setJetsonIP NOTIFY jetsonIPChanged)

        /*! 
         *  @property navIP
         *  @brief IPv4-адрес бортовой навигации.
         *  @details В настоящее время это свойство используется только для проверки
         *  доступности соединения с навигационным модулем на борту.
         *  По умолчанию, свойство возвращает \c 192.168.1.49.
         *  @par %navIP(), setNavIP(), navIPChanged()
         */
        Q_PROPERTY(QString navIP READ navIP WRITE setNavIP NOTIFY navIPChanged)

        /*! 
         *  @property utl1IP
         *  @brief Зарезервированный IPv4-адрес.
         *  @details В настоящее время это свойство используется только для проверки
         *  доступности соединения с указанным IP-адресом. В дальнейшем развитии программы,
         *  эт свойство будет хранить адрес коммутатора антенн.
         *  По умолчанию, свойство возвращает \c 192.168.1.50.
         *  @par %utl1IP(), setUtl1IP(), utl1IPChanged()
         */
        Q_PROPERTY(QString utl1IP READ utl1IP WRITE setUtl1IP NOTIFY utl1IPChanged)

        /*! 
         *  @property utl2IP
         *  @brief Зарезервированный IPv4-адрес.
         *  @details В настоящее время это свойство используется только для проверки
         *  доступности соединения с указанным IP-адресом. В дальнейшем развитии программы,
         *  эт свойство будет хранить адрес коммутатора питания.
         *  По умолчанию, свойство возвращает \c 192.168.1.51.
         *  @par %utl2IP(), setUtl2IP(), utl2IPChanged()
         */
        Q_PROPERTY(QString utl2IP READ utl2IP WRITE setUtl2IP NOTIFY utl2IPChanged)

        /*! 
         *  @property telemetryPort
         *  @brief Port for requesting telemetry.
         *  @details This port is used for connecting to SAR \b navd2 service
         *  and requesting telemetry. Needs to be used in pair with property #remoteIP.
         *  По умолчанию, свойство возвращает \c 9955.
         *  @par %telemetryPort(), setTelemetryPort(), telemetryPortChanged()
         */
        Q_PROPERTY(QString telemetryPort READ telemetryPort WRITE setTelemetryPort NOTIFY telemetryPortChanged)

        /*! 
         *  @property telemetryRecvPort
         *  @brief Port for receiving telemetry.
         *  @details This port is used for receiving telemetry from SAR \b navd2 service
         *  and requesting telemetry. Needs to be used in pair with property #localIP.
         *  By default, this property returns \c 10337.
         *  @par %telemetryRecvPort(), setTelemetryRecvPort(), telemetryRecvPortChanged()
         */
        Q_PROPERTY(QString telemetryRecvPort READ telemetryRecvPort WRITE setTelemetryRecvPort NOTIFY telemetryRecvPortChanged)

        /*! 
         *  @property tcpLFSPort
         *  @brief Port for receiving TCP-IP fsend data.
         *  @details TCP-IP LFS server will be working on this port.
         *  SAR \b fsend service will try to connect to this port when data is ready to send.
         *  Application will automatically set this port and #localIP as \b execd argument.
         *  Needs to be used in pair with #localIP.
         *  By default, this property returns \c 10000.
         *  @par %tcpLFSPort(), setTcpLFSPort(), tcpLFSPortChanged()
         */
        Q_PROPERTY(QString tcpLFSPort READ tcpLFSPort WRITE setTcpLFSPort NOTIFY tcpLFSPortChanged)

        /*! 
         *  @property udpLFSPort
         *  @brief Port for receiving UDP \b fsend data.
         *  @details UDP LFS server will be working on this port.
         *  SAR \b fsend service will try to connect to this port when strip data is ready to send.
         *  Needs to be used in pair with #localIP.
         *  By default, this property returns \c 48455.
         *  @warning Functionality of UDP LFS server is currently \b not implemented.
         *  @par %udpLFSPort(), setUdpLFSPort(), udpLFSPortChanged()
         */
        Q_PROPERTY(QString udpLFSPort READ udpLFSPort WRITE setUdpLFSPort NOTIFY udpLFSPortChanged)

        /*! 
         *  @property execdPort
         *  @brief Port for SAR \b execd service.
         *  @details Application will send command requests to this port.
         *  SAR can provide \b execd feedback (not to confuse with \b stdout feedback) to #localIP.
         *  Needs to be used in pair with #remoteIP.
         *  By default, this property returns \c 9845.
         *  @par %execdPort(), setExecdPort(), execdPortChanged()
         */
        Q_PROPERTY(QString execdPort READ execdPort WRITE setExecdPort NOTIFY execdPortChanged)

        /*! 
         *  @property feedbackPort
         *  @brief Port for SAR \b execd service.
         *  @details Port for SAR \b stdout/stderr.
         *  SAR will redirect it's \b stdout and \b stderr to this port.
         *  Needs to be used in pair with #localIP.
         *  By default, this property returns \c 9846.
         *  @par %feedbackPort(), setFeedbackPort(), feedbackPortChanged()
         */
        Q_PROPERTY(QString feedbackPort READ feedbackPort WRITE setFeedbackPort NOTIFY feedbackPortChanged)

        /*! 
         *  @property telemetryFrequency
         *  @brief Telemetry package interval in seconds.
         *  @details Describes how fast SAR \b navd2 service will send telemetry
         *  packages to application host computer.
         *  By default, this property returns \c 0.1 (seconds).
         *  @par %telemetryFrequency(), setTelemetryFrequency(), telemetryFrequencyChanged()
         */
        Q_PROPERTY(float telemetryFrequency READ telemetryFrequency WRITE setTelemetryFrequency NOTIFY telemetryFrequencyChanged)

        /*! 
         *  @property proxyEnabled
         *  @brief Legacy setting for replacing \b --remote flag.
         *  @details If this property evaluates to true, application will
         *  replace #localIP in --remote \b execd argument with #remoteIP.
         *  By default, this property returns \c false.
         *  @warning Implementation removed in \b version \b 2.0.
         *  @par %proxyEnabled(), setProxyEnabled(), proxyEnabledChanged()
         */
        Q_PROPERTY(bool proxyEnabled READ proxyEnabled WRITE setProxyEnabled NOTIFY proxyEnabledChanged)

        /*! 
         *  @property tcpMarker
         *  @brief Compatibility setting for old \b fsend versions.
         *  @details Describes, which split char between file size and 
         *  file name will be used on parsing TCP-IP data packet.
         *  In known cases, can evaluate to \c NULL char and \c NEWLINE char.
         *  By default, this property returns \c \0 (NULL).
         *  @par %tcpMarker(), setTcpMarker(), tcpMarkerChanged()
         */
        Q_PROPERTY(QString tcpMarker READ tcpMarker WRITE setTcpMarker NOTIFY tcpMarkerChanged)

        /*! 
         *  @property antennaAlignment
         *  @brief Describes, in which side of UAV antenna was placed.
         *  @details If boolean evaluates to \c true, antenna is placed on
         *  the right side of UAV, otherwise, on the left.
         *  By default, this property returns \c false (left side).
         *  @par %antennaAlignment(), setAntennaAlignment(), antennaAlignmentChanged()
         */
        Q_PROPERTY(bool antennaAlignment READ antennaAlignment WRITE setAntennaAlignment NOTIFY antennaAlignmentChanged)

        /*! 
         *  @property angleCorrection
         *  @brief Debug property for adding or subtracting angle values from image metadata.
         *  @details Value describes, how many degrees will be added/subtracted from image
         *  metadata azimuth.
         *  By default, this property returns \c 0 (no correction).
         *  @note In current software version, it is probably better approach to use image editor
         *  for individual images. Setting this property to any values other than \c 0 can result 
         *  in strange image geopositioning behaviour.
         *  @par %angleCorrection(), setAngleCorrection(), angleCorrectionChanged()
         */
        Q_PROPERTY(float angleCorrection READ angleCorrection WRITE setAngleCorrection NOTIFY angleCorrectionChanged)

        /*! 
         *  @property useRadians
         *  @brief Compatibility setting for older firmware versions.
         *  @details If boolean evalueates to \c true, image metadata decoding process
         *  will expect radian values in azimuth, drift angle and div fields. VT45-firmware
         *  (target platform) currently behaves like that. User needs to manually uncheck 
         *  this boolean, if resulting images are poor cut and incorrectly aligned.
         *  By default, this property returns \c true.
         *  @par %useRadians(), setUseRadians(), useRadiansChanged()
         */
        Q_PROPERTY(bool useRadians READ useRadians WRITE setUseRadians NOTIFY useRadiansChanged)

        /*! 
         *  @property useDriftAngle
         *  @brief Compatibility setting for older firmware versions.
         *  @details If boolean evalueates to \c true, image metadata decoding process
         *  will use drift angle values in geopositioning, otherwise drift angle value
         *  will be ignored. User needs to manually uncheck this boolean,
         *  if resulting images are incorrectly aligned.
         *  By default, this property returns \c true.
         *  @par %useDriftAngle(), setUseDriftAngle(), useDriftAngleChanged()
         */
        Q_PROPERTY(bool useDriftAngle READ useDriftAngle WRITE setUseDriftAngle NOTIFY useDriftAngleChanged)

        /*! 
         *  @property thetaAzimuthCorrection
         *  @brief Debug property for subtracting diargam size angle value from image metadata.
         *  @details Value describes, how many degrees will be subtracted from image
         *  metadata theta-azimuth (div).
         *  By default, this property returns \c 5 (diargam angle is lower by 5 degrees).
         *  @par %thetaAzimuthCorrection(), setThetaAzimuthCorrection(), thetaAzimuthCorrectionChanged()
         */
        Q_PROPERTY(float thetaAzimuthCorrection READ thetaAzimuthCorrection WRITE setThetaAzimuthCorrection NOTIFY thetaAzimuthCorrectionChanged)

        /*! 
         *  @property overrideImageHeight
         *  @brief Debug property for overriding image \b ly parameter with real pixel height.
         *  @details If value evaluates to true, \b ly field of image metadata will be replaced
         *  with actual pixel height of this image. 
         *  By default, this property returns \c true (ly is overriden).
         *  @warning Currently, setting this boolean to false results in incorrect cutting of image.
         *  This can be changed in future firmware versions.
         *  @par %overrideImageHeight(), setOverrideImageHeight(), overrideImageHeightChanged()
         */
        Q_PROPERTY(bool overrideImageHeight READ overrideImageHeight WRITE setOverrideImageHeight NOTIFY overrideImageHeightChanged)

        /*! 
         *  @property cutImage
         *  @brief Debug property for disabling image software cutting.
         *  @details If value evaluates to false, no cutting will be applied to
         *  telescopic images. Otherwise, image will be cut according to it's 
         *  metadata.
         *  By default, this property returns \c true (cutting enabled).
         *  @par %cutImage(), setCutImage(), cutImageChanged()
         */
        Q_PROPERTY(bool cutImage READ cutImage WRITE setCutImage NOTIFY cutImageChanged)

        /*! 
         *  @property storedLatitude
         *  @brief Internal stored property for restoring map camera position between sessions.
         *  @par %storedLatitude(), setStoredLatitude(), storedLatitudeChanged()
         */
        Q_PROPERTY(double storedLatitude READ storedLatitude WRITE setStoredLatitude NOTIFY storedLatitudeChanged)

        /*! @property storedLongitude
         *  @brief Internal stored property for restoring map camera position between sessions.
         *  @par %storedLongitude(), setStoredLongitude(), storedLongitudeChanged()
         */
        Q_PROPERTY(double storedLongitude READ storedLongitude WRITE setStoredLongitude NOTIFY storedLongitudeChanged)

        /*! 
         *  @property storedZoomLevel
         *  @brief Internal stored property for restoring map camera position between sessions.
         *  @par %storedZoomLevel(), setStoredZoomLevel(), storedZoomLevelChanged()
         */
        Q_PROPERTY(double storedZoomLevel READ storedZoomLevel WRITE setStoredZoomLevel NOTIFY storedZoomLevelChanged)

        /*! 
         *  @property storedCatalogue
         *  @brief Internal stored property for restoring offline view folder between sessions.
         *  @par %storedCatalogue(), setStoredCatalogue(), storedCatalogueChanged()
         */
        Q_PROPERTY(QString storedCatalogue READ storedCatalogue WRITE setStoredCatalogue NOTIFY storedCatalogueChanged)

        /*! 
         *  @property theme
         *  @brief Selected application theme.
         *  @details Currently can evaluates to \c nord or \c contrast.
         *  In future rework of theme engine, it will fetch theme type from 
         *  theme .json file.
         *  By default, this property returns \c contrast.
         *  @par %theme(), setTheme(), themeChanged()
         */
        Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)

        public:
            //! @brief Возвращает указатель на статический экземпляр класса.
            static Config* get();

            virtual ~Config();

            /*! 
             *  @brief Синхронизирует настройки в ОЗУ с файлом на диске.
             *  @note Может быть вызванна из QML через мета-объектную систему.
             *  @warning Отладочная функция. Не вызывайте её, если не имеете четкого
             *  представления о своих действиях.
             */
            Q_INVOKABLE void sync();

            /*! 
             *  @brief Сохраняет настройки из памяти на диск.
             *  @details Записывает все текущие настройки из оперативной памяти
             *  приложения в .ini-файл на диске.
             *  @note Может быть вызванна из QML через мета-объектную систему.
             */
            Q_INVOKABLE void save();

            /*! 
             *  @brief Загружает в память приложения настройки из файла.
             *  @details Полностью заменяет все текущие настройки программы на
             *  настройки из файла на диске.
             *  @note Может быть вызванна из QML через мета-объектную систему.
             *  @sa revert()
             */
            Q_INVOKABLE void load();

            /*! 
             *  @brief Альтернативное имя для #load().
             *  @note Может быть вызванна из QML через мета-объектную систему.
             *  @sa load()
             */
            Q_INVOKABLE void revert();

            /*! 
             *  @brief Сбрасывает настройки в ОЗУ и в файле на диске к заводским.
             *  @details Полностью очищает все настройки в оперативной памяти приложения
             *  и в.ini-файле, затем заполняет их заводскими настройками из статической
             *  памяти приложения.
             *  @note Может быть вызванна из QML через мета-объектную систему.
             */
            Q_INVOKABLE void reset();

            /*! 
             *  @brief Возвращает текущую версию приложения.
             *  @details Версия приложения указывается при сборке проекта в системе CMake.
             *  @note Может быть вызванна из QML через мета-объектную систему.
             */
            Q_INVOKABLE QString projectVersion(); 

            [[nodiscard]] QString remoteIP() const; void setRemoteIP(const QString&);
            [[nodiscard]] QString localIP() const; void setLocalIP(const QString&);
            [[nodiscard]] QString telemetryPort() const; void setTelemetryPort(const QString&);
            [[nodiscard]] QString tcpLFSPort() const; void setTcpLFSPort(const QString&);
            [[nodiscard]] QString udpLFSPort() const; void setUdpLFSPort(const QString&);
            [[nodiscard]] QString execdPort() const; void setExecdPort(const QString&);
            [[nodiscard]] QString feedbackPort() const; void setFeedbackPort(const QString&);
            [[nodiscard]] bool proxyEnabled() const; void setProxyEnabled(bool);
            [[nodiscard]] bool antennaAlignment() const; void setAntennaAlignment(bool);
            [[nodiscard]] float angleCorrection() const; void setAngleCorrection(float);
            [[nodiscard]] bool useRadians() const; void setUseRadians(bool);
            [[nodiscard]] bool useDriftAngle() const; void setUseDriftAngle(bool);
            [[nodiscard]] float thetaAzimuthCorrection() const; void setThetaAzimuthCorrection(float);
            [[nodiscard]] double storedLatitude() const; void setStoredLatitude(double);
            [[nodiscard]] double storedLongitude() const; void setStoredLongitude(double);
            [[nodiscard]] double storedZoomLevel() const; void setStoredZoomLevel(double);
            [[nodiscard]] QString storedCatalogue() const; void setStoredCatalogue(const QString&);
            [[nodiscard]] float telemetryFrequency() const; void setTelemetryFrequency(float);
            [[nodiscard]] bool overrideImageHeight() const; void setOverrideImageHeight(bool);
            [[nodiscard]] bool cutImage() const; void setCutImage(bool);
            [[nodiscard]] QString tcpMarker() const; void setTcpMarker(const QString&);
            [[nodiscard]] QString theme() const; void setTheme(const QString&);
            [[nodiscard]] QString jetsonIP() const; void setJetsonIP(const QString&);
            [[nodiscard]] QString navIP() const; void setNavIP(const QString&);
            [[nodiscard]] QString utl1IP() const; void setUtl1IP(const QString&);
            [[nodiscard]] QString utl2IP() const; void setUtl2IP(const QString&);
            [[nodiscard]] QString telemetryRecvPort() const; void setTelemetryRecvPort(const QString&);

            signals:
                void remoteIPChanged();
                void localIPChanged();
                void telemetryPortChanged();
                void tcpLFSPortChanged();
                void udpLFSPortChanged();
                void execdPortChanged();
                void feedbackPortChanged();
                void proxyEnabledChanged();
                void antennaAlignmentChanged();
                void angleCorrectionChanged();
                void useRadiansChanged();
                void useDriftAngleChanged();
                void thetaAzimuthCorrectionChanged();
                void storedLatitudeChanged();
                void storedLongitudeChanged();
                void storedZoomLevelChanged();
                void storedCatalogueChanged();
                void telemetryFrequencyChanged();
                void overrideImageHeightChanged();
                void cutImageChanged();
                void tcpMarkerChanged();
                void themeChanged();
                void scheduleRestart();
                void jetsonIPChanged();
                void navIPChanged();
                void utl1IPChanged();
                void utl2IPChanged();
                void telemetryRecvPortChanged();

        private:
            explicit Config(QObject* parent = nullptr);
            Config(const Config &);
            Config &operator=(const Config &); 

        private:
            const QMap<QString, QVariant> defaults = {
                {"remoteIP", "127.0.0.1"},
                {"jetsonIP", "192.168.1.48"},
                {"navIP", "192.168.1.49"},
                {"utl1IP", "192.168.1.50"},
                {"utl2IP", "192.168.1.51"},
                {"localIP", "127.0.0.1"},
                {"telemetryPort", "9955"},
                {"telemetryRecvPort", "10337"},
                {"lfsPort", "10000"},
                {"stripPort", "48455"},
                {"execdPort", "9845"},
                {"feedbackPort", "9846"},
                {"telemetryFrequency", "0.1"},
                {"proxyEnabled", "false"},
                {"tcpMarker", "\0"},
                {"storedLatitude", "60"},
                {"storedLongitude", "30"},
                {"storedZoomLevel", "6"},
                {"storedCatalogue", "C:/"},
                {"antennaAlignment", "false"},
                {"angleCorrection", "0"},
                {"useRadians", "true"},
                {"useDriftAngle", "true"},
                {"thetaAzimuthCorrection", "5"},
                {"overrideImageHeight", "true"},
                {"cutImage", "true"},
                {"theme", "contrast"}
            };

            QSettings* ini;

            QString m_remoteIP;
            QString m_localIP;
            QString m_telemetryPort;
            QString m_tcpLFSPort;
            QString m_udpLFSPort;
            QString m_execdPort;
            QString m_feedbackPort;
            bool m_proxyEnabled;
            bool m_antennaAlignment;
            float m_angleCorrection;
            bool m_useRadians;
            bool m_useDriftAngle;
            float m_thetaAzimuthCorrection;
            double m_storedLatitude;
            double m_storedLongitude;
            double m_storedZoomLevel;
            QString m_storedCatalogue;
            float m_telemetryFrequency;
            bool m_overrideImageHeight;
            bool m_cutImage;
            QString m_tcpMarker;
            QString m_theme;
            QString m_jetsonIP;
            QString m_navIP;
            QString m_utl1IP;
            QString m_utl2IP;
            QString m_telemetryRecvPort;
    };
} // namespace Config;
