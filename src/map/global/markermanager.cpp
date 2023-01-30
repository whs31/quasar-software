#include "markermanager.h"

MarkerManager *MarkerManager::_instance = nullptr;
MarkerManager::MarkerManager(QObject *parent)
    : QObject{parent}
{}
MarkerManager *MarkerManager::get(QObject *parent)
{
    if (_instance != NULL)
        return _instance;
    _instance = new MarkerManager(parent);
    return _instance;
}

void MarkerManager::newMarker(qreal latitude, qreal longitude)
{
    markerPointer = new Marker(get());

    MarkerDialog markerDialog(latitude, longitude, *markerPointer);
    if (markerDialog.exec() == QDialog::Accepted)
    {
        dialogAccept();
    }
    else
    {
        dialogReject();
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

void MarkerManager::dialogAccept()
{
    // only if save = true
    // тут нужно чето придумать с индексами
    markerList.append(markerPointer); // save me to xml file

    if (markerPointer->autocapture)
    {
        RuntimeData::get()->autocaptureMarks.append(QGeoCoordinate(markerPointer->latitude, markerPointer->longitude));
        RuntimeData::get()->setTotalAutocapCount(RuntimeData::get()->autocaptureMarks.length());
        Debug::Log("?[MARKER] Created new autocapture mark with name " + markerPointer->name);
    }
    else
    {
        Debug::Log("[MARKER] Created new marker with name " + markerPointer->name);
    }
    LinkerQML::addModel(*markerPointer);
}

void MarkerManager::dialogReject()
{
    Debug::Log("[MARKER] Marker discarded");
    markerPointer = nullptr;
}
