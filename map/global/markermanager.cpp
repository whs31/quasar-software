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
        //вызываем этот метод перед передачей в qml
        //для обновления anchorPoint и iconPath после присвоения иконки в диалоговом окне
        marker->update(); 
        Debug::Log("[MARKER] Created new marker with name " + marker->name);
        LinkerQML::addModel(*marker);
        //markerList.append(*marker); //save me to xml file //only if saveable = true

    } else {
        Debug::Log("[MARKER] Marker discarded");
        delete marker;
    }
}
