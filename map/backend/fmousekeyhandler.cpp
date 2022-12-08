#include "fmousekeyhandler.h"
#include "qapplication.h"

FMouseKeyHandler::FMouseKeyHandler(QObject *parent)
    : QObject{parent}
{
    clipboard = QApplication::clipboard();
}

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
