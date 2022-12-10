#include "style.h"

Style* Style::_instance = nullptr;
QStringList Style::colors;
QStringList Style::formats;
Style::Style(bool TestMode) : TestMode(TestMode)
{
    initializeColors();
    initializeFormats();
    if(!TestMode)
    {
        QFile qss(defaultQSS);
        if (!qss.exists())   {
            Debug::Log("!![QSS] Unable to set stylesheet, file not found\n");
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

Style* Style::initialize(bool testMode)
{
    if(_instance != NULL)
        return _instance;
    _instance = new Style(testMode);
    return _instance;
}

void Style::updateQSS(void)
{
    QFile qss(testQSS);
    if (!qss.exists())   {
        Debug::Log("!![QSS] Unable to set test stylesheet, file not found\n");
    }
    else   {
        qss.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qss);
        qApp->setStyleSheet(ts.readAll());                              //графика для Widgets
    }
}

void Style::initializeColors()
{
    colors = UXManager::GetColorList();
    for (int c = 0; c < colors.length(); c++)
    {
        colors[c].prepend("<font color=\"");
        colors[c].append("\">");
    }
    colors.append("</font>");
}

void Style::initializeFormats()
{
    formats = UXManager::GetFormatList();
    QStringList _f = formats;
    for(int k = 0; k < (_f.size()/2); k++) _f.swapItemsAt(k,formats.size()-(1+k));
    for(int f = 0; f < _f.length(); f++)
    {
        _f[f].remove(0, 1);
        _f[f].prepend("</");
    }
    formats = formats + _f;
}

QString Style::StyleText(QString string, Colors color, Format format, QString complicatedFormat)
{
    if(format != Format::NoFormat)
    {
        if(format != Format::Complicated)
        {
            string.prepend(formats[format-1]);
            string.append(formats[formats.length()-(format)]);
        } else {
            string = Style::makeComplicatedFormat(string, complicatedFormat);
        }
    }
    if(color != Colors::NoColor)
    {
        string.append(colors.last());
        string.prepend(colors[color-1]);
    }
    return string;
}

QString Style::makeComplicatedFormat(QString text, QString complicatedFormat)
{
    QStringList cf = complicatedFormat.split("-");
    for (QString s : cf)
    {
        if(s == "b")
        {
            text.prepend("<b>");
            text.append("</b>");
        } else if(s == "i")
        {
            text.prepend("<i>");
            text.append("</i>");
        } else if(s == "u")
        {
            text.prepend("<u>");
            text.append("</u>");
        } else if(s == "sup")
        {
            text.prepend("<sup>");
            text.append("</sup>");
        } else if(s == "sub")
        {
            text.prepend("<sub>");
            text.append("</sub>");
        }
    }
    return text;
}
