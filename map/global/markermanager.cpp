#include "markermanager.h"

QVector<TMarker*> MarkerManager::markerList = { };
MarkerManager* MarkerManager::_instance = nullptr;
MarkerManager::MarkerManager(QObject *parent)
    : QObject{parent}
{}
MarkerManager* MarkerManager::initialize()
{
    if(_instance != NULL)
        return _instance;
    _instance = new MarkerManager();
    return _instance;
}

void MarkerManager::newMarker(qreal latitude, qreal longitude)
{
    TMarker* marker = new TMarker();
    MarkerDialog markerDialog(latitude, longitude, *marker);
    if(markerDialog.exec() == QDialog::Accepted)
    {
        //only if saveable = true
        //тут нужно чето придумать с индексами
        markerList.append(marker); //save me to xml file 
        
        //вызываем этот метод перед передачей в qml
        //для обновления anchorPoint и iconPath после присвоения иконки в диалоговом окне
        marker->update(); 
        Debug::Log("[MARKER] Created new marker with name " + marker->name);
        LinkerQML::addModel(*marker);
        

    } else {
        Debug::Log("[MARKER] Marker discarded");
        delete marker;
    }
}

void MarkerManager::removeMarker(qint32 index)
{
    qCritical()<<markerList.length();
    markerList.remove(index);
}