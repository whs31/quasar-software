#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTimer>


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

class Style : public QObject
{
    Q_OBJECT
public:
    Style(bool TestMode = true, QObject* parent = nullptr);

    static QString StyleText(QString string, Colors color = Colors::NoColor, Format format = Format::NoFormat);
public slots:
    void updateQSS(void);
private:
    bool TestMode;
    QString defaultQSS = ":/stylesheet/stylesheet.qss";
    QString testQSS = "/home/user/quasar-ui/QuaSAR-UI/src/stylesheet/stylesheet.qss";
};

#endif // STYLE_H
