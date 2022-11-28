#ifndef UXMANAGER_H
#define UXMANAGER_H

#include <QObject>
#include <QVector>
#include "qcolor.h"

enum Colors : short int
{
    NoColor,
    Main,
    MainShade900,
    MainShade800,
    Accent,
    Success,
    Failure,
    __c__
};

enum Format : short int
{
    NoFormat,
    Bold,
    Italic,
    Underline,
    SuperScript,
    SubScript,
    Complicated
};

class UXManager : public QObject
{
    Q_OBJECT
public:
    explicit UXManager(QObject *parent = nullptr);
    static QColor GetColor(Colors color = Colors::NoColor);
    static QString GetFormat(Format format = Format::NoFormat);

protected:
    static short int GetLengthOfColors();
    static QStringList GetColorList();
    static QStringList GetFormatList();

private:
    static QVector<QColor> ColorList;
    static QStringList ColorStringList;
    static QStringList FormatList;
    static void fillStringList();


signals:

};

#endif // UXMANAGER_H
