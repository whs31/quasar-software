#include "markermanager.h"

MarkerManager *MarkerManager::_instance = nullptr;
MarkerManager::MarkerManager(QObject *parent)
    : QObject{parent}
{
    QObject::connect(MarkerWindowBackend::get(), SIGNAL(returnCodeChanged()), this, SLOT(dialogReturn()));
}
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
    MarkerWindowBackend::get()->setName(markerPointer->name);
    MarkerWindowBackend::get()->setLatitude(markerPointer->latitude);
    MarkerWindowBackend::get()->setLongitude(markerPointer->longitude);
    MarkerWindowBackend::get()->setRecord(markerPointer->save);
    MarkerWindowBackend::get()->setScreenAnchor(markerPointer->scalable);
    MarkerWindowBackend::get()->setColorCode(markerPointer->color);
    MarkerWindowBackend::get()->setIconCode(markerPointer->icon);
    MarkerWindowBackend::get()->show();

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

void MarkerManager::dialogReturn()
{
    if (MarkerWindowBackend::get()->getReturnCode() == 1)
    {
        markerPointer->name = MarkerWindowBackend::get()->getName();
        markerPointer->latitude = MarkerWindowBackend::get()->getLatitude();
        markerPointer->longitude = MarkerWindowBackend::get()->getLongitude();
        markerPointer->save = MarkerWindowBackend::get()->getRecord();
        markerPointer->setScalable(MarkerWindowBackend::get()->getScreenAnchor());
        markerPointer->setColor((MarkerColor)MarkerWindowBackend::get()->getColorCode());
        markerPointer->setIcon((MarkerIcon)MarkerWindowBackend::get()->getIconCode());

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
    else if(MarkerWindowBackend::get()->getReturnCode() == -1)
    {
        Debug::Log("[MARKER] Marker discarded");
        markerPointer = nullptr;
    }
}
