#include "remotedata.h"

using namespace Network;

RemoteData::RemoteData(QObject *parent)
    : QObject{parent}
    , m_storageSpace(0)
    , m_de10ping((int)PingStatus::Idle)
    , m_jetsonping((int)PingStatus::Idle)
    , m_navping((int)PingStatus::Idle)
    , m_utl1ping((int)PingStatus::Idle)
    , m_utl2ping((int)PingStatus::Idle)
{}

float RemoteData::storageSpace() const { return m_storageSpace; }
void RemoteData::setStorageSpace(float other) {
    if (qFuzzyCompare(m_storageSpace, other)) return;
    m_storageSpace = other;
    emit storageSpaceChanged();
}

int RemoteData::de10ping() const { return m_de10ping; }
void RemoteData::setDe10ping(int other) {
    if (m_de10ping == other)
        return;
    m_de10ping = other;
    emit de10pingChanged();
}

int RemoteData::jetsonping() const { return m_jetsonping; }
void RemoteData::setJetsonping(int other) {
    if (m_jetsonping == other)
        return;
    m_jetsonping = other;
    emit jetsonpingChanged();
}

int RemoteData::navping() const { return m_navping; }
void RemoteData::setNavping(int other) {
    if (m_navping == other)
        return;
    m_navping = other;
    emit navpingChanged();
}

int RemoteData::utl1ping() const { return m_utl1ping; }
void RemoteData::setUtl1ping(int other) {
    if (m_utl1ping == other)
        return;
    m_utl1ping = other;
    emit utl1pingChanged();
}

int RemoteData::utl2ping() const { return m_utl2ping; }
void RemoteData::setUtl2ping(int other) {
    if (m_utl2ping == other)
        return;
    m_utl2ping = other;
    emit utl2pingChanged();
}
