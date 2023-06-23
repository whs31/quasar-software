#include "marker.h"

Map::Marker::Marker(double latitude, double longitude, QString name, QString color, QString icon)
  : latitude(latitude)
  , longitude(longitude)
  , name(name)
  , color(color)
  , icon(icon)
{}
