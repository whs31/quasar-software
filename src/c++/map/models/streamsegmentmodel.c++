//
// Created by whs31 on 20.07.23.
//

#include "streamsegmentmodel.h"
#include <QtCore/QDebug>

namespace Map
{
  StreamSegmentModel::StreamSegmentModel(QObject* parent)
    : QAbstractListModel(parent)
  {}

  QHash<int, QByteArray> StreamSegmentModel::roleNames() const
  {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[Index] = "index";                           // int
    roles[ChunkCoordinate] = "chunkCoordinate";       // QtPositioning.coordinate
    roles[ChunkAzimuth] = "chunkAzimuth";             // real
    roles[ChunkOffset] = "chunkOffset";               // Qt.point
    roles[ChunkSize] = "chunkSize";                   // Qt.size
    roles[ChunkZoomLevel] = "chunkZoomLevel";         // real
    roles[ChunkRatio] = "chunkRatio";                 // real
    roles[ChunkOpacity] = "chunkOpacity";             // real
    roles[ChunkVisibility] = "chunkVisibility";       // bool
    roles[Base64] = "base64";                         // string
    return roles;
  }

  int StreamSegmentModel::rowCount(const QModelIndex& parent) const { return m_storage.size(); }
  QVariant StreamSegmentModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return QVariant();

    switch(role)
    {
      case Index: return index.row();
      case ChunkCoordinate: return QVariant::fromValue(m_storage[index.row()].coordinate());
      case ChunkAzimuth: return QVariant::fromValue(m_storage[index.row()].azimuth());
      case ChunkOffset: return QVariant::fromValue(m_storage[index.row()].offset());
      case ChunkSize: return QVariant::fromValue(m_storage[index.row()].rectSize());
      case ChunkZoomLevel: return QVariant::fromValue(m_storage[index.row()].zoomLevel());
      case ChunkRatio: return QVariant::fromValue(m_storage[index.row()].ratio());
      case ChunkOpacity: return QVariant::fromValue(m_storage[index.row()].opacity());
      case ChunkVisibility: return QVariant::fromValue(m_storage[index.row()].isVisible());
      case Base64: return QVariant::fromValue(m_storage[index.row()].base64());

      default: return "Error reading from model";
    }
  }

  bool StreamSegmentModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if(data(index, role) != value)
    {
      switch(role)
      {
        case Index: return false;
        case ChunkCoordinate: m_storage[index.row()].setCoordinate(value.value<QGeoCoordinate>()); break;
        case ChunkAzimuth: m_storage[index.row()].setAzimuth(value.toFloat()); break;
        case ChunkOffset: m_storage[index.row()].setOffset(value.toPointF()); break;
        case ChunkSize: m_storage[index.row()].setRectSize(value.toSizeF()); break;
        case ChunkZoomLevel: return false;
        case ChunkRatio: m_storage[index.row()].setRatio(value.toFloat()); break;
        case ChunkOpacity: m_storage[index.row()].setOpacity(value.toFloat()); break;
        case ChunkVisibility: m_storage[index.row()].setVisible(value.toBool()); break;
        case Base64: return false;

        default: return false;
      }
      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void StreamSegmentModel::add(const QuasarSDK::Map::MapImageSegment& image_segment)
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_storage.push_back(image_segment);
    endInsertRows();

    qDebug() << "[SSM] Model received new segment. Now it contains" << rowCount() << "segments";
  }

  void StreamSegmentModel::remove(int index)
  {
    beginRemoveRows(QModelIndex(), index, index);
    m_storage.remove(index);
    endRemoveRows();

    qDebug() << "[SSM] Model lost an segment. Now it contains" << rowCount() << "segments";
  }

  void StreamSegmentModel::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_storage.clear();
    endRemoveRows();

    qDebug() << "[SSM] Model cleared";
  }
} // Map