#include "marker.h"

Marker::Marker(QObject *parent)
    : QObject{parent}
{
}

void Marker::setIcon(MarkerIcon icon)
{
    switch (icon) {
    case Default:
        iconPath = "qrc:/map/markers/default.png";
        anchorX = 16;
        anchorY = 32;
        break;
    case MarkerIcon::Flag:
        iconPath = "qrc:/map/markers/flag.png";
        anchorX = 16;
        anchorY = 16;
        break;
    case MarkerIcon::Radar:
        iconPath = "qrc:/map/markers/radar.png";
        anchorX = 16;
        anchorY = 16;
        break;
    case MarkerIcon::Target:
        iconPath = "qrc:/map/markers/autocapture.png";
        anchorX = 16;
        anchorY = 16;
        break;
    default:
        iconPath = "qrc:/map/markers/default.png";
        anchorX = 16;
        anchorY = 32;
        break;
    }
}

void Marker::setColor(MarkerColor color)
{
    switch (color) {
    case Gray:
        colorValue = QColor("#B0BEC5");
        break;
    case Brown:
        colorValue = QColor("#BCAAA4");
        break;
    case Blue:
        colorValue = QColor("#90CAF9");
        break;
    case Green:
        colorValue = QColor("#81C784");
        break;
    case Teal:
        colorValue = QColor("#80CBC4");
        break;
    case Yellow:
        colorValue = QColor("#FFF176");
        break;
    case Orange:
        colorValue = QColor("#FF8A65");
        break;
    case Red:
        colorValue = QColor("#F06292");
        break;
    default:
        colorValue = QColor("#FF1212");
        break;
    }
}
