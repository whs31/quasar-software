#include "markermanager.h"

MarkerManager::MarkerManager(QObject *parent)
    : QObject{parent}
{

}

void MarkerManager::newMarker()
{
    TMarker marker;
    MarkerDialog markerDialog;
    if(markerDialog.exec() == QDialog::Accepted)
    {
        
    } else {
        // do nothing
    }
}
