#include "config.h++"
#include "paths.h++"

#include <QtCore/QSettings>
#include <QtCore/QDebug>

Config::Config* Config::Config::instance = nullptr;
Config::Config *Config::Config::get(QObject* parent)
{
    if(instance != nullptr)
        return instance;
    instance = new Config(parent);
    return instance;
}

void Config::Config::save()
{
    qInfo() << "[CONFIG] Saving settings to file";
    for(const auto& key : map()->keys())
        ini->setValue(key, map()->value(key));
}

void Config::Config::load()
{
    qInfo() << "[CONFIG] Loading settings from file";
    for(const auto& key : ini->allKeys())
        map()->insert(key, ini->value(key));
}

void Config::Config::revert()
{

}

void Config::Config::reset()
{

}

QQmlPropertyMap* Config::Config::map()
{
    return &m_values;
}

void Config::Config::sync()
{
    emit m_values.valueChanged("asd", "asd");
}

Config::Config::Config(QObject *parent)
    : QObject{parent}
    , ini(new QSettings(Paths::config() + "/config.ini", QSettings::IniFormat, this))
{
    qDebug().noquote() << "[CONFIG] Storing config in" << ini->fileName();

    for(const auto &key : defaults.keys())
        map()->insert(key, defaults.value(key));
    if(ini->allKeys().empty())
        this->save();
    else
        this->load();
}

namespace Config {

}
