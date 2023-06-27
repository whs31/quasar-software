#include "trackeventmodel.h"
#include <QtPositioning/QGeoCoordinate>

namespace Map
{

  TrackEventModel::TrackEventModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_maxEvents(5)
  {}

  int TrackEventModel::rowCount(const QModelIndex& parent) const
  {
    return m_data.size();
  }

  QVariant TrackEventModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return {};

    switch(role)
    {
      case ModelRoles::EventIndex: return index.row();
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
    if(m_data.size() == m_maxEvents)
    {
      beginRemoveRows(QModelIndex(), 0, 0);
      m_data.erase(m_data.begin());
      endRemoveRows();
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.emplace_back();
    endInsertRows();
  }

  void TrackEventModel::appendNewValue(const QGeoCoordinate& coord)
  {
    if(not coord.isValid())
      return;

    m_data.at(rowCount() - 1).m_path.push_back(QVariant::fromValue(coord));
    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, 0));
  }

  void TrackEventModel::setMaxEvents(int count)
  {
    m_maxEvents = count;
  }

} // Map