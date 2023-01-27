#include "recallhandler.h"

RecallHandler::RecallHandler(QObject *parent)
    : QObject{parent} {}

void RecallHandler::reconnect(void)     { LinkerQML::initialize()->reconnect(); if(RuntimeData::get()->getConnected()) { LinkerQML::panGPS(); } }
void RecallHandler::disconnect(void)    { LinkerQML::initialize()->disconnect(); }
void RecallHandler::changeDirectory(void)
{
    QString pathNotNullCheck = QFileDialog::getExistingDirectory(nullptr,
                                                                tr("Выберите папку c выходными изображениями РЛС"),
                                                                QStandardPaths::displayName(QStandardPaths::DesktopLocation));
    if(pathNotNullCheck != NULL) {  SConfig::get()->setDefaultCatalogue(pathNotNullCheck); }
}
