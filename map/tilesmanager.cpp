#include "tilesmanager.h"

QString TilesManager::OSMConfigsPath = "";
QString TilesManager::TileServerPath = "";
TilesManager::TilesManager(QObject *parent)
    : QObject{parent}
{
    InitializeConfig(SConfig::TESTMODE);
    Debug::Log("?[TILESERVER] Path initialized");
}

void TilesManager::InitializeConfig(bool TestMode)
{
    TilesManager::OSMConfigsPath = QCoreApplication::applicationDirPath()+"/maptsc";
    TilesManager::TileServerPath = QCoreApplication::applicationDirPath()+"/tiles";

    QDir osmconfigs(TilesManager::OSMConfigsPath);
    if(!osmconfigs.exists()) { osmconfigs.mkpath(TilesManager::OSMConfigsPath); }
    if(!QFile::exists((TilesManager::OSMConfigsPath + "/street"+".bak")))
    {
        QFile::copy(":/osmconfigs/street", TilesManager::OSMConfigsPath + "/street"+".bak");
    }
    if(TestMode)
    {
        JSONManager::editJSONValue(TilesManager::OSMConfigsPath + "/street", "UrlTemplate", "http://a.tile.thunderforest.com/transport-dark/%z/%x/%y.png");
    }
    else
    {
        JSONManager::editJSONValue(TilesManager::OSMConfigsPath + "/street", "UrlTemplate", "file://"+TilesManager::TileServerPath+"/%z/%x/%y.png");
    }
}
