#ifndef UXMANAGER_H
#define UXMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QVector>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
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
    CriticalFailure,
    Info,
    Warning,
    ConsoleTextColor,
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
    static QColor GetColor(Colors color = Colors::NoColor, bool useBeforeClassInit = false);
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
    static void makeJSON();

    static QString jsonFilePath;
    static QJsonObject jsonobj;

signals:

};

#endif // UXMANAGER_H
