#include "stext.h"

SText::SText(QObject *parent)
    : QObject{parent}
{

}

QString SText::localNumeralEnding(int numeral)
{
    if(numeral >= 5 && numeral <= 20 || numeral == 0)
        return "ий";
    for(int decimals = 0; decimals <= 9; decimals++)
    {
        if(numeral == decimals * 10 + 1) 
            return "ие";
        if(numeral >= decimals * 10 + 2 && numeral <= decimals * 10 + 4)
            return "ия";
        return "ий";
    }
    return "ий";
}

QString SText::colorText(QString text, QColor color)
{
    return "<font color=\"" + color.name() + "\">" + text + "</font>";
}
