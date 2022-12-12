#include "tmarker.h"

TMarker::TMarker(QObject *parent)
    : QObject{parent}
{

}

void TMarker::update(void)
{
    if(icon == MarkerIcon::SARImage)
    {
        iconPath = "qrc:/map-resources/markers/radar.png";
        anchorX = 16; anchorY = 16;
    } 
    else if(icon == MarkerIcon::Flag)
    {
        iconPath = "qrc:/map-resources/markers/flag.png";
        anchorX = 16; anchorY = 30;
    } 
    else {
        iconPath = "qrc:/map-resources/markers/default.png";
        anchorX = 16; anchorY = 32;
    }
    if(scalable)
    {
        zoomLevel = 16;
    } 
}
