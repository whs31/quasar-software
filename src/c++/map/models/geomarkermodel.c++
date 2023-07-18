//
// Created by whs31 on 18.07.23.
//

#include "geomarkermodel.h"
#include <QtCore/QDebug>

namespace Map
{
  GeoMarkerModel::GeoMarkerModel(QObject* parent)
      : QAbstractListModel(parent)
  {}

  int GeoMarkerModel::rowCount(const QModelIndex& parent) const { return m_storage.size(); }
  QVariant GeoMarkerModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return QVariant();

    switch(role)
    {
      case Index: return index.row();
      case MarkerCoordinate: return QVariant::fromValue(m_storage[index.row()].coordinate());
      case MarkerName: return QVariant::fromValue(m_storage[index.row()].name());
      case MarkerColor: return QVariant::fromValue(m_storage[index.row()].color());
      case MarkerIcon: return QVariant::fromValue(m_storage[index.row()].icon());

      default: return "Error reading from model";
    }
  }

  bool GeoMarkerModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if(data(index, role) != value)
    {
      switch(role)
      {
        case Index: return false;
        case MarkerCoordinate: m_storage[index.row()].setCoordinate(value.value<QGeoCoordinate>()); break;
        case MarkerName: m_storage[index.row()].setName(value.toString()); break;
        case MarkerColor: m_storage[index.row()].setColor(value.toString()); break;
        case MarkerIcon: m_storage[index.row()].setIcon(value.toString()); break;

        default: return false;
      }
      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void GeoMarkerModel::add(const GeoMarker& marker)
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_storage.push_back(marker);
    endInsertRows();

    qDebug() << "[MARKER] Model received new marker. Now it contains" << rowCount() << "markers";
  }

  void GeoMarkerModel::remove(int index)
  {
    beginRemoveRows(QModelIndex(), index, index);
    m_storage.erase(m_storage.begin() + index);
    endRemoveRows();

    qDebug() << "[MARKER] Model lost an marker. Now it contains" << rowCount() << "markers";
  }

  void GeoMarkerModel::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_storage.clear();
    endRemoveRows();

    qDebug() << "[MARKER] Model cleared";
  }

  QHash<int, QByteArray> GeoMarkerModel::roleNames() const
  {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[Index] = "index";
    roles[MarkerCoordinate] = "markerCoordinate";
    roles[MarkerName] = "markerName";
    roles[MarkerColor] = "markerColor";
    roles[MarkerIcon] = "markerIcon";
    return roles;
  }
} // Map