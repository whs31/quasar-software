
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

#include "cachemanager.h"

enum Colors : short int
{
    NoColor,
	Info100,
	Info200,
	Info300,
	Accent100,
	Success100,
    Error200,
    Error100,
    Warning100,
    Text100,
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
    static UXManager* initialize(QObject *parent = nullptr, QString m_settingsPath = "only assign this value on first init");
    
    static QColor GetColor(Colors color = Colors::NoColor, bool useBeforeClassInit = false);
    static QString GetFormat(Format format = Format::NoFormat);
    static short int GetLengthOfColors();
    static QStringList GetColorList();
    static QStringList GetFormatList();
    

private:
    static UXManager* _instance;
    explicit UXManager(QObject *parent = nullptr);
    static QString settingsPath;
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
