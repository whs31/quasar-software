#include "fmousekeyhandler.h"
#include "qapplication.h"

FMouseKeyHandler::FMouseKeyHandler(QObject *parent)
    : QObject{parent}
{
    clipboard = QApplication::clipboard();
}

short int FMouseKeyHandler::mouseState(void) { return _mouseState; } 
void FMouseKeyHandler::setMouseState(short int state) { if(_mouseState == state) return; _mouseState = state; SMouseState::mouseState = state; emit mouseStateChanged(); }

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
    setMouseState(MouseState::Blank);

}