#include "stripmodel.h"
#include <QtCore/QDebug>

namespace Map
{

  StripModel::StripModel(QObject* parent)
      : QAbstractListModel(parent)
  {}

  QHash<int, QByteArray> StripModel::roleNames() const
  {
    QHash<int, QByteArray> roles;
    roles[Index] = "index";
    roles[Filename] = "filename";
    roles[Latitude] = "latitude";
    roles[Longitude] = "longitude";
    roles[DX] = "dx";
    roles[Azimuth] = "azimuth";
    roles[LX] = "lx";
    roles[LY] = "ly";
    roles[OffsetX] = "offset_x";
    roles[OffsetY] = "offset_y";
    roles[Valid] = "valid";
    roles[LOD1FilePath] = "lod1";
    roles[LOD0FilePath] = "lod0";
    roles[Transparency] = "transparency";
    roles[Shown] = "shown";
    roles[MercatorZoomLevel] = "mercator_zoom_level";
    roles[MarkedForExport] = "marked_for_export";
    return roles;
  }

  int StripModel::rowCount(const QModelIndex& parent) const
  {
    return storage.size();
  }

  QVariant StripModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return {};

    switch(role)
    {
      case Index: return index.row();
      case Filename: return QVariant::fromValue(storage[index.row()].filename);
      case Latitude: return QVariant::fromValue(storage[index.row()].coordinate.latitude());
      case Longitude: return QVariant::fromValue(storage[index.row()].coordinate.longitude());
      case DX: return QVariant::fromValue(storage[index.row()].dx);
      case Azimuth: return QVariant::fromValue(storage[index.row()].azimuth);
      case LX: return QVariant::fromValue(storage[index.row()].lx);
      case LY: return QVariant::fromValue(storage[index.row()].ly);
      case OffsetX: return QVariant::fromValue(storage[index.row()].offset_x);
      case OffsetY: return QVariant::fromValue(storage[index.row()].offset_y);
      case Valid: return QVariant::fromValue(storage[index.row()].valid);
      case LOD1FilePath: return QVariant::fromValue(storage[index.row()].path.second);
      case LOD0FilePath: return QVariant::fromValue(storage[index.row()].path.first);
      case Transparency: return QVariant::fromValue(storage[index.row()].opacity);
      case Shown: return QVariant::fromValue(storage[index.row()].shown);
      case MercatorZoomLevel: return QVariant::fromValue(storage[index.row()].mercator_zoom_level);
      case MarkedForExport: return QVariant::fromValue(storage[index.row()].marked_for_export);

      default: return "Error reading from model";
    }
  }

  bool StripModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if(data(index, role) != value)
    {
      switch(role)
      {
        case Index: return false;
        case Filename: storage[index.row()].filename = value.toString(); break;
        case Latitude: storage[index.row()].coordinate.setLatitude(value.toDouble()); break;
        case Longitude: storage[index.row()].coordinate.setLongitude(value.toDouble()); break;
        case DX: storage[index.row()].dx = value.toFloat(); break;
        case Azimuth: storage[index.row()].azimuth = value.toFloat(); break;
        case LX: storage[index.row()].lx = value.toFloat(); break;
        case LY: storage[index.row()].ly = value.toFloat(); break;
        case OffsetX: storage[index.row()].offset_x = value.toFloat(); break;
        case OffsetY: storage[index.row()].offset_y = value.toFloat(); break;
        case Valid: storage[index.row()].valid = value.toBool(); break;
        case LOD1FilePath: storage[index.row()].path.second = value.toString(); break;
        case LOD0FilePath: storage[index.row()].path.first = value.toString(); break;
        case Transparency: storage[index.row()].opacity = value.toFloat(); break;
        case Shown: storage[index.row()].shown = value.toBool(); break;
        case MercatorZoomLevel: storage[index.row()].mercator_zoom_level = value.toDouble(); break;
        case MarkedForExport: storage[index.row()].marked_for_export = value.toBool();break;

        default: return false;
      }
      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void StripModel::add(const StripImage& image)
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    storage.push_back(image);
    endInsertRows();

    qDebug() << "[STRIP MODEL] Model received new image. Now it contains" << rowCount() << "images";
  }

  void StripModel::remove(int index)
  {
    beginRemoveRows(QModelIndex(), index, index);
    storage.remove(index);
    endRemoveRows();

    qDebug() << "[STRIP MODEL] Model lost an image. Now it contains" << rowCount() << "images";
  }

  void StripModel::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    storage.clear();
    endRemoveRows();

    qDebug() << "[STRIP MODEL] Model cleared";
  }

  bool StripModel::exportSelectedImages(const QString& target) noexcept
  {
    QList<QString> res;
    for(const auto& image: qAsConst(storage))
    {
      if(image.marked_for_export)
        res.push_back(image.path.first);
    }

    if(not res.empty())
    {
      qInfo() << "[STRIP MODEL] Marked" << res.size() << "images for export. Exporting...";
      emit markedForExport(res, target);
      return true;
    }
    else
    {
      qWarning() << "[STRIP MODEL] No images marked for export";
      return false;
    }
  }

  QVector<StripImage>* StripModel::direct() { return &storage; }

} // Map