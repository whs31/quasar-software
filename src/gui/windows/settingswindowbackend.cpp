#include "settingswindowbackend.h"

SettingsWindowBackend* SettingsWindowBackend::pointer = nullptr;
SettingsWindowBackend* SettingsWindowBackend::get(QObject* parent)
{
    if(pointer != NULL)
        return pointer;
    pointer = new SettingsWindowBackend(parent);
    return pointer;
}
SettingsWindowBackend::SettingsWindowBackend(QObject *parent)
    : QObject{parent}
{

}
