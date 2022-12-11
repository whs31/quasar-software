#include "markermanager.h"

MarkerManager::MarkerManager(QObject *parent)
    : QObject{parent}
{

}

void MarkerManager::newMarker(qreal latitude, qreal longitude)
{
    TMarker* marker = new TMarker();
    MarkerDialog markerDialog(latitude, longitude, *marker);
    if(markerDialog.exec() == QDialog::Accepted)
    {
        Debug::Log("[MARKER] Created new marker with name " + marker->name);
    } else {
        Debug::Log("[MARKER] Marker discarded");
        delete marker;
    }
}
