#include "fmousekeyhandler.h"
#include "qapplication.h"

FMouseKeyHandler::FMouseKeyHandler(QObject *parent)
    : QObject{parent}
{
    clipboard = QApplication::clipboard();
}

qint16 FMouseKeyHandler::mouseState(void) { _mouseState = RuntimeData::mouseState; return _mouseState; }
void FMouseKeyHandler::setMouseState(qint16 state) { if(_mouseState == state) return; _mouseState = state; RuntimeData::mouseState = state; emit mouseStateChanged(); }

void FMouseKeyHandler::copyCoordinates(qreal latitude, qreal longitude)
{
    RuntimeData::get()->setStatusPopup("Координаты скопированы в " +
                                        SText::colorText("буфер обмена!", ThemeManager::get()->getWarningLight()));
    RuntimeData::get()->setStatusPopupTrigger(true);
    clipboard->setText("Широта: " + QString::number(latitude) + ", Долгота: " + QString::number(longitude));
}

void FMouseKeyHandler::placeMarker(qreal latitude, qreal longitude)
{
    setMouseState(MouseState::Blank);
    MarkerManager::newMarker(latitude, longitude);
}
