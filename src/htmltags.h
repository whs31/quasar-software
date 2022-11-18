#ifndef HTMLTAGS_H
#define HTMLTAGS_H

#include <QObject>

class HTMLTags : public QObject
{
    Q_OBJECT
public:
    explicit HTMLTags() {}
    virtual ~HTMLTags() {}

    //colors for text
    const QString HtmlColorMain = "<font color=\"#2ECC71\">";
    const QString HtmlColorMainFaded = "<font color=\"#27AE60\">";
    const QString HtmlColorMainAccent = "<font color=\"#F1C40F\">";
    const QString HtmlColorSuccess = "<font color=\"#CDDC39\">";
    const QString HtmlColorFailure = "<font color=\"#EF5350\">";
    const QString HtmlColorEnd = "</font>";
    //html tags
    const QString HtmlBold = "<b>";
    const QString HtmlBoldEnd = "</b>";

};

#endif // HTMLTAGS_H
