#include "fmousekeyhandler.h"
#include "qapplication.h"

FMouseKeyHandler::FMouseKeyHandler(QObject *parent)
    : QObject{parent}
{
    clipboard = QApplication::clipboard();
}

void FMouseKeyHandler::copyCoordinates(qreal latitude, qreal longitude)
{
    RuntimeData::get()->statusPopupSet("Координаты скопированы в " +
                                        SText::colorText("буфер обмена!", ThemeManager::get()->getWarningLight()));
    RuntimeData::get()->statusPopupTriggerSet(true);
    clipboard->setText("Широта: " + QString::number(latitude) + ", Долгота: " + QString::number(longitude));
}

void FMouseKeyHandler::placeMarker(qreal latitude, qreal longitude)
{
    RuntimeData::get()->setMouseState(0);
    MarkerManager::get()->newMarker(latitude, longitude);
}
