#include "tags.h"

Tags::Tags() {}
QString Tags::StyleText(QString string, Colors color, Format format)
{
    const QString _colors[7] = { "", "<font color=\"#2ECC71\">", "<font color=\"#27AE60\">", "<font color=\"#F1C40F\">", "<font color=\"#CDDC39\">", "<font color=\"#EF5350\">", "</font>"};
    const QString _styles[8] = { "", "<b>", "<i>", "<u>", "/<u>", "</i>", "</b>", "" };
    if(format != Format::NoFormat)
    {
        string.prepend(_styles[format]);
        string.append(_styles[_styles->length()-(format+1)]);
    }
    if(color != Colors::NoColor)
    {
        string.append(_colors[_colors->length()]);
        string.prepend(_colors[color]);
    }
    return string;
}
