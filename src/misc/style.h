#ifndef STYLE_H
#define STYLE_H

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTimer>

#include "uxmanager.h"
#include "debug.h"

class Style : public QObject
{
    Q_OBJECT
public:
    static Style* initialize(QObject* parent = nullptr, bool testMode = false);

    static QString StyleText(QString string, Colors color = Colors::NoColor, Format format = Format::NoFormat, QString comlplicatedFormat = ""); //e.g. "b-i-u-sup-sub"
public slots:
    void updateQSS(void);
private:
    Style(QObject* parent = nullptr, bool TestMode = false);
    static Style* _instance;
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
