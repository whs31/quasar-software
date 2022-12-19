#include "markermanager.h"

QVector<TMarker *> MarkerManager::markerList = {};
MarkerManager *MarkerManager::_instance = nullptr;
MarkerManager::MarkerManager(QObject *parent)
    : QObject{parent}
{}
MarkerManager *MarkerManager::initialize()
{
    if (_instance != NULL)
        return _instance;
    _instance = new MarkerManager();
    return _instance;
}

void MarkerManager::newMarker(qreal latitude, qreal longitude, bool quiet)
{
    TMarker* marker = new TMarker(initialize());
    if (!quiet)
    {
        MarkerDialog markerDialog(latitude, longitude, *marker);
        if (markerDialog.exec() == QDialog::Accepted)
        {
            // only if save = true
            // тут нужно чето придумать с индексами
            markerList.append(marker); // save me to xml file

            // вызываем этот метод перед передачей в qml
            // для обновления anchorPoint и iconPath после присвоения иконки в диалоговом окне
            marker->update();
            Debug::Log("[MARKER] Created new marker with name " + marker->name);
            LinkerQML::addModel(*marker);
        }
        else
        {
            Debug::Log("[MARKER] Marker discarded");
            delete marker;
        }
    } else {
        marker->name = "Положение РЛС";
        marker->color = QColor(255, 255, 255, 128);
        marker->icon = MarkerIcon::SARImage;
        marker->scalable = true;
        marker->save = false;
        marker->latitude = latitude;
        marker->longitude = longitude;
        marker->update();
        LinkerQML::addModel(*marker);
    }
}

void MarkerManager::removeMarker(qint32 index)
{
    markerList.remove(index);
    Debug::Log("[MARKER] Marker " + QString::number(index) + " removed from map. Vector l = " + QString::number(markerList.length()));
}