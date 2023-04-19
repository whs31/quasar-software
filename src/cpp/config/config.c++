#include "config.h++"

Config::Config::Config(QObject *parent)
    : QObject{parent}
{

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
