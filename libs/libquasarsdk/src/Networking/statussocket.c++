//
// Created by whs31 on 30.07.23.
//

#include "statussocket.h"
#include <QtCore/QTimer>
#include "telemetry_datagrams.h"
#include "crc16.h"

constexpr static uint32_t STATUS_MARKER = 0x55FF55FF;
constexpr static uint32_t STATUS_RECEIVE_MARKER = 0xEE55EE55;

namespace QuasarSDK
{
  StatusSocket::StatusSocket(QObject* parent, QuasarSDK::RemoteData* remote_data_pointer)
    : BaseUDPSocket(parent)
    , m_updateTimer(new QTimer(this))
    , m_requestSocket(new QUdpSocket(this))
    , m_request_addr(QString())
    , m_request_port(0)
    , m_recv_port(0)
    , m_output(remote_data_pointer)
  {
    this->setName("Status");
    connect(this, &StatusSocket::received, this, &StatusSocket::process, Qt::DirectConnection);
    connect(m_updateTimer, &QTimer::timeout, this, &StatusSocket::request);
  }

  void StatusSocket::process(QByteArray data) noexcept
  {
    uint32_t marker = *(uint32_t*)data.data();
    if(marker != STATUS_RECEIVE_MARKER)
    {
      qWarning() << "[STATUS] Received unknown marker:" << Qt::hex << marker << Qt::dec;
      return;
    }

    QDataStream stream(&data, ReadOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    Datagrams::StatusDatagram received;
    stream >> received;

    //output->setDatagram(received);

    qCritical() << "0x" + QString::number(received.marker, 16) + " " + QString::number(received.voltage1) + " "
                   + QString::number(received.voltage2) + " " +
                   QString::number(received.switch_data) + " "
                   + QString::number(received.sar_data) + " " +
                   QString::number(received.r1) + " "
                   + QString::number(received.r2);
    emit metrics("0x" + QString::number(received.marker, 16) + " " + QString::number(received.voltage1) + " "
                 + QString::number(received.voltage2) + " " +
                 QString::number(received.switch_data) + " "
                 + QString::number(received.sar_data) + " " +
                 QString::number(received.r1) + " "
                 + QString::number(received.r2), sizeof(received), false);
  }

  void StatusSocket::request()
  {
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    Datagrams::TelemetryRequest request = { STATUS_MARKER, 0x01, (uint16_t)(m_recv_port), (uint32_t)(FREQUENCY), 0 };
    uint16_t crc = Utils::crc16_ccitt((const char*)&request, sizeof(Datagrams::TelemetryRequest) - sizeof(uint16_t));
    request.crc16 = crc;

    stream << request;

    m_requestSocket->writeDatagram(buffer, QHostAddress(m_request_addr), m_request_port);
    emit metrics("0x" + QString::number(request.marker, 16) + " " + QString::number(request.init_flag) + " "
                 + QString::number(request.port) + " " + QString::number(request.interval_ms)
                 + " 0x" + QString::number(request.crc16, 16), sizeof(request), true);
  }

  void StatusSocket::start(const QString& address)
  {
    try { BaseUDPSocket::start(address); }
    catch(const std::invalid_argument& o) { qCritical() << "[STATUS] Caught exception:" << o.what(); }
    
    m_recv_port = address.split(":").last().toUInt();
    this->request();
    m_updateTimer->start(30 * 1'000);
    qDebug().noquote() << "[STATUS] Started reading at frequency of" << 1000 / FREQUENCY << "Hz";
  }

  void StatusSocket::stop() noexcept
  {
    BaseUDPSocket::stop();
    m_updateTimer->stop();
    qDebug() << "[STATUS] Stopped reading";
  }

  void StatusSocket::setRequestAddress(const QString& addr)
  {
    m_request_addr = addr.split(":").first();
    m_request_port = addr.split(":").last().toUInt();
  }
} // QuasarSDK