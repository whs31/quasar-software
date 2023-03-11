#include "theme_p.hpp"
#include <QDebug>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QApplication>

Theme *Theme::_instance = nullptr;
Theme *Theme::get(QObject *parent) {
    if (_instance != nullptr) return _instance;
    _instance = new Theme(parent);
    return _instance;
}
Theme::Theme(QObject *parent)
    : QObject{parent}
    , d_ptr(new ThemePrivate(this)) {}

void Theme::setWindowDimension(float width, float height)
{
    Q_D(Theme);
    d->setWindowDimension(width, height);
}

QString Theme::color(QString key)
{
    Q_D(Theme);
    return d->m_color.value(key);
}
QPointF Theme::scalingFactor() const { return m_scalingFactor; }
void Theme::setScalingFactor(QPointF factor) {
    if (m_scalingFactor == factor) return;
    m_scalingFactor = factor;
    emit scalingFactorChanged();
}

void Theme::setQWidgetsStylesheet()
{
    QFile qss(":/stylesheet/lightstyle.qss");
    if (!qss.exists())
    {
        qCritical() << "[THEME] Unable to set test stylesheet, file not found";
    }
    else
    {
        qss.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qss);
        qApp->setStyleSheet(ts.readAll());
    }
}

/****************************************************************************************************************************************************************
███████████████████████████          🔒 PRIVATE IMPLEMENTATION 🔒          ███████████████████████████████──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────f
*****************************************************************************************************************************************************************/

ThemePrivate::ThemePrivate(Theme* parent)
    : q_ptr(parent)
{
    findThemesInFolder();
}

void ThemePrivate::setWindowDimension(float w, float h)
{
    Q_Q(Theme);
    QPointF _factor(w / q->BASE_RESOLUTION[0], h / q->BASE_RESOLUTION[1]);
    q->setScalingFactor(_factor);

    qDebug().nospace() << "[THEME] Using screen resolution of current monitor: " << w << "x" << h;
    qDebug().nospace() << "[THEME] Recalculated coefficients for GUI: " << q->scalingFactor().x() << ", " << q->scalingFactor().y();
}

void ThemePrivate::findThemesInFolder()
{
    Q_Q(Theme);
    QDir themesDirectory(QCoreApplication::applicationDirPath() + "/themes");
    themesDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    themesDirectory.setNameFilters(QStringList("*.json"));
    for(QString string : themesDirectory.entryList())
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
    for(QString name : foundThemes)
    {
        if(name == theme)
        {
            qDebug().nospace() << "[THEME] Found default theme " << theme;

            QString _val;
            QFile _file(QCoreApplication::applicationDirPath() + "/themes/" + name);
            _file.open(QIODevice::ReadOnly | QIODevice::Text);
            _val = _file.readAll();
            _file.close();
            QJsonDocument _doc = QJsonDocument::fromJson(_val.toUtf8());
            QJsonObject _object = _doc.object();
            m_color.clear();
            for(QString key : _object.keys())
            {
                m_color.insert(key, _object.value(key).toString());
            }

            qInfo() << "[THEME] Theme set.";

            break;
        }
    }
}
