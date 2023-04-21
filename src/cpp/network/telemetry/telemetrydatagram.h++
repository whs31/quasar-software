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
    };
} // namespace Network;
