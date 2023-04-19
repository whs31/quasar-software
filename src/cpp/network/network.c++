#include "network.h++"
#include <QtCore/QDebug>

Network::Network* Network::Network::instance = nullptr;
Network::Network* Network::Network::get(QObject *parent) {
    if(instance != nullptr)
        return instance;
    instance = new Network(parent);
    return instance;
}

Network::Network::Network(QObject *parent)
    : QObject{parent}
{
    qDebug() << "[NETWORK] Beginning network setup";
}

