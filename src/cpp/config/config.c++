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
    //ini->setValue("network/remoteIP", network().remoteIP);
}

void Config::Config::load()
{

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
    this->load();
}

namespace Config {

}
