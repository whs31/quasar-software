#include "disktools.h"

DiskTools* _instance = nullptr;
DiskTools::DiskTools(QObject *parent)
    : QObject{parent}
{}
DiskTools* DiskTools::initialize(QObject( parent))
{
    if(_instance != nullptr)
        return _instance;
    _instance = new DiskTools(parent);
    return _instance;
}
