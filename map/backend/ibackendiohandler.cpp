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

void IBackendIOHandler::reconnect(void)
{
    LinkerQML::initialize()->reconnect();
}

void IBackendIOHandler::disconnect(void)
{
    LinkerQML::initialize()->disconnect();
}

void IBackendIOHandler::changeDirectory(void)
{
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(nullptr,
                                                                tr("Выберите папку c выходными изображениями РЛС"),
                                                                QStandardPaths::displayName(QStandardPaths::HomeLocation));
    if(pathNotNullCheck != NULL) 
    { 
        SConfig::setHashValue("ViewPath", pathNotNullCheck); 
        }
}

bool IBackendIOHandler::calibrateSeaLevel(void)
{
    QMessageBox askForClearTrack;
    askForClearTrack.setWindowTitle("Калибровка высоты");
    askForClearTrack.setIcon(QMessageBox::Information);
    askForClearTrack.setText("Калибровка высоты должна проводиться на земле. Убедитесь, что беспилотник находится на стартовой площадке.");
    askForClearTrack.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    askForClearTrack.setDefaultButton(QMessageBox::Cancel);
    int ret = askForClearTrack.exec(); // не ставить шорт, иначе будет выход за границы буфера (енумы qt имеют неадекватные значения)
    switch (ret)
    {
    case QMessageBox::Yes:
        RuntimeData::initialize()->setSeaLevel(RuntimeData::initialize()->getElevation());
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
    return true;
}