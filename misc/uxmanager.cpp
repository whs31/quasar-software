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

    ColorList.append(QColor("#A2FF78"));            //    Success
    ColorList.append(QColor("#FF6D6A"));            //    Failure




    FormatList.append("<b>");                       //    Bold
    FormatList.append("<i>");                       //    Italic
    FormatList.append("<u>");                       //    UnderLine
    FormatList.append("<sup>");                     //    SuperScript
    FormatList.append("<sub>");                     //    SubScript




    fillStringList();
}

QColor UXManager::GetColor(Colors color)
{
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
