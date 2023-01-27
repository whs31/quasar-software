#include "markermanager.h"

QVector<Marker *> MarkerManager::markerList = {};
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
    Marker* marker = new Marker(initialize());
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
            if(marker->autocapture)
            {
                RuntimeData::get()->autocaptureMarks.append(QGeoCoordinate(marker->latitude, marker->longitude));
                RuntimeData::get()->setTotalAutocapCount(RuntimeData::get()->autocaptureMarks.length());
                Debug::Log("?[MARKER] Created new autocapture mark with name " + marker->name);
            } else {
                Debug::Log("[MARKER] Created new marker with name " + marker->name);
            }
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
    for(size_t i = 0; i < RuntimeData::get()->autocaptureMarks.length(); i++)
    {
        if(QGeoCoordinate(markerList[index]->latitude, markerList[index]->longitude).distanceTo(RuntimeData::get()->autocaptureMarks[i]) <= 10)
        {
            RuntimeData::get()->autocaptureMarks.remove(i);
            RuntimeData::get()->setTotalAutocapCount(RuntimeData::get()->autocaptureMarks.length());
        }
        break;
    }
    markerList.remove(index);
    Debug::Log("[MARKER] Marker " + QString::number(index) + " removed from map. Vector l = " + QString::number(markerList.length()));
}

void MarkerManager::removeMarkerFromCoordinates(QGeoCoordinate coordinate)
{
    for(size_t i = 0; i < RuntimeData::get()->autocaptureMarks.length(); i++)
    {
        if(coordinate.distanceTo(RuntimeData::get()->autocaptureMarks[i]) <= 10)
        {
            RuntimeData::get()->autocaptureMarks.remove(i);
            RuntimeData::get()->setTotalAutocapCount(RuntimeData::get()->autocaptureMarks.length());
            break;
        }
    }
    for(size_t j = 0; j < markerList.length(); j++)
    {
        if(coordinate.distanceTo(QGeoCoordinate(markerList[j]->latitude, markerList[j]->longitude)) <= 10)
        {
            LinkerQML::removeMarker(j);
            Debug::Log("[MARKER] Autocapture mark " + QString::number(j) + " removed from map.");
            break;
        }
    }
}
