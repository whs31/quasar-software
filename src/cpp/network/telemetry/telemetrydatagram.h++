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

#include "definitions.h++"
#include <cstdint>

namespace Network
{
    struct __packed TelemetryDatagram
    {
        uint32_t marker;
        uint8_t version;
        double latitude;
        double longitude;
        double altitude;
        double velocity_course;
        double velocity_east;
        double velocity_north;
        double velocity_vertical;
        double pitch;
        double roll;
        double yaw;
        double course;
        uint64_t time;
        bool valid;
        uint16_t crc16;
    };
} // namespace Network;
