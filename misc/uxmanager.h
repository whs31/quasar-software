/* Gray:
 *  #9191a9
 *  #535771
 *  #23243b
 * White:
 *  #fafafc
 *  #D8d8d8
 *  #Bebebf
 * Main
 *  #4799ff
 *  #007cfe
 *  #0068d8
 * Error:
 *  #ff8181
 *  #ff5c5c
 *  #ff3737
 * Warning:
 *  #ffcd71
 *  #ffae33
 *  #ff8900
 * Reserved:
 *  #ffee6a
 *  #ffde35
 *  #ffcd00
 * Accent:
 *  #81eff4
 *  #00e1e7
 *  #00d0df
 * Purple
 *  #f1a7eb
 *  #c35cde
 *  #7600d2
 * Success:
 *  #00eca0
 *  #00db86
 *  #00c36b
*/

#ifndef UXMANAGER_H
#define UXMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QVector>
#include <QFile>
#include <QDir>
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
