//
// Created by whs31 on 27.07.23.
//

#include "plannermark.h"
#include <QtNetwork/QHostAddress>
#include <QuasarSDK/PlannerDatagrams>

namespace Map
{
  int PlannerMark::m_shared_counter = 0;
  PlannerMark::PlannerMark()
    : GeoMarker()
    , m_id(-1)
    , m_radius(0)
    , m_address("127.0.0.1:25565")
    , m_lifetime_count(0)
    , m_command("$storage_status()")
  {}

  PlannerMark::PlannerMark(const QGeoCoordinate& coord, const QString& point_name, const QColor& point_color, int point_radius,
                           const QString& response_address, const QString& point_command, int lifetime)
    : GeoMarker(coord, point_name, point_color)
    , m_id(++m_shared_counter)
    , m_radius(point_radius)
    , m_address(response_address)
    , m_lifetime_count(lifetime)
    , m_command(point_command)
  {}

  int PlannerMark::id() const { return m_id; }
  void PlannerMark::setID(int x) { m_id = x; }

  int PlannerMark::radius() const { return m_radius; }
  void PlannerMark::setRadius(int x) { m_radius = x; }

  QString PlannerMark::address() const { return m_address; }
  uint32_t PlannerMark::iphex() const { return QHostAddress(address().split(':').first()).toIPv4Address(); }
  uint16_t PlannerMark::port() const { return address().split(':').last().toUInt(); }
  void PlannerMark::setAddress(const QString& x) { m_address = x; }

  int PlannerMark::lifetime() const { return m_lifetime_count; }
  void PlannerMark::setLifetime(int x) { m_lifetime_count = x; }

  QString PlannerMark::command() const { return m_command; }
  void PlannerMark::setCommand(const QString& x) { m_command = x; }

  QByteArray PlannerMark::appendDatagram() const
  {
    QByteArray ret;
    QDataStream stream(&ret, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    PlannerAppendDatagram datagram = { 0x55DD55DD, static_cast<uint16_t>(id()), static_cast<uint16_t>(radius()), iphex(),
                                       port(), QuasarSDK::Map::BasicMapObject::coordinate().latitude(),
                                       QuasarSDK::Map::BasicMapObject::coordinate().longitude(),
                                       static_cast<uint16_t>(lifetime()), static_cast<uint16_t>(command().length()),
                                       command().toUtf8() };
    stream << datagram;
    return ret;
  }

  QByteArray PlannerMark::removeDatagram() const
  {
    QByteArray ret;
    QDataStream stream(&ret, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    PlannerRemoveDatagram datagram = { 0x55DD55DD, static_cast<uint16_t>(id()), 0, 0, 0, 0, 0 };
    stream << datagram;
    return ret;
  }
} // Map