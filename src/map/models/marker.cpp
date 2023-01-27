#include "marker.h"

Marker::Marker(QObject *parent)
    : QObject{parent}
{
}

void Marker::update(void)
{
    switch (icon)
    {
    case MarkerIcon::SARImage:
        iconPath = "qrc:/map/markers/radar.png";
        anchorX = 16;
        anchorY = 16;
        break;
    case MarkerIcon::Flag:
        iconPath = "qrc:/map/markers/flag.png";
        anchorX = 16;
        anchorY = 16;
        break;
    case MarkerIcon::AutocaptureMark:
    {
        iconPath = "qrc:/map/markers/autocapture.png";
        anchorX = 16;
        anchorY = 16;
        break;
    }
    default:
        iconPath = "qrc:/map/markers/default.png";
        anchorX = 16;
        anchorY = 32;
        break;
    }
    scalable ? zoomLevel = 16 : zoomLevel = 0;
}
