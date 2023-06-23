/*!
 *  @file network.h
 *  @author Dmitry Ryazancev
 *  @date 22.06.2023
 *  @copyright Radar-MMS 2023
 */

#pragma once

#include <QtCore/QObject>
#include "network/netenums.h"
#include "telemetry/telemetry.h"
#include "execd/remotedata.h"

class QTimer;

//! @brief Пространство имен для работы с сетевыми подключениями к РЛС.
namespace Networking
{
  class TelemetrySocket;
  class ExecdSocket;
  class FeedbackSocket;
  class TCPSocket;
  class StripSocket;
  class Pinger;

  /*!
   *  @brief Класс-синглтон, отвечающий за связь с РЛС.
   *  @details Фабричный класс, регулирующий инстанциирование и запуск
   *  объектов сокетов TCP и UDP. Класс предоставляет функции для чтения
   *  и записи аргументов формирования, проверки доступности соединения и
   *  прямого управления сокетами. Также предоставляет указатели на хранилища
   *  данных (телеметрии и общих данных РЛС).
   *  Для отладочной информации класс предоставляет в виде сигналов метрики каждого дочернего сокета.
   *  @note Класс необходимо зарегистрировать как \c singletonInstance для доступа к нему из QML.
   */
  class Network : public QObject
  {
    Q_OBJECT

      /*!
       *  @property telemetry
       *  @brief Указатель на хранилище телеметрии.
       *  @details Свойство возвращает указатель на класс Telemetry.
       *  @par %telemetry(), setTelemetry(), telemetryChanged()
       *
       *  @property remoteData
       *  @brief Указатель на хранилище информации об РЛС.
       *  @details Свойство возвращает указатель на класс RemoteData.
       *  @par %remoteData(), setRemoteData(), remoteDataChanged()
       *
       *  @property networkDelay
       *  @brief Предоставляет текущую задержку в получении пакетов.
       *  @details Свойство хранит задержку между пакетами, которая
       *  учитывается в свойстве #connected. Задержка измеряется в
       *  секундах.
       *  @par %networkDelay(), setNetworkDelay(), networkDelayChanged()
       *
       *  @property tcpProgress
       *  @brief Предоставляет текущее состояние загрузчика TCP-IP.
       *  @details Свойство хранит текущий прогресс загрузки пакета
       *  данных по сокету TCP-IP. Диапазон значений - от 0 до 100.
       *  @par %tcpProgress(), setTcpProgress(), tcpProgressChanged()
       *
       *  @property connected
       *  @brief Предоставляет информацию о статусе соединения.
       *  @details Свойство хранит текущий статус соединения в виде \c int,
       *  где: 0 - полностью отключенно, 1 - частичное соединение и 2 - подключено
       *  к РЛС.
       *  @par %connected(), setConnected(), connectedChanged()
       *
       *  @property recording
       *  @brief Предоставляет состояние полосовой съемки.
       *  @details Если свойство равняется \c true, то в данный момент РЛС
       *  ведет съемку полосового изображения.
       *  @par %recording(), setRecording(), recordingChanged()
       */

      Q_PROPERTY(Telemetry* telemetry READ telemetry WRITE setTelemetry NOTIFY telemetryChanged)
      Q_PROPERTY(RemoteData* remoteData READ remoteData WRITE setRemoteData NOTIFY remoteDataChanged)
      Q_PROPERTY(float networkDelay READ networkDelay WRITE setNetworkDelay NOTIFY networkDelayChanged)
      Q_PROPERTY(float tcpProgress READ tcpProgress WRITE setTcpProgress NOTIFY tcpProgressChanged)
      Q_PROPERTY(int connected READ connected WRITE setConnected NOTIFY connectedChanged)
      Q_PROPERTY(bool recording READ recording WRITE setRecording NOTIFY recordingChanged)

    public:
      //! @brief Возвращает указатель на статический экземпляр класса.
      static Network* get();

      TelemetrySocket* telemetrySocket;       //!< Указатель на объект сокета телеметрии (сервис \b navd2 на РЛС).
      ExecdSocket* execdSocket;               //!< Указатель на объект сокета команд РЛС (сервис \b execd на РЛС).
      FeedbackSocket* feedbackSocket;         //!< Указатель на объект сокета обратной связи (поток \b stdout с РЛС).
      TCPSocket* tcpSocket;                   //!< Указатель на объект сокета TCP-IP (сервис \b fsend на РЛС).
      StripSocket* stripSocket;               //!< Указатель на объект сокета полосовых данных.

      /*!
       * @brief Производит попытку подключения к РЛС.
       * @details Функция запускает все дочерние сокеты с выбранными
       * параметрами и адресами.
       * @param telemetry_request_addr - IP-адрес для запросов телеметрии в формате \c 192.168.1.0:5555.
       * @param telemetry_recv_addr - IP-адрес для получения телеметрии.
       * @param telemetry_frequency - интервал в секундах между пакетами телеметрии.
       * @param execd_addr - IP-адрес для команд в сервис \b Execd на РЛС.
       * @param feedback_addr - IP-адрес для приема потока \b stdout с РЛС.
       * @param tcp_lfs_addr - IP-адрес для сервера TCP-IP.
       * @param udp_lfs_addr - IP-адрес для сокета полосовых изображений.
       * @note Может быть вызвана из QML через мета-объектную систему.
       */
      Q_INVOKABLE void begin(const QString& telemetry_request_addr, const QString& telemetry_recv_addr,
                             float telemetry_frequency,
                             const QString& execd_addr, const QString& feedback_addr,
                             const QString& tcp_lfs_addr, const QString& udp_lfs_addr) noexcept;

      /*!
       * @brief Производит отключение от РЛС.
       * @details Функция останавливает все дочерние сокеты и устанавливает
       * состояние подключения и задержку.
       * @note Может быть вызвана из QML через мета-объектную систему.
       */
      Q_INVOKABLE void stop() noexcept;

      /*!
       * @brief Выполняет встроенную команду сервиса \b execd.
       * @details Функция посылает в сервис \b execd выбранную встроенную
       * команду из списка команд (см. #Networking::Enums). Если команда
       * требует дополнительных аргументов, то они будут добавлены автоматически.
       * @param command - выбранная команда.
       * @note Может быть вызвана из QML через мета-объектную систему.
       */
      Q_INVOKABLE void executeCommand(const Networking::Enums::NetworkCommand command) noexcept;

      /*!
       * @brief Выполняет произвольную команду сервиса \b execd.
       * @details Функция конвертирует выбранную строку в команду
       * сервиса \b execd и отправляет ее на РЛС. Если команда валидна,
       * то она будет выполнена.
       * @param string - строка для выполнения.
       * @note Может быть вызвана из QML через мета-объектную систему.
       */
      Q_INVOKABLE void executeString(const QString& string) noexcept;

      /*!
       * @brief Возвращает аргумент из списка сервиса \b execd.
       * @details Функция возвращает константный аргумент по заданному ключу
       * и категории аргументов.
       * @param key - ключ (например, "--x0").
       * @param category - категория аргумента (см. #Enums::ArgumentCategory).
       * @note Может быть вызвана из QML через мета-объектную систему.
       */
      Q_INVOKABLE QString argument(const QString& key, Networking::Enums::ArgumentCategory category = Enums::Form) const noexcept;

      /*!
       * @brief Устанавливает аргумент из списка сервиса \b execd.
       * @details Функция устанавливает выбранный аргумент в приватный список
       * аргументов сервиса \b execd и выбранную категорию. Значение аргумента
       * будет автоматически приведено к корректному виду (\c int, \c float, \c string).
       * @param key - ключ (например, "--x0").
       * @param value - новое значение аргумента.
       * @param category - категория аргумента (см. #Enums::ArgumentCategory).
       * @note Может быть вызвана из QML через мета-объектную систему.
       */
      Q_INVOKABLE void setArgument(const QString& key, const QVariant& value, Networking::Enums::ArgumentCategory category = Enums::Form) noexcept;

      /*!
       * @brief Конвертирует IP-адрес и порт в общую строку.
       * @param ip - IP-адрес (например, "192.168.1.10").
       * @param port - порт в виде строки (например, "9955").
       * @return Строка с IP-адресом и портом (например, "192.168.1.10:9955").
       * @note Может быть вызвана из QML через мета-объектную систему.
       */
      Q_INVOKABLE static QString stringifyIP(const QString& ip, const QString& port) noexcept;

      [[nodiscard]] Telemetry* telemetry() const; void setTelemetry(Telemetry*);
      [[nodiscard]] RemoteData* remoteData() const; void setRemoteData(RemoteData*);
      [[nodiscard]] float networkDelay() const; void setNetworkDelay(float);
      [[nodiscard]] int connected() const; void setConnected(int);
      [[nodiscard]] float tcpProgress() const; void setTcpProgress(float);
      [[nodiscard]] bool recording() const; void setRecording(bool);

    signals:
      void telemetryChanged();
      void remoteDataChanged();
      void networkDelayChanged();
      void connectedChanged();
      void tcpProgressChanged();
      void recordingChanged();

      /*!
       *  @brief Метрики сокетов.
       *  @details Группа сигналов, предоставляющих отладочную информацию
       *  о данных, проходящих через сокет в обоих направлениях.
       *  @param data - данные, приведенные к виду строки.
       *  @param size_bytes - размер данных в байтах.
       *  @param out - направление движения данных: \c true означает выходной поток, \c false - входной.
       *  @{
       */
      void telemetrySocketMetrics(const QString& data, int size_bytes, bool out);
      void execdSocketMetrics(const QString& data, int size_bytes, bool out);
      void feedbackSocketMetrics(const QString& data, int size_bytes, bool out);
      void lfsSocketMetrics(const QString& msg, int size_bytes, bool out);
      void stripSocketMetrics(const QString msg, int size_bytes, bool out);
      //! @}

    private:
      explicit Network(QObject* parent = nullptr);
      Network(const Network&);
      Network& operator=(const Network&);

      void processFeedback(QByteArray) noexcept;

    private:
      QTimer* m_network_delay_timer;

      Telemetry* m_telemetry;
      RemoteData* m_remoteData;

      Pinger* m_de10ping;
      Pinger* m_jetsonping;
      Pinger* m_navping;
      Pinger* m_utl1ping;
      Pinger* m_utl2ping;

      float m_networkDelay;
      int m_connected;
      float m_tcpProgress;
      bool m_recording;
  };
} // namespace Network;
