/**
 * \ingroup sdk_network
 * \class QuasarSDK::TelemetrySocket CTelemetrySocket.h <QuasarSDK/Networking/CTelemetrySocket.h>
 * \brief Класс для работы с сервисом \c navd2 на РЛС.
 * \details Предоставляет функционал запроса и приема датаграмм телеметрии
 * с РЛС. Автоматически парсит пакеты телеметрии и записывает значения в класс-хранилище
 * Telemetry.
 * \extends BaseUDPSocket
 */

#include "CTelemetrySocket.h"
#include <QtCore/QTimer>
#include <QtCore/QDataStream>
#include "FCommon.h"
#include "FCRC16.h"

constexpr static uint32_t MARKER = 0x55bb55bb;
constexpr static uint32_t RECV_MARKER_LITTLE = 0xaa55aa55;
constexpr static uint32_t RECV_MARKER_BIG = 0x55aa55aa;

namespace QuasarSDK
{
  /**
   * \brief Создает новый объект TelemetrySocket с указанным родителем и целью для вывода телеметрии.
   * \param parent - родитель класса в иерархии Qt.
   * \param output - указатель на класс Telemetry, в который будет отправляться результат парсинга датаграмм.
   */
  TelemetrySocket::TelemetrySocket(QObject* parent, Telemetry* output)
    : BaseUDPSocket(parent)
    , m_updateTimer(new QTimer(this))
    , output(output)
    , m_requestSocket(new QUdpSocket(this))
    , m_frequency(0.2)
    , request_port(0)
    , recv_port(0)
    , m_checkCRC(true)
  {
    this->setName("Telemetry");

    connect(m_updateTimer, &QTimer::timeout, this, &TelemetrySocket::requestTelemetry);
    connect(this, &TelemetrySocket::received, this, &TelemetrySocket::processTelemetry);
  }

  /**
   * \brief Начинает процедуру запроса и приема телеметрии с РЛС.
   * \note Несмотря на то, что класс TelemetrySocket - наследник BaseUDPSocket,
   * запуск и остановка должна производиться через вызов этой функции, а не функций start() и stop().
   * \param address - полный адрес (IPv4 и порт) для запроса телеметрии.
   * \param recv_address - полный адрес для приёма телеметрии.
   */
  void TelemetrySocket::start2way(const QString& address, const QString& recv_address) noexcept
  {
    if(not address.contains(":") or address.split(":").size() != 2)
    {
      qCritical() << "[TELEMETRY] Provided incorrect request address";
      return;
    }

    request_addr = address.split(":").first();
    request_port = address.split(":").last().toUInt();
    recv_port = recv_address.split(":").last().toUInt();

    try
    {
      this->start(recv_address);
    }
    catch(const std::invalid_argument& o)
    {
      qCritical() << "[TELEMETRY] Catched exception:" << o.what();
    }
    this->requestTelemetry();
    m_updateTimer->start((int) (30 * 1'000));
    qDebug().noquote() << "[TELEMETRY] Started reading at frequency of" << 1 / frequency() << "Hz";
  }

  /**
   * \brief Останавливает процедуру запроса и приема телеметрии.
   */
  void TelemetrySocket::stop2way() noexcept
  {
    this->stop();
    m_updateTimer->stop();
    qDebug() << "[TELEMETRY] Stopped reading";
  }

  /**
   * \property TelemetrySocket::frequency
   * \brief Предоставляет частоту запроса пакетов телеметрии.
   * \details По умолчанию равно 0.2 секунды. Свойство доступно и для чтения, и для записи.
   * Значение представлено интервалом в секундах между двумя
   * смежными входящими пакетами телеметрии.
   */
  float TelemetrySocket::frequency() const { return m_frequency; }
  void TelemetrySocket::setFrequency(float o) { m_frequency = o; }

  /**
   * \property TelemetrySocket::checkCRC
   * \brief Предоставляет состояние проверки контрольной суммы на входящих пакетах.
   * \details По умолчанию - \c true. Свойство доступно и для чтения, и для записи.
   * Если свойство равно \c true, то проверка будет производится, и,
   * в случае несовпадения, будет выброшено предупреждение в консоль.
   */
  bool TelemetrySocket::checkCRC() const { return m_checkCRC; }
  void TelemetrySocket::setCheckCRC(bool o) { m_checkCRC = o; }

  void TelemetrySocket::processTelemetry(QByteArray data)
  {
    uint32_t marker = *(uint32_t*) data.data();
    if(marker != RECV_MARKER_LITTLE)
    {
      qWarning() << "[TELEMETRY] Triggered first marker mismatch";
      return;
    }

    QDataStream stream(&data, ReadOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    Datagrams::TelemetryDatagram received;
    stream >> received;

    if(received.marker != RECV_MARKER_BIG)
    {
      qWarning() << "[TELEMETRY] Triggered second marker mismatch";
      return;
    }

    const float MS_TO_KMH = 3.6;

    received.latitude = Utils::rad2deg(received.latitude);
    received.longitude = Utils::rad2deg(received.longitude);
    received.velocity_course = received.velocity_course * MS_TO_KMH;
    received.velocity_east = received.velocity_east * MS_TO_KMH;
    received.velocity_north = received.velocity_north * MS_TO_KMH;
    received.velocity_vertical = received.velocity_vertical * MS_TO_KMH;
    received.pitch = Utils::rad2deg(received.pitch);
    received.roll = Utils::rad2deg(received.roll);
    received.yaw = Utils::rad2deg(received.yaw);
    received.course = received.yaw;
    received.satellites = received.satellites >> 1;

    output->setDatagram(received);

    uint16_t crc = checkCRC() ? Utils::crc16_ccitt((const char*) &received, sizeof(Datagrams::TelemetryDatagram) - sizeof(uint16_t))
                             : received.crc16;
    if(crc != received.crc16)
      qWarning().noquote().nospace() << "[TELSOCK] Checksum mismatch [" << crc << " : " << received.crc16 << "]";

    emit metrics("0x" + QString::number(received.marker, 16) + " " + QString::number(received.version) + " "
                       + QString::number(received.latitude, 'f', 7) + " " +
                       QString::number(received.longitude, 'f', 7) + " "
                       + QString::number(received.altitude, 'f', 2) + " " +
                       QString::number(received.velocity_course, 'f', 1) + " "
                       + QString::number(received.velocity_east, 'f', 1) + " " +
                       QString::number(received.velocity_north, 'f', 1) + " "
                       + QString::number(received.velocity_vertical, 'f', 1) + " " +
                       QString::number(received.pitch, 'f', 2) + " "
                       + QString::number(received.roll, 'f', 2) + " " + QString::number(received.yaw, 'f', 2) + " "
                       + QString::number(received.course, 'f', 2) + " " + QString::number(received.time) + " " +
                       QString::number(received.satellites)
                       + " 0x" + QString::number(received.crc16, 16), sizeof(received), false);
    emit ping();
  }

  void TelemetrySocket::requestTelemetry()
  {
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    Datagrams::TelemetryRequest request = { MARKER, 0x01, (uint16_t)(recv_port), (uint32_t)(this->frequency() * 1'000), 0 };
    uint16_t crc = Utils::crc16_ccitt((const char*)&request, sizeof(Datagrams::TelemetryRequest) - sizeof(uint16_t));
    request.crc16 = crc;

    stream << request;

    m_requestSocket->writeDatagram(buffer, QHostAddress(request_addr), request_port);
    emit metrics("0x" + QString::number(request.marker, 16) + " " + QString::number(request.init_flag) + " "
                       + QString::number(request.port) + " " + QString::number(request.interval_ms)
                       + " 0x" + QString::number(request.crc16, 16), sizeof(request), true);
  }
} // QuasarSDK