#include "uxmanager.h"

QVector<QColor> UXManager::ColorList;
QStringList UXManager::ColorStringList;
QStringList UXManager::FormatList;
QString UXManager::jsonFilePath;
QJsonObject UXManager::jsonobj;
UXManager* UXManager::_instance = nullptr;
QString UXManager::settingsPath = "nullstr";

UXManager *UXManager::initialize(QObject *parent, QString m_settingsPath)
{
    if (_instance != NULL)
        return _instance;
    settingsPath = m_settingsPath;
    _instance = new UXManager(parent);
    return _instance;
}

UXManager::UXManager(QObject *parent) : QObject{parent}
{
    QJsonDocument json;
    if(QFile::exists((settingsPath+"/ux.json")))
    {
        QFile jsonFile(settingsPath+"/ux.json");
        jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonContents = jsonFile.readAll();
        json = QJsonDocument::fromJson(jsonContents.toUtf8());
    } else {
        makeJSON();
        QFile jsonFile(settingsPath+"/ux.json");
        jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonContents = jsonFile.readAll();
        json = QJsonDocument::fromJson(jsonContents.toUtf8());
    }
    jsonobj = json.object();

    ColorList.append(QColor(jsonobj.value(QString("Info100")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Info200")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Info300")).toString()));

    ColorList.append(QColor(jsonobj.value(QString("Accent100")).toString()));

    ColorList.append(QColor(jsonobj.value(QString("Success100")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Error200")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Error100")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Warning100")).toString()));

    ColorList.append(QColor(jsonobj.value(QString("Text100")).toString()));




    FormatList.append("<b>");                       //    Bold
    FormatList.append("<i>");                       //    Italic
    FormatList.append("<u>");                       //    UnderLine
    FormatList.append("<sup>");                     //    SuperScript
    FormatList.append("<sub>");                     //    SubScript

    fillStringList();
}

QColor UXManager::GetColor(Colors color, bool useBeforeClassInit)
{
    //prevent crash
    if(color == Colors::Error200 && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Error200")).toString());
    } else if (color == Colors::Info200 && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Info200")).toString());
    } else if (color == Colors::Warning100 && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Warning100")).toString());
    } else if (color == Colors::Error100 && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Error100")).toString());
    } else if (color == Colors::Text100 && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Text100")).toString());
    }
    return ColorList[color];
}

short int UXManager::GetLengthOfColors()
{
    return Colors::__c__-1;
}

QStringList UXManager::GetColorList()
{
    return UXManager::ColorStringList;
}

QStringList UXManager::GetFormatList()
{
    return UXManager::FormatList;
}

void UXManager::fillStringList()
{
	for (short int i = 0; i < UXManager::GetLengthOfColors(); i++)
		UXManager::ColorStringList.append(ColorList[i].name());
}

void UXManager::makeJSON()
{
    QFile::copy(":/json-backup/ux.json", settingsPath + "/ux.json");
}

