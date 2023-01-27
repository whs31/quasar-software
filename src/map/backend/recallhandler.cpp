#include "recallhandler.h"

RecallHandler::RecallHandler(QObject *parent)
    : QObject{parent} {}

void RecallHandler::reconnect(void)     { LinkerQML::get()->reconnect(); if(RuntimeData::get()->getConnected()) { LinkerQML::panGPS(); } } //rework using signal handler
void RecallHandler::disconnect(void)    { LinkerQML::get()->disconnect(); }                                                                //rework using signal handler
void RecallHandler::changeDirectory(void)
{
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(nullptr,
                                                                tr("Выберите папку c выходными изображениями РЛС"),                        //rework using filepath QML type
                                                                QStandardPaths::displayName(QStandardPaths::DesktopLocation));
    if(pathNotNullCheck != NULL) {  SConfig::get()->setDefaultCatalogue(pathNotNullCheck); }
}
