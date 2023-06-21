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
         *  @brief Порт для запросов телеметрии.
         *  @details Этот порт используется для подключения к сервису \b navd2 на РЛС и
         *  отправки запроса на телеметрию. Порт должен использоваться в паре с #remoteIP.
         *  По умолчанию, свойство возвращает \c 9955.
         *  @par %telemetryPort(), setTelemetryPort(), telemetryPortChanged()
         */
        Q_PROPERTY(QString telemetryPort READ telemetryPort WRITE setTelemetryPort NOTIFY telemetryPortChanged)

        /*! 
         *  @property telemetryRecvPort
         *  @brief Порт для входящих пакетов телеметрии.
         *  @details Определяет, какой порт будет использоваться для связи с сервисом \b navd2
         *  на РЛС и получаться входящие пакеты телеметрии. Порт должен быть использован в паре с #localIP.
         *  По умолчанию, свойство возвращает \c 10337.
         *  @par %telemetryRecvPort(), setTelemetryRecvPort(), telemetryRecvPortChanged()
         */
        Q_PROPERTY(QString telemetryRecvPort READ telemetryRecvPort WRITE setTelemetryRecvPort NOTIFY telemetryRecvPortChanged)

        /*! 
         *  @property tcpLFSPort
         *  @brief Порт для сервера TCP-IP, используемого сервисом \b fsend на РЛС.
         *  @details TCP-IP сервер будет запущен на этом порте.
         *  Сервис \b fsend на РЛС будет подключаться к этому порту, когда РЛС будет готова
         *  отправить пакет данных.
         *  Порт должен быть использован в паре с #localIP.
         *  По умолчанию, свойство возвращает \c 10000.
         *  @par %tcpLFSPort(), setTcpLFSPort(), tcpLFSPortChanged()
         */
        Q_PROPERTY(QString tcpLFSPort READ tcpLFSPort WRITE setTcpLFSPort NOTIFY tcpLFSPortChanged)

        /*! 
         *  @property udpLFSPort
         *  @brief Порт для сервера UDP, используемого сервисом \b fsend на РЛС.
         *  @details Сервис \b fsend на РЛС будет подключаться к этому порту, когда РЛС будет готова
         *  отправить пакет данных. Этот порт в данный момент принимает только данные полосовых
         *  изображений. Порт должен быть использован в паре с #localIP.
         *  По умолчанию, свойство возвращает \c 48455.
         *  @warning Functionality of UDP LFS server is currently \b not implemented.
         *  @par %udpLFSPort(), setUdpLFSPort(), udpLFSPortChanged()
         */
        Q_PROPERTY(QString udpLFSPort READ udpLFSPort WRITE setUdpLFSPort NOTIFY udpLFSPortChanged)

        /*! 
         *  @property execdPort
         *  @brief Порт для сервиса \b execd на РЛС.
         *  @details Свойство определяет, в какой порт приложение будет отправлять команды для
         *  сервиса \b execd.
         *  Порт должен быть использован в паре с #remoteIP.
         *  По умолчанию, свойство возвращает \c 9845.
         *  @par %execdPort(), setExecdPort(), execdPortChanged()
         */
        Q_PROPERTY(QString execdPort READ execdPort WRITE setExecdPort NOTIFY execdPortChanged)

        /*! 
         *  @property feedbackPort
         *  @brief Порт для сервиса \b execd на РЛС.
         *  @details Свойство определяет, в какой порт будет перенаправляться вывод stdout/stderr
         *  с РЛС сервисом \b execd.
         *  Порт должен быть использован в паре с #localIP.
         *  По умолчанию, свойство возвращает \c 9846.
         *  @par %feedbackPort(), setFeedbackPort(), feedbackPortChanged()
         */
        Q_PROPERTY(QString feedbackPort READ feedbackPort WRITE setFeedbackPort NOTIFY feedbackPortChanged)

        /*! 
         *  @property telemetryFrequency
         *  @brief Интервал между пакетами телеметрии.
         *  @details Определяет, с каким интервалом (в секундах) сервис \b navd2 на РЛС будет
         *  отправлять пакеты с телеметрией на компьютер с приложением..
         *  По умолчанию, свойство возвращает \c 0.1 (сек).
         *  @par %telemetryFrequency(), setTelemetryFrequency(), telemetryFrequencyChanged()
         */
        Q_PROPERTY(float telemetryFrequency READ telemetryFrequency WRITE setTelemetryFrequency NOTIFY telemetryFrequencyChanged)

        /*! 
         *  @property proxyEnabled
         *  @brief Свойство совместимости, переопределяющее флаг \b --remote.
         *  @details Если свойство равняется \c true, то #localIP во флаге \b --remote
         *  будет заменен на #remoteIP. Свойство необходимо для совместимости с прокси
         *  НПК СПО.
         *  По умолчанию, свойство возвращает \c false.
         *  @warning Реализация удалена в версии приложения \b 2.0.
         *  @par %proxyEnabled(), setProxyEnabled(), proxyEnabledChanged()
         */
        Q_PROPERTY(bool proxyEnabled READ proxyEnabled WRITE setProxyEnabled NOTIFY proxyEnabledChanged)

        /*! 
         *  @property tcpMarker
         *  @brief Свойство совместимости со старыми версиями сервиса \b fsend.
         *  @details Определяет, какой символ будет использоваться для разделения
         *  пакета данных сокета TCP-IP data.
         *  В текущей реальности может равняться \c NULL или \c NEWLINE.
         *  По умолчанию, свойство возвращает \c \0 (NULL).
         *  @par %tcpMarker(), setTcpMarker(), tcpMarkerChanged()
         */
        Q_PROPERTY(QString tcpMarker READ tcpMarker WRITE setTcpMarker NOTIFY tcpMarkerChanged)

        /*! 
         *  @property antennaAlignment
         *  @brief Свойство, определяющее, на какой стороне борта установленна антенна.
         *  @details Если свойство равняется \c true, приложение будет считать, что
         *  антенна установлена на правой стороне борта.
         *  По умолчанию, свойство возвращает \c false (слева).
         *  @par %antennaAlignment(), setAntennaAlignment(), antennaAlignmentChanged()
         */
        Q_PROPERTY(bool antennaAlignment READ antennaAlignment WRITE setAntennaAlignment NOTIFY antennaAlignmentChanged)

        /*! 
         *  @property angleCorrection
         *  @brief Отладочное свойство для коррекции азимута РЛИ.
         *  @details Свойство описывает, на сколько градусов будет скорректирован азимут из
         *  метаданных радиолокационного изображения.
         *  По умолчанию, свойство возвращает \c 0 (коррекция отсутствует).
         *  @note В текущей версии приложения, лучшим подходом будет использовать индивидуальные
         *  коррекции из редактора изображений для каждого изображения. Установка значения этого
         *  свойства на любые значения, отличные от нуля, может привести к некорректной геопривязке.
         *  @par %angleCorrection(), setAngleCorrection(), angleCorrectionChanged()
         */
        Q_PROPERTY(float angleCorrection READ angleCorrection WRITE setAngleCorrection NOTIFY angleCorrectionChanged)

        /*! 
         *  @property useRadians
         *  @brief Свойство совместимости для старых версий прошивки.
         *  @details Если свойство равняется \c true, процесс декодирования метаданных изображения
         *  будет использовать значения азимута, угла сноса и угла расхождения диаграммы
         *  направленности в радианах, а не в градусах. Пользователь приложения должен вручную изменить значение
         *  этой настройки, если результат геопривязки некорректен.
         *  По умолчанию, свойство возвращает \c true.
         *  @par %useRadians(), setUseRadians(), useRadiansChanged()
         */
        Q_PROPERTY(bool useRadians READ useRadians WRITE setUseRadians NOTIFY useRadiansChanged)

        /*! 
         *  @property useDriftAngle
         *  @brief Свойство совместимости для старых версий прошивки.
         *  @details Если свойство равняется \c true, процесс декодирования метаданных изображения
         *  будет использовать значения угла сноса в геопривязке. В противном случае угол сноса
         *  будет считаться равным нулю. Пользователь приложения должен вручную изменить значение
         *  этой настройки, если результат геопривязки некорректен.
         *  По умолчанию, свойство возвращает \c true.
         *  @par %useDriftAngle(), setUseDriftAngle(), useDriftAngleChanged()
         */
        Q_PROPERTY(bool useDriftAngle READ useDriftAngle WRITE setUseDriftAngle NOTIFY useDriftAngleChanged)

        /*! 
         *  @property thetaAzimuthCorrection
         *  @brief Отладочное свойство для коррекции угла расхождения диаграммы РЛИ.
         *  @details Свойство определяет, на сколько градусов будет уменьшен угол
         *  расхождения диаграммы направленности из метаданных РЛИ при его обрезке.
         *  По умолчанию, свойство возвращает \c 5 (тета-азимут диаграммы уменьшен на 5 градусов).
         *  @par %thetaAzimuthCorrection(), setThetaAzimuthCorrection(), thetaAzimuthCorrectionChanged()
         */
        Q_PROPERTY(float thetaAzimuthCorrection READ thetaAzimuthCorrection WRITE setThetaAzimuthCorrection NOTIFY thetaAzimuthCorrectionChanged)

        /*! 
         *  @property overrideImageHeight
         *  @brief Отладочное свойство для коррекции пиксельной высоты РЛИ.
         *  @details Если свойство равняется \c true, поле --ly из метаданных будет заменено
         *  на реальную пиксельную высоту данного изображения.
         *  По умолчанию, свойство возвращает \c true (ly скорректировано).
         *  @warning В данный момент установка данного свойства на значение \c false приводит к
         *  некорректной обрезке изображения по диаграмме направленности. Это может измениться
         *  в будущих версиях прошивки РЛС.
         *  @par %overrideImageHeight(), setOverrideImageHeight(), overrideImageHeightChanged()
         */
        Q_PROPERTY(bool overrideImageHeight READ overrideImageHeight WRITE setOverrideImageHeight NOTIFY overrideImageHeightChanged)

        /*! 
         *  @property cutImage
         *  @brief Отладочное свойство, регулирующее обрезку РЛИ по диаграмме.
         *  @details Если свойство равняется \c true, к любым найденным и полученным
         *  РЛИ будет применена обрезка по диаграмме направленности из его метаданных
         *  (только для телескопических РЛИ).
         *  По умолчанию, свойство возвращает \c true (cutting enabled).
         *  @par %cutImage(), setCutImage(), cutImageChanged()
         */
        Q_PROPERTY(bool cutImage READ cutImage WRITE setCutImage NOTIFY cutImageChanged)

        /*! 
         *  @property storedLatitude
         *  @brief Приватное свойство для сохранения состояния карты между сессиями.ns.
         *  @par %storedLatitude(), setStoredLatitude(), storedLatitudeChanged()
         */
        Q_PROPERTY(double storedLatitude READ storedLatitude WRITE setStoredLatitude NOTIFY storedLatitudeChanged)

        /*! @property storedLongitude
         *  @brief Приватное свойство для сохранения состояния карты между сессиями.
         *  @par %storedLongitude(), setStoredLongitude(), storedLongitudeChanged()
         */
        Q_PROPERTY(double storedLongitude READ storedLongitude WRITE setStoredLongitude NOTIFY storedLongitudeChanged)

        /*! 
         *  @property storedZoomLevel
         *  @brief Приватное свойство для сохранения состояния карты между сессиями.
         *  @par %storedZoomLevel(), setStoredZoomLevel(), storedZoomLevelChanged()
         */
        Q_PROPERTY(double storedZoomLevel READ storedZoomLevel WRITE setStoredZoomLevel NOTIFY storedZoomLevelChanged)

        /*! 
         *  @property storedCatalogue
         *  @brief Приватное свойство, хранящее каталог с оффлайн-изображениями из прошлой сессии.
         *  @par %storedCatalogue(), setStoredCatalogue(), storedCatalogueChanged()
         */
        Q_PROPERTY(QString storedCatalogue READ storedCatalogue WRITE setStoredCatalogue NOTIFY storedCatalogueChanged)

        /*! 
         *  @property theme
         *  @brief Выбранная цветовая схема приложения.
         *  @details В данный момент может быть \c nord или \c contrast.
         *  В будущих обновлениях приложения будет добавлена поддержка чтения
         *  имени темы из названия .json-файла произвольной темы.
         *  По умолчанию, свойство возвращает \c contrast.
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
