#include "style.h"

Style::Style(bool TestMode, QObject* parent) : QObject(parent), TestMode(TestMode)
{
    if(!TestMode)
    {
        QFile qss(defaultQSS);
        if (!qss.exists())   {
            qWarning()<<("[QSS] Unable to set stylesheet, file not found\n");
        }
        else   {
            qss.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&qss);
            qApp->setStyleSheet(ts.readAll());                          //графика для Widgets
        }
    } else {
        QTimer* watcher = new QTimer();
        watcher->start(500);
        connect(watcher, SIGNAL(timeout()), this, SLOT(updateQSS()));
    }
}

void Style::updateQSS(void)
{
    QFile qss(testQSS);
    if (!qss.exists())   {
        qWarning()<<("[QSS] Unable to set test stylesheet, file not found\n");
    }
    else   {
        qss.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qss);
        qApp->setStyleSheet(ts.readAll());                              //графика для Widgets
    }
}

QString Style::StyleText(QString string, Colors color, Format format)
{
    const QStringList _colors = {
                                        "<font color=\"#E3D4AD\">",
                                        "<font color=\"#D3BC8D\">",
                                        "<font color=\"#9e9075\">",
                                        "<font color=\"#E59E6D\">",
                                        //"<font color=\"#844D99\">",
                                        "<font color=\"#A2FF78\">",
                                        "<font color=\"#FF6D6A\">",
                                        "</font>"
    };
    const QStringList _styles = {
                                        "<b>",
                                        "<i>",
                                        "<u>",
                                        "<sup>",
                                        "<sub>",
                                        "</sub>",
                                        "<sup><b>",
                                        "</b></sup>",
                                        "</sup>",
                                        "</u>",
                                        "</i>",
                                        "</b>"
    };
    if(format != Format::NoFormat)
    {
        string.prepend(_styles[format-1]);
        string.append(_styles[_styles.length()-(format)]);
    }
    if(color != Colors::NoColor)
    {
        string.append(_colors.last());
        string.prepend(_colors[color-1]);
    }
    return string;
}
