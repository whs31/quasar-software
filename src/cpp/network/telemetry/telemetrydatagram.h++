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
    struct __packed TelemetryDatagram
    {
        uint32_t marker; // const
        uint8_t version; // const
        double latitude; // rad
        double longitude; // rad
        double altitude; // m
        double velocity_course; // m s
        double velocity_east; // m s
        double velocity_north; // m s
        double velocity_vertical; // m s
        double pitch; // rad
        double roll; // rad
        double yaw; // rad
        double course; // rad
        uint64_t time; //
        bool valid; // unix time * 1000
        uint16_t crc16;

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
            dataStream << data.valid;
            dataStream << data.crc16;

            return dataStream;
        }
    };

    struct __packed TelemetryRequest
    {
        uint32_t marker = 0x55bb55bb;
        uint8_t init_flag; //0x00 ends stream, 0x01 begins stream
        uint16_t port;
        int32_t interval_ms;
        uint16_t crc16;

        friend QDataStream& operator << (QDataStream& dataStream, const TelemetryRequest& data)
        {
            dataStream << data.marker;
            dataStream << data.init_flag;
            dataStream << data.port;
            dataStream << data.interval_ms;
            dataStream << data.crc16;

            return dataStream;
        }
    };
} // namespace Network;
