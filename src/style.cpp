#include "style.h"

Style::Style() {}
QString Style::StyleText(QString string, Colors color, Format format)
{
    const QStringList _colors = {
                                        "<font color=\"#2ECC71\">",
                                        "<font color=\"#27AE60\">",
                                        "<font color=\"#F1C40F\">",
                                        "<font color=\"#CDDC39\">",
                                        "<font color=\"#EF5350\">",
                                        "</font>"
    };
    const QStringList _styles = {
                                        "<b>",
                                        "<i>",
                                        "<u>",
                                        "<sup>",
                                        "</sup>",
                                        "</u>",
                                        "</i>",
                                        "</b>"
    };
    if(format != Format::NoFormat)
    {
        string.prepend(_styles[format-1]);
        string.append(_styles[_styles.length()-(format)]);
    }
    if(color != Colors::NoColor)
    {
        string.append(_colors.last());
        string.prepend(_colors[color-1]);
    }
    return string;
}
