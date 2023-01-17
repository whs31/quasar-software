#include "recallhandler.h"

RecallHandler::RecallHandler(QObject *parent)
    : QObject{parent} {}

bool RecallHandler::clearTrack(void)
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

void RecallHandler::reconnect(void)     { LinkerQML::initialize()->reconnect(); if(RuntimeData::initialize()->getConnected()) { LinkerQML::panGPS(); } }
void RecallHandler::disconnect(void)    { LinkerQML::initialize()->disconnect(); }
void RecallHandler::changeDirectory(void)
{
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(nullptr,
                                                                tr("Выберите папку c выходными изображениями РЛС"),
                                                                QStandardPaths::displayName(QStandardPaths::HomeLocation));
    if(pathNotNullCheck != NULL) 
    { 
        SConfig::setHashValue("ViewPath", pathNotNullCheck); 
        }
}

bool RecallHandler::calibrateSeaLevel(void)
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

bool RecallHandler::clearMap(void)
{
    QMessageBox box;
    box.setWindowTitle("Очистка карты");
    box.setIcon(QMessageBox::Information);
    box.setText("Вы уверены, что хотите очистить карту от всех изображений?");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Cancel);
    int ret = box.exec();
    switch (ret)
    {
    case QMessageBox::Yes:
        return true;
        break;
    case QMessageBox::Cancel:
        return false;
        break;
    default:
        break;
    }
    return false;
}

bool RecallHandler::clearCache(void)
{
    QMessageBox box;
    box.setWindowTitle("Очистка кэша");
    box.setIcon(QMessageBox::Information);
    box.setText("Вы уверены, что хотите очистить кэш программы? Все полученные в ходе полёта изображения исчезнут из памяти компьютера.");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Cancel);
    int ret = box.exec();
    switch (ret)
    {
    case QMessageBox::Yes:
        return true;
        break;
    case QMessageBox::Cancel:
        return false;
        break;
    default:
        break;
    }
    return false;
}

void RecallHandler::toggleConsole(void)     { RuntimeData::initialize()->toggleConsole(); }
void RecallHandler::placeMarker(void)       { RuntimeData::mouseState = MouseState::MarkerPlacement; }
void RecallHandler::formSingleImage(void)   { RuntimeData::initialize()->formSingleImage(); }
void RecallHandler::formContinuously(void)  { RuntimeData::initialize()->formContinuous(); }
void RecallHandler::clearSARDisk(void)      
{ 
    QMessageBox box;
    box.setWindowTitle("Очистка хранилища РЛС");
    box.setIcon(QMessageBox::Warning);
    box.setText("Вы уверены, что хотите очистить хранилище изображений на РЛС? Это действие приведет к полному удалению всех снимков и голограмм. Его нельзя обратить!");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Cancel);
    int ret = box.exec();
    switch (ret)
    {
    case QMessageBox::Yes:
        RuntimeData::initialize()->clearSARDisk(); 
        break;
    case QMessageBox::Cancel:
        return;
        break;
    default:
        break;
    }
}