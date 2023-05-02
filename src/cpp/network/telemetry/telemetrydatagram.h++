#pragma once

/* Telemetry Datagram in Rust
 *
#[repr(C, packed)]
#[derive(Serialize)]
pub struct Datagram{
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

#include <definitions.h++>
#include <cstdint>
#include <QtCore/QDataStream>

namespace Network
{
    struct TelemetryDatagram
    {
        uint32_t marker = 0x0; // const
        uint8_t version = 0x0; // const
        double latitude = 0; // rad
        double longitude = 0; // rad
        double altitude = 0; // m
        double velocity_course = 0; // m s
        double velocity_east = 0; // m s
        double velocity_north = 0; // m s
        double velocity_vertical = 0; // m s
        double pitch = 0; // rad
        double roll = 0; // rad
        double yaw = 0; // rad
        double course = 0; // rad
        quint64 time = 0; //
        uint8_t satellites = 0;
        uint16_t crc16 = 0x0;

        friend QDataStream& operator << (QDataStream& dataStream, const TelemetryDatagram& data)
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

        friend QDataStream& operator >> (QDataStream& dataStream, TelemetryDatagram& data)
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
    };

    struct TelemetryRequest
    {
        uint32_t marker = 0x55bb55bb;
        uint8_t init_flag = 0x00; //0x00 ends stream, 0x01 begins stream
        uint16_t port = 0;
        uint32_t interval_ms = 0;
        uint16_t crc16 = 0x0;

        friend QDataStream& operator << (QDataStream& dataStream, const TelemetryRequest& data)
        {
            dataStream << data.marker;
            dataStream << data.init_flag;
            dataStream << data.port;
            dataStream << data.interval_ms;
            dataStream << data.crc16;

            return dataStream;
        }

        friend QDataStream& operator >> (QDataStream& dataStream, TelemetryRequest& data)
        {
            dataStream >> data.marker;
            dataStream >> data.init_flag;
            dataStream >> data.port;
            dataStream >> data.interval_ms;
            dataStream >> data.crc16;

            return dataStream;
        }
    };
} // namespace Network;
