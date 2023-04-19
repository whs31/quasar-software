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
    ini->setValue("network/remoteIP", network().remoteIP);
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

Config::Config::Config(QObject *parent)
    : QObject{parent}
    , ini(new QSettings(Paths::config() + "/config.ini", QSettings::IniFormat, this))
{
    qDebug().noquote() << "[CONFIG] Storing config in" << ini->fileName();
    this->load();
}

Config::network_t Config::Config::network() const { return m_network; }
void Config::Config::setNetwork(const network_t& other) {
    m_network = other;
    emit networkChanged();
}

Config::map_t Config::Config::map() const { return m_map; }
void Config::Config::setMap(const map_t& other) {
    m_map = other;
    emit mapChanged();
}

Config::image_t Config::Config::image() const { return m_image; }
void Config::Config::setImage(const image_t& other) {
    m_image = other;
    emit imageChanged();
}
