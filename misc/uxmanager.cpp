#include "uxmanager.h"

QVector<QColor> UXManager::ColorList;
QStringList UXManager::ColorStringList;
QStringList UXManager::FormatList;
UXManager::UXManager(QObject *parent) : QObject{parent}
{
    ColorList.append(QColor("#E3D4AD"));            //    Main
    ColorList.append(QColor("#D3BC8D"));            //    MainShade900
    ColorList.append(QColor("#9e9075"));            //    MainShade800

    ColorList.append(QColor("#E59E6D"));            //    Accent

    ColorList.append(QColor("#b2ff59"));            //    Success
    ColorList.append(QColor("#ff5252"));            //    Failure
    ColorList.append(QColor("#c50e29"));            //    CriticalFailure
    ColorList.append(QColor("#40c4ff"));            //    Info
    ColorList.append(QColor("#ffd740"));            //    Warning

    ColorList.append(QColor("#e1f5fe"));            //    ConsoleTextColor




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
        return QColor("#ff5252" );
    } else if (color == Colors::Info && useBeforeClassInit)
    {
        return QColor("#40c4ff");
    } else if (color == Colors::Warning && useBeforeClassInit)
    {
        return QColor("#ffd740");
    } else if (color == Colors::CriticalFailure && useBeforeClassInit)
    {
        return QColor("#c50e29");
    } else if (color == Colors::ConsoleTextColor && useBeforeClassInit)
    {
        return QColor("#e1f5fe");
    }
    return ColorList[color];
}

short int UXManager::GetLengthOfColors()
{
    return Colors::__c__-1;
}

void UXManager::fillStringList()
{
    for(short int i = 0; i<UXManager::GetLengthOfColors(); i++)
    {
        UXManager::ColorStringList.append(ColorList[i].name());
    }
}

QStringList UXManager::GetColorList()
{
    return UXManager::ColorStringList;
}

QStringList UXManager::GetFormatList()
{
    return UXManager::FormatList;
}
