#pragma once

/*
Telemetry Datagram in Rust

#[repr(C, packed)]
#[derive(Serialize)]
pub struct Datagram
{
    marker : u32,
    version : u8,
    lat : f64,
    lon : f64,
    ele : f64,
    velocity_course : f64,
    velocity_east : f64,
    velocity_north : f64,
    velocity_vertical : f64,
    pitch : f64,
    roll : f64,
    yaw : f64,
    course : f64,
    time : u64,
    valid : bool,
    crc : u16
}
*/

#include <cstdint>
#include <QtCore/QDataStream>

namespace Networking
{
  //! @brief Датаграма телеметрии от РЛС к наземке. Сериализована в Big Endian.
  struct TelemetryDatagram
  {
    uint32_t marker = 0x0;              //!< Маркер сообщения. Равен \c 0x55AA55AA.
    uint8_t version = 0x0;              //!< Версия протокола.
    double latitude = 0;                //!< Широта в градусах.
    double longitude = 0;               //!< Долгота в градусах.
    double altitude = 0;                //!< Высота в метрах.
    double velocity_course = 0;         //!< Путевая скорость в м/с.
    double velocity_east = 0;           //!< Скорость на восток в м/с.
    double velocity_north = 0;          //!< Скорость на север в м/с.
    double velocity_vertical = 0;       //!< Вертикальная скорость в м/с.
    double pitch = 0;                   //!< Тангаж БПЛА в радианах.
    double roll = 0;                    //!< Крен БПЛА в радианах.
    double yaw = 0;                     //!< Рыскание БПЛА в радианах.
    double course = 0;                  //!< Курс (азимут) БПЛА в радианах.
    quint64 time = 0;                   //!< Unix-time на борту.
    uint8_t satellites = 0;             //!< Текущее количество спутников навигации.
    uint16_t crc16 = 0x0;               //!< Контрольная сумма датаграмы \c CRC16_CCIT.

    friend QDataStream& operator << (QDataStream& dataStream, const TelemetryDatagram& data);
    friend QDataStream& operator >> (QDataStream& dataStream, TelemetryDatagram& data);
  };

  //! @brief Датаграма запроса телеметрии от наземки к РЛС. Сериализована в Big Endian.
  struct TelemetryRequest
  {
    uint32_t marker = 0x55bb55bb;       //!< Маркер сообщения. Равен \c 0x55BB55BB.
    uint8_t init_flag = 0x00;           //!< Тип команды. \c 0x00 завершает передачу, \c 0х01 - начинает.
    uint16_t port = 0;                  //!< Порт для обратной связи.
    uint32_t interval_ms = 0;           //!< Интервал передачи телеметрии в мс.
    uint16_t crc16 = 0x0;               //!< Контрольная сумма датаграмы \c CRC16_CCIT.

    friend QDataStream& operator << (QDataStream& dataStream, const TelemetryRequest& data);
    friend QDataStream& operator >> (QDataStream& dataStream, TelemetryRequest& data);
  };

  inline QDataStream &operator <<(QDataStream &dataStream, const TelemetryDatagram &data)
  {
    dataStream << data.marker;
    dataStream << data.version;
    dataStream << data.latitude;
    dataStream << data.longitude;
    dataStream << data.altitude;
    dataStream << data.velocity_course;
    dataStream << data.velocity_east;
    dataStream << data.velocity_north;
    dataStream << data.velocity_vertical;
    dataStream << data.pitch;
    dataStream << data.roll;
    dataStream << data.yaw;
    dataStream << data.course;
    dataStream << data.time;
    dataStream << data.satellites;
    dataStream << data.crc16;

    return dataStream;
  }

  inline QDataStream &operator >>(QDataStream &dataStream, TelemetryDatagram &data)
  {
    dataStream >> data.marker;
    dataStream >> data.version;
    dataStream >> data.latitude;
    dataStream >> data.longitude;
    dataStream >> data.altitude;
    dataStream >> data.velocity_course;
    dataStream >> data.velocity_east;
    dataStream >> data.velocity_north;
    dataStream >> data.velocity_vertical;
    dataStream >> data.pitch;
    dataStream >> data.roll;
    dataStream >> data.yaw;
    dataStream >> data.course;
    dataStream >> data.time;
    dataStream >> data.satellites;
    dataStream >> data.crc16;

    return dataStream;
  }

  inline QDataStream &operator <<(QDataStream &dataStream, const TelemetryRequest &data)
  {
    dataStream << data.marker;
    dataStream << data.init_flag;
    dataStream << data.port;
    dataStream << data.interval_ms;
    dataStream << data.crc16;

    return dataStream;
  }

  inline QDataStream &operator >>(QDataStream &dataStream, TelemetryRequest &data)
  {
    dataStream >> data.marker;
    dataStream >> data.init_flag;
    dataStream >> data.port;
    dataStream >> data.interval_ms;
    dataStream >> data.crc16;

    return dataStream;
  }
} // namespace Network;
