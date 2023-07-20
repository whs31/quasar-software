//
// Created by whs31 on 18.07.23.
//

#include "geomarkermodel.h"
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonArray>
#include <QtCore/QFile>

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
    if(index >= rowCount())
      return;
    beginRemoveRows(QModelIndex(), index, index);
    m_storage.remove(index);
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

  void GeoMarkerModel::save(const QString& path, GeoMarkerModel::SaveFormat format) const noexcept
  {
    if(m_storage.empty())
    {
      qWarning() << "[MARKER] No markers to save";
      return;
    }

    QByteArray data;
    switch(format)
    {
      case JSON: data = toJSON(); break;
      case PlainText: data = toPlainText(); break;

      default: qCritical() << "[MARKER] Incorrect format of save file";
    }

    QFile file(path);
    if(not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      qCritical() << "[MARKER] Failed to save markers";
      return;
    }
    file.write(data);
    file.close();
    qDebug() << "$ [MARKER] Saved markers to" << path;
  }

  void GeoMarkerModel::load(const QString& path) noexcept
  {
    // not implemented
  }

  QByteArray GeoMarkerModel::toJSON() const noexcept
  {
    QJsonArray json_array;
    for(const auto& marker : m_storage)
    {
      QJsonObject marker_object;
      marker_object["latitude"] = marker.coordinate().latitude();
      marker_object["longitude"] = marker.coordinate().longitude();
      marker_object["name"] = marker.name();
      marker_object["color"] = marker.color().name();
      marker_object["icon_path"] = marker.icon();

      json_array.append(marker_object);
    }

    QJsonDocument document(json_array);
    return document.toJson();
  }

  QByteArray GeoMarkerModel::toPlainText() const noexcept
  {
    QByteArray ret;
    for(const auto& marker : m_storage)
    {
      ret.append("Маркер: " + marker.name().toUtf8() + "\n");
      ret.append("\t широта: " + QString::number(marker.coordinate().latitude(), 'f', 8).toUtf8() + "\n");
      ret.append("\t долгота: " + QString::number(marker.coordinate().longitude(), 'f', 8).toUtf8() + "\n");
      ret.append("\n");
    }
    return ret;
  }
} // Map
