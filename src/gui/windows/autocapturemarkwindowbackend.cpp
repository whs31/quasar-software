#include "autocapturemarkwindowbackend.h"

AutocaptureMarkWindowBackend* AutocaptureMarkWindowBackend::pointer = nullptr;
AutocaptureMarkWindowBackend* AutocaptureMarkWindowBackend::get(QObject* parent)
{
    if(pointer != NULL)
        return pointer;
    pointer = new AutocaptureMarkWindowBackend(parent);
    return pointer;
}
AutocaptureMarkWindowBackend::AutocaptureMarkWindowBackend(QObject *parent)
    : QObject{parent}
{

}
