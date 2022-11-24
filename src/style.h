#ifndef STYLE_H
#define STYLE_H

#include <QObject>

enum Colors : short int
{
    NoColor,
    Main,
    MainFaded,
    Accent,
    Success,
    Failure
};

enum Format : short int
{
    NoFormat,
    Bold,
    Italic,
    Underline,
    SuperScript
};

class Style
{
public:
    Style();

    static QString StyleText(QString string, Colors color = Colors::NoColor, Format format = Format::NoFormat);

private:
};

#endif // STYLE_H
