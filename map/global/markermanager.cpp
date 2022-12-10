#include "markermanager.h"

MarkerManager::MarkerManager(QObject *parent)
    : QObject{parent}
{

}

void MarkerManager::newMarker(qreal latitude, qreal longitude)
{
    TMarker marker;
    MarkerDialog markerDialog(latitude, longitude, &marker);
    if(markerDialog.exec() == QDialog::Accepted)
    {
        qDebug()<<marker.name;
    } else {
        delete &marker;
    }
}
