#include "fmousekeyhandler.h"
#include "qapplication.h"

FMouseKeyHandler::FMouseKeyHandler(QObject *parent)
    : QObject{parent}
{
    clipboard = QApplication::clipboard();
}

qint16 FMouseKeyHandler::mouseState(void) { _mouseState = SMouseState::mouseState; return _mouseState; qWarning()<<_mouseState; }
void FMouseKeyHandler::setMouseState(qint16 state) { if(_mouseState == state) return; _mouseState = state; SMouseState::mouseState = state; emit mouseStateChanged(); qWarning()<<_mouseState; }

void FMouseKeyHandler::copyCoordinates(qreal latitude, qreal longitude)
{
    QMessageBox notifyAboutCopy;
    notifyAboutCopy.setWindowTitle("Координаты скопированы");
    notifyAboutCopy.setIcon(QMessageBox::Information);
    notifyAboutCopy.setText("Координаты скопированы в буфер обмена!");
    notifyAboutCopy.setStandardButtons(QMessageBox::Yes);
    notifyAboutCopy.setDefaultButton(QMessageBox::Yes);
    notifyAboutCopy.exec();
    clipboard->setText("широта: " + QString::number(latitude) + ", долгота: " + QString::number(longitude));
}

void FMouseKeyHandler::placeMarker(qreal latitude, qreal longitude)
{
    qCritical()<<"fmousekeyhandler received";
    setMouseState(MouseState::Blank);
    MarkerManager::newMarker();
}
