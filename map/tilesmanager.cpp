#include "tilesmanager.h"

QString TilesManager::OSMConfigsPath = "";
QString TilesManager::TileServerPath = "";
TilesManager::TilesManager(QObject *parent)
    : QObject{parent}
{
    InitializeConfig();
    Debug::Log("?[TILESERVER] Path initialized");
}

void TilesManager::InitializeConfig()
{
    TilesManager::OSMConfigsPath = QCoreApplication::applicationDirPath()+"/maptsc";
    TilesManager::TileServerPath = QCoreApplication::applicationDirPath()+"/tiles";

    QDir osmconfigs(TilesManager::OSMConfigsPath);
    if(!osmconfigs.exists()) { osmconfigs.mkpath(TilesManager::OSMConfigsPath); }
    if(!QFile::exists((TilesManager::OSMConfigsPath + "/street"+".bak")))
    {
        QFile::copy(":/osmconfigs/street", TilesManager::OSMConfigsPath + "/street"+".bak");
    }
    if(SConfig::TESTMODE)
    {
        JSONManager::editJSONValue(TilesManager::OSMConfigsPath + "/street", "UrlTemplate", "http://a.tile.thunderforest.com/transport-dark/%z/%x/%y.png");
    }
    else
    {
        JSONManager::editJSONValue(TilesManager::OSMConfigsPath + "/street", "UrlTemplate", "file:///" + TilesManager::TileServerPath + "/%z/%x/%y.png");
    }
    Debug::Log("?[TILESERVER] Tiles directory: " "file:///" + TilesManager::TileServerPath + "/%z/%x/%y.png");
}
