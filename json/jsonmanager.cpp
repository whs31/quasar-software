#include "jsonmanager.h"

JSONManager::JSONManager()
    : QObject{parent()}
{

}

QJsonObject JSONManager::parseJSON(QString path)
{
    QJsonDocument json;
    QFile jsonfile(path);
    if(QFile::exists(path))
    {
        jsonfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonContents = jsonfile.readAll();
        json = QJsonDocument::fromJson(jsonContents.toUtf8());
        jsonfile.close();
    } else {
        Debug::Log("!![JSON] .json file unavialable");
        QJsonObject object {
        };
        return object;
    }
    return json.object();
}
