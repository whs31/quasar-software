#include "trackeventmodel.h"

#include <QtPositioning/QGeoCoordinate>
#include <QtCore/QDebug>

using namespace Map;

TrackEventModel::TrackEventModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int TrackEventModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant TrackEventModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }
    switch (role) {
    case ModelRoles::EventIndex : return index.row();
    case ModelRoles::EventPath: return m_data.at(index.row()).m_path;
    default: return {};
    }
}

QHash<int, QByteArray> TrackEventModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ModelRoles::EventIndex] = "eventIndex";
    roles[ModelRoles::EventPath] = "eventPath";
    return roles;
}

void TrackEventModel::createNewEvent()
{
    if (m_data.size() == m_eventsCount) {
        beginRemoveRows(QModelIndex(), 0, 0);
        m_data.erase(m_data.begin());
        endRemoveRows();
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.emplace_back(EventData());
    endInsertRows();
}

void TrackEventModel::appendNewValue(const QGeoCoordinate &_coord)
{
    if(!_coord.isValid()){
        return;
    }
    m_data.at(rowCount() - 1).m_path.push_back(QVariant::fromValue(_coord));
    emit dataChanged(createIndex(0, 0),createIndex(rowCount() - 1, 0));
//    qDebug() <<m_data.at(rowCount() - 1).m_path;
}

void TrackEventModel::setEventsCount(const quint8 _eventsCount)
{
    m_eventsCount = _eventsCount;
}
