#include "theme_p.h"
#include "config/paths.h"
#include "config/config.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QCoreApplication>
#include <QtGui/QColor>

using namespace GUI;

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
    this->findThemesInFolder();
    connect(Config::Config::get(), &Config::Config::themeChanged, this, [this](){
        this->findThemesInFolder();
    });
}

void ThemePrivate::findThemesInFolder()
{
    Q_Q(Theme);
    QDir themesDirectory(QCoreApplication::applicationDirPath() + "/themes");
    themesDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    themesDirectory.setNameFilters(QStringList("*.json"));
    for(const QString &string : themesDirectory.entryList())
        foundThemes.push_back(string);

    if(themesDirectory.entryList().empty())
        qWarning() << "[THEME] Themes not found. Contact software provider.";
    else
        applyTheme(CONFIG(theme));
}

void ThemePrivate::applyTheme(QString theme)
{
    Q_Q(Theme);
    for(const QString& name : foundThemes)
    {
        qDebug().nospace() << "[THEME] Found theme " << theme;

        QString val;
        QFile file(Config::Paths::themes() + "/" + name);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject object = doc.object();

        if(object.value("name") == theme)
        {
            m_color.clear();
            for(const QString& key : object.keys())
                m_color.insert(key, object.value(key).toString());

            qInfo() << "[THEME] Theme set.";
        }
    }
}
