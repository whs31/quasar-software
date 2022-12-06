#ifndef STYLE_H
#define STYLE_H

#include "uxmanager.h"
#include "debug.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTimer>

class Style : public UXManager
{
    Q_OBJECT
public:
    Style(bool TestMode = false);

    static QString StyleText(QString string, Colors color = Colors::NoColor, Format format = Format::NoFormat, QString comlplicatedFormat = ""); //e.g. "b-i-u-sup-sub"
public slots:
    void updateQSS(void);
private:
    void initializeColors();
    void initializeFormats();
    static QString makeComplicatedFormat(QString text, QString complicatedFormat);

    bool TestMode;
    static QStringList colors;
    static QStringList formats;
    QString defaultQSS = ":/stylesheet/lightstyle.qss";
    QString testQSS = "/home/user/quasar-ui/QuaSAR-UI/src/stylesheet/stylesheet.qss";
};

#endif // STYLE_H
