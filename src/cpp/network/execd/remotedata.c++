#include "remotedata.h++"
//#include <QtCore/QDebug>

using namespace Network;

RemoteData::RemoteData(QObject *parent)
    : QObject{parent}
{

}

float RemoteData::storageSpace() const { return m_storageSpace; }
void RemoteData::setStorageSpace(float other) {
    if (qFuzzyCompare(m_storageSpace, other)) return;
    m_storageSpace = other;
    emit storageSpaceChanged();
}
