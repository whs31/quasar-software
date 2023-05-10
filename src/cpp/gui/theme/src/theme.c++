#include "theme_p.h++"
#include "config/paths.h++"

#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QCoreApplication>
#include <QtGui/QColor>
#include <memory>

using namespace GUI;

DECLARE_SINGLETON_IMPL(Theme)

Theme::Theme(QObject *parent)
    : QObject{parent}
    , d_ptr(new ThemePrivate(this)) {}

QString Theme::color(QString key)
{
    Q_D(Theme);
    return d->m_color.value(key);
}

QString Theme::colorText(const QString& text, const QString& theme_color_name)
{
    return ("<font color=\"" + this->color(theme_color_name) + "\">" + text + "</font>");
}

ThemePrivate::ThemePrivate(Theme* parent)
    : q_ptr(parent)
{
    findThemesInFolder();
}

void ThemePrivate::findThemesInFolder()
{
    Q_Q(Theme);
    QDir themesDirectory(QCoreApplication::applicationDirPath() + "/themes");
    themesDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    themesDirectory.setNameFilters(QStringList("*.json"));
    for(const QString &string : themesDirectory.entryList())
    {
        foundThemes.push_back(string);
    }
    if(themesDirectory.entryList().empty())
        qWarning() << "[THEME] Themes not found. Contact software provider.";
    else
        applyTheme(q->DEFAULT_THEME); // @TODO: replace it with config value
}

void ThemePrivate::applyTheme(QString theme)
{
    Q_Q(Theme);
    for(const QString &name : foundThemes)
    {
        if(name == theme)
        {
            qDebug().nospace() << "[THEME] Found default theme " << theme;

            QString _val;
            QFile _file(Config::Paths::themes() + "/" + name);
            _file.open(QIODevice::ReadOnly | QIODevice::Text);
            _val = _file.readAll();
            _file.close();
            QJsonDocument _doc = QJsonDocument::fromJson(_val.toUtf8());
            QJsonObject _object = _doc.object();
            m_color.clear();
            for(const QString &key : _object.keys())
                m_color.insert(key, _object.value(key).toString());

            qInfo() << "[THEME] Theme set.";
            break;
        }
    }
}
