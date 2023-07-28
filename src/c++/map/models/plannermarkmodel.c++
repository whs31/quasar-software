//
// Created by whs31 on 28.07.23.
//

#include "plannermarkmodel.h"
#include <QtCore/QDebug>
#include <QuasarSDK/API>

namespace Map
{
  PlannerMarkModel::PlannerMarkModel(QObject* parent)
      : QAbstractListModel(parent)
  {}

  QHash<int, QByteArray> PlannerMarkModel::roleNames() const
  {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[Index] = "index";
    roles[MarkerCoordinate] = "markerCoordinate";
    roles[MarkerName] = "markerName";
    roles[MarkerColor] = "markerColor";
    roles[MarkerID] = "markerID";
    roles[MarkerRadius] = "markerRadius";
    roles[MarkerAddress] = "markerAddress";
    roles[MarkerLifetime] = "markerLifetime";
    roles[MarkerCommand] = "markerCommand";
    return roles;
  }

  int PlannerMarkModel::rowCount(const QModelIndex& parent) const { return m_storage.size(); }
  QVariant PlannerMarkModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return QVariant();

    switch(role)
    {
      case Index: return index.row();
      case MarkerCoordinate: return QVariant::fromValue(m_storage[index.row()].coordinate());
      case MarkerName: return QVariant::fromValue(m_storage[index.row()].name());
      case MarkerColor: return QVariant::fromValue(m_storage[index.row()].color());
      case MarkerID: return QVariant::fromValue(m_storage[index.row()].id());
      case MarkerRadius: return QVariant::fromValue(m_storage[index.row()].radius());
      case MarkerAddress: return QVariant::fromValue(m_storage[index.row()].address());
      case MarkerLifetime: return QVariant::fromValue(m_storage[index.row()].lifetime());
      case MarkerCommand: return QVariant::fromValue(m_storage[index.row()].command());

      default: return "Error reading from model";
    }
  }

  bool PlannerMarkModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if(data(index, role) != value)
    {
      switch(role)
      {
        case Index: return false;
        case MarkerCoordinate: m_storage[index.row()].setCoordinate(value.value<QGeoCoordinate>()); break;
        case MarkerName: m_storage[index.row()].setName(value.toString()); break;
        case MarkerColor: m_storage[index.row()].setColor(value.toString()); break;
        case MarkerID: m_storage[index.row()].setID(value.toInt()); break;
        case MarkerRadius: m_storage[index.row()].setRadius(value.toInt()); break;
        case MarkerAddress: m_storage[index.row()].setAddress(value.toString()); break;
        case MarkerLifetime: m_storage[index.row()].setLifetime(value.toInt()); break;
        case MarkerCommand: m_storage[index.row()].setCommand(value.toString()); break;

        default: return false;
      }
      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void PlannerMarkModel::add(const PlannerMark& marker)
  {
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    m_storage.push_back(marker);
//    endInsertRows();

    qDebug() << "[PLANNER] Model received new planner mark. Now it contains" << rowCount() << "markers";
  }

  void PlannerMarkModel::add(double latitude, double longitude, const QString& name, const QColor& color, int radius,
                             const QString& address, int lifetime, const QString& command)
  {
    this->add(PlannerMark({latitude, longitude}, name, color, radius, address, command, lifetime));
  }

  void PlannerMarkModel::remove(int index)
  {
    if(index >= rowCount())
      return;
    beginRemoveRows(QModelIndex(), index, index);
    m_storage.remove(index);
    endRemoveRows();

    qDebug() << "[PLANNER] Model lost an marker. Now it contains" << rowCount() << "markers";
  }

  void PlannerMarkModel::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_storage.clear();
    endRemoveRows();

    qDebug() << "[PLANNER] Model cleared";
  }
} // Map
