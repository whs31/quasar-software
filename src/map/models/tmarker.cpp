#include "tmarker.h"

TMarker::TMarker(QObject *parent)
    : QObject{parent}
{
}

void TMarker::update(void)
{
    switch (icon)
    {
    case MarkerIcon::SARImage:
        iconPath = "qrc:/map-resources/markers/radar.png";
        anchorX = 16;
        anchorY = 16;
        break;
    case MarkerIcon::Flag:
        iconPath = "qrc:/map-resources/markers/flag.png";
        anchorX = 16;
        anchorY = 16;
        break;
    case MarkerIcon::AutocaptureMark:
    {
        iconPath = "qrc:/map-resources/markers/autocapture.png";
        anchorX = 16;
        anchorY = 16;
        break;
    }
    default:
        iconPath = "qrc:/map-resources/markers/default.png";
        anchorX = 16;
        anchorY = 32;
        break;
    }
    scalable ? zoomLevel = 16 : zoomLevel = 0;
}
