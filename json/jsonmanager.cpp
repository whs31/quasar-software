#include "jsonmanager.h"

JSONManager::JSONManager()
    : QObject{parent()}
{

}

QJsonObject JSONManager::parseJSON(QString path)
{
    
}

void JSONManager::editJSONValue(QString path, QString key, QString value)
{
    QJsonDocument json;
    QFile jsonfile(path+".bak");
    if(QFile::exists(path))
    {
        jsonfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonContents = jsonfile.readAll();
        json = QJsonDocument::fromJson(jsonContents.toUtf8());
        jsonfile.close();
    } else {
        Debug::Log("!![JSON] .json file unavialable");
    }
    QJsonObject jsonobj = json.object();
    jsonobj.insert(key, value);
    QSaveFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(jsonobj).toJson());
    file.commit();
    Debug::Log("[JSON] Successfully edited JSON value");
}
