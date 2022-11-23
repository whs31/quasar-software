#ifndef TAGS_H
#define TAGS_H

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
    Underline
};

class Tags
{
public:
    Tags();

    static QString StyleText(QString string, Colors color = Colors::NoColor, Format format = Format::NoFormat);

private:
};

#endif // TAGS_H
