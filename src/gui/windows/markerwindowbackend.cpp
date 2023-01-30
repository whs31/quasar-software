#include "markerwindowbackend.h"

MarkerWindowBackend* MarkerWindowBackend::pointer = nullptr;
MarkerWindowBackend* MarkerWindowBackend::get(QObject* parent)
{
    if(pointer != NULL)
        return pointer;
    pointer = new MarkerWindowBackend(parent);
    return pointer;
}
MarkerWindowBackend::MarkerWindowBackend(QObject *parent)
    : WindowBackend{parent}
{
    show();
}
