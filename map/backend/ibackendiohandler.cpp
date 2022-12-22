#include "ibackendiohandler.h"

IBackendIOHandler::IBackendIOHandler(QObject *parent)
    : QObject{parent}
{
}

bool IBackendIOHandler::clearTrack(void)
{
    QMessageBox askForClearTrack;
    askForClearTrack.setWindowTitle("Очистка трека");
    askForClearTrack.setIcon(QMessageBox::Information);
    askForClearTrack.setText("Вы уверены, что хотите полностью очистить трек?");
    askForClearTrack.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    askForClearTrack.setDefaultButton(QMessageBox::Cancel);
    int ret = askForClearTrack.exec(); // не ставить шорт, иначе будет выход за границы буфера (енумы qt имеют неадекватные значения)
    switch (ret)
    {
    case QMessageBox::Yes:
        LinkerQML::clearRoute();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
    return true;
}
