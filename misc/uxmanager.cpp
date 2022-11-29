#include "uxmanager.h"

QVector<QColor> UXManager::ColorList;
QStringList UXManager::ColorStringList;
QStringList UXManager::FormatList;
QString UXManager::jsonFilePath;
QJsonObject UXManager::jsonobj;
UXManager::UXManager(QObject *parent) : QObject{parent}
{
    QJsonDocument json;
    if(QFile::exists((QCoreApplication::applicationDirPath()+"/ux.json")))
    {
        QFile jsonFile(QCoreApplication::applicationDirPath()+"/ux.json");
        jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonContents = jsonFile.readAll();
        json = QJsonDocument::fromJson(jsonContents.toUtf8());
    } else {
        makeJSON();
        QFile jsonFile(QCoreApplication::applicationDirPath()+"/ux.json");
        jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString jsonContents = jsonFile.readAll();
        json = QJsonDocument::fromJson(jsonContents.toUtf8());
    }
    jsonobj = json.object();

    ColorList.append(QColor(jsonobj.value(QString("Main")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("MainShade900")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("MainShade800")).toString()));

    ColorList.append(QColor(jsonobj.value(QString("Accent")).toString()));

    ColorList.append(QColor(jsonobj.value(QString("Success")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Failure")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("CriticalFailure")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Info")).toString()));
    ColorList.append(QColor(jsonobj.value(QString("Warning")).toString()));

    ColorList.append(QColor(jsonobj.value(QString("ConsoleTextColor")).toString()));




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
    if(color == Colors::Failure && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Failure")).toString());
    } else if (color == Colors::Info && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Info")).toString());
    } else if (color == Colors::Warning && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("Warning")).toString());
    } else if (color == Colors::CriticalFailure && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("CriticalFailure")).toString());
    } else if (color == Colors::ConsoleTextColor && useBeforeClassInit)
    {
        return QColor(jsonobj.value(QString("ConsoleTextColor")).toString());
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
    for(short int i = 0; i<UXManager::GetLengthOfColors(); i++)
    {
        UXManager::ColorStringList.append(ColorList[i].name());
    }
}

void UXManager::makeJSON()
{
    QFile::copy(":/json-backup/ux.json", QCoreApplication::applicationDirPath()+"/ux.json");
}

