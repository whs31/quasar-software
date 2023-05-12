#include "image.h++"
#include <QtCore/QDebug>

namespace Map {

Image::Image()
{

}

QDebug& operator<< (QDebug& d, Image& image)
{
    d << "name: " << image.filename
      << "marker: " << image.header.meta_marker
      << "metasize: " << image.header.meta_size
      << "latitude: " << image.meta.latitude
      << "longitude: " << image.meta.longitude
      << "dx: " << image.meta.dx
      << "dy: " << image.meta.dy
      << "x0: " << image.meta.x0
      << "y0: " << image.meta.y0
      << "angle: " << image.meta.angle
      << "drift_angle: " << image.meta.drift_angle
      << "lx: " << image.meta.lx
      << "ly: " << image.meta.ly
      << "div: " << image.meta.div
      << "velocity: " << image.meta.velocity
      << "altitude: " << image.meta.altitude
      << "kr: " << image.meta.kr
      << "time_shift: " << image.meta.time_shift
      << "time_duration: " << image.meta.time_duration
      << "reserved_1: " << image.meta.reserved_1
      << "reserved_2: " << image.meta.reserved_2
      << "mode: " << image.meta.mode
      << "image_type: " << image.meta.image_type
      << "reserved_3: " << image.meta.reserved_3
      << "reserved_4: " << image.meta.reserved_4
      << "crc16: " << image.meta.crc16
      << "lod0: " << image.path.first
      << "lod1: " << image.path.second
      << "valid: " << image.valid;

    return d;
}
}
