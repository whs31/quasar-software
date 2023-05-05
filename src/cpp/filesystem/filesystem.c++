#include "filesystem.h++"

Filesystem* Filesystem::instance = nullptr;
Filesystem* Filesystem::get(QObject* parent) {
    if(instance == nullptr)
        instance = new Filesystem(parent);
    return instance;
}

Filesystem::Filesystem(QObject *parent)
    : QObject{parent}
{

}

