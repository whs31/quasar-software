#include "imagemodel.h"
#include <QtCore/QDebug>

namespace Map
{

  ImageModel::ImageModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_totalCount(0)
  {}

  QHash<int, QByteArray> ImageModel::roleNames() const
  {
    QHash<int, QByteArray> roles;
    roles[Index] = "index";
    roles[Filename] = "filename";
    roles[Latitude] = "latitude";
    roles[Longitude] = "longitude";
    roles[DX] = "dx";
    roles[DY] = "dy";
    roles[X0] = "x0";
    roles[Y0] = "y0";
    roles[Angle] = "angle";
    roles[DriftAngle] = "drift_angle";
    roles[LX] = "lx";
    roles[LY] = "ly";
    roles[Div] = "div";
    roles[Velocity] = "velocity";
    roles[Altitude] = "altitude";
    roles[KR] = "kr";
    roles[TimeShift] = "time_shift";
    roles[TimeDuration] = "time_duration";
    roles[Mode] = "mode";
    roles[ImageType] = "image_type";
    roles[Crc16] = "crc16";
    roles[Valid] = "valid";
    roles[LOD1FilePath] = "lod1";
    roles[LOD0FilePath] = "lod0";
    roles[Transparency] = "transparency";
    roles[Shown] = "shown";
    roles[MercatorZoomLevel] = "mercator_zoom_level";
    roles[MarkedForExport] = "marked_for_export";
    roles[Neural] = "neural_data";
    return roles;
  }

  int ImageModel::rowCount(const QModelIndex& parent) const
  {
    return storage.size();
  }

  QVariant ImageModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return QVariant();

    switch(role)
    {
      case Index: return index.row();
      case Filename: return QVariant::fromValue(storage[index.row()].filename);
      case Latitude: return QVariant::fromValue(storage[index.row()].meta.latitude);
      case Longitude: return QVariant::fromValue(storage[index.row()].meta.longitude);
      case DX: return QVariant::fromValue(storage[index.row()].meta.dx);
      case DY: return QVariant::fromValue(storage[index.row()].meta.dy);
      case X0: return QVariant::fromValue(storage[index.row()].meta.x0);
      case Y0: return QVariant::fromValue(storage[index.row()].meta.y0);
      case Angle: return QVariant::fromValue(storage[index.row()].meta.angle);
      case DriftAngle: return QVariant::fromValue(storage[index.row()].meta.drift_angle);
      case LX: return QVariant::fromValue(storage[index.row()].meta.lx);
      case LY: return QVariant::fromValue(storage[index.row()].meta.ly);
      case Div: return QVariant::fromValue(storage[index.row()].meta.div);
      case Velocity: return QVariant::fromValue(storage[index.row()].meta.velocity);
      case Altitude: return QVariant::fromValue(storage[index.row()].meta.altitude);
      case KR: return QVariant::fromValue(storage[index.row()].meta.kr);
      case TimeShift: return QVariant::fromValue(storage[index.row()].meta.time_shift);
      case TimeDuration: return QVariant::fromValue(storage[index.row()].meta.time_duration);
      case Mode: return QVariant::fromValue(storage[index.row()].meta.mode);
      case ImageType: return QVariant::fromValue(storage[index.row()].meta.image_type);
      case Crc16: return QVariant::fromValue(QString("0x" + QString::number(storage[index.row()].meta.crc16, 16)));
      case Valid: return QVariant::fromValue(storage[index.row()].valid);
      case LOD1FilePath: return QVariant::fromValue(storage[index.row()].path.second);
      case LOD0FilePath: return QVariant::fromValue(storage[index.row()].path.first);
      case Transparency: return QVariant::fromValue(storage[index.row()].opacity);
      case Shown: return QVariant::fromValue(storage[index.row()].shown);
      case MercatorZoomLevel: return QVariant::fromValue(storage[index.row()].mercator_zoom_level);
      case MarkedForExport: return QVariant::fromValue(storage[index.row()].marked_for_export);
      case Neural: return QVariant::fromValue(storage[index.row()].neural_data);

      default: return "Error reading from model";
    }
  }

  bool ImageModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if(data(index, role) != value)
    {
      switch(role)
      {
        case Index: return false;
        case Filename: storage[index.row()].filename = value.toString(); break;
        case Latitude: storage[index.row()].meta.latitude = value.toDouble(); break;
        case Longitude: storage[index.row()].meta.longitude = value.toDouble(); break;
        case DX: storage[index.row()].meta.dx = value.toFloat(); break;
        case DY: storage[index.row()].meta.dy = value.toFloat(); break;
        case X0: storage[index.row()].meta.x0 = value.toFloat(); break;
        case Y0: storage[index.row()].meta.y0 = value.toFloat(); break;
        case Angle: storage[index.row()].meta.angle = value.toFloat(); break;
        case DriftAngle: storage[index.row()].meta.drift_angle = value.toFloat(); break;
        case LX: storage[index.row()].meta.lx = value.toFloat(); break;
        case LY: storage[index.row()].meta.ly = value.toFloat(); break;
        case Div: storage[index.row()].meta.div = value.toFloat(); break;
        case Velocity: storage[index.row()].meta.velocity = value.toFloat(); break;
        case Altitude: storage[index.row()].meta.altitude = value.toFloat(); break;
        case KR: storage[index.row()].meta.kr = value.toFloat(); break;
        case TimeShift: storage[index.row()].meta.time_shift = value.toFloat(); break;
        case TimeDuration: storage[index.row()].meta.time_duration = value.toFloat(); break;
        case Mode: storage[index.row()].meta.mode = value.toInt(); break;
        case ImageType: storage[index.row()].meta.image_type = value.toInt(); break;
        case Crc16: storage[index.row()].meta.crc16 = value.toUInt(); break;
        case Valid: storage[index.row()].valid = value.toBool(); break;
        case LOD1FilePath: storage[index.row()].path.second = value.toString(); break;
        case LOD0FilePath: storage[index.row()].path.first = value.toString(); break;
        case Transparency: storage[index.row()].opacity = value.toFloat(); break;
        case Shown: storage[index.row()].shown = value.toBool(); break;
        case MercatorZoomLevel: storage[index.row()].mercator_zoom_level = value.toDouble(); break;
        case MarkedForExport: storage[index.row()].marked_for_export = value.toBool(); break;

        default: return false;
      }
      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void ImageModel::add(const TelescopicImage& image)
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    storage.push_back(image);
    endInsertRows();
    emit added();

    setTotalCount(rowCount());

    qDebug() << "[IMAGE] Model received new image. Now it contains" << rowCount() << "images";
  }

  void ImageModel::remove(int index)
  {
    beginRemoveRows(QModelIndex(), index, index);
    storage.remove(index);
    endRemoveRows();

    setTotalCount(rowCount());

    qDebug() << "[IMAGE] Model lost an image. Now it contains" << rowCount() << "images";
  }

  void ImageModel::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    storage.clear();
    endRemoveRows();

    setTotalCount(rowCount());

    qDebug() << "[IMAGE] Model cleared";
  }

  QVariant ImageModel::getRole(int i, const QString& role) const
  {
    if(role == "filepath")
      return data(index(i), LOD0FilePath);
    if(role == "filename")
      return data(index(i), Filename);
    if(role == "velocity")
      return data(index(i), Velocity);
    if(role == "elevation")
      return data(index(i), Altitude);
    if(role == "lx")
      return data(index(i), LX);
    if(role == "ly")
      return data(index(i), LY);
    if(role == "x0")
      return data(index(i), X0);
    if(role == "dx")
      return data(index(i), DX);
    return "Error parsing";
  }

  QGeoCoordinate ImageModel::lastImagePosition()
  {
    if(storage.empty())
      return {0, 0};
    return {storage.last().meta.latitude, storage.last().meta.longitude};
  }

  bool ImageModel::exportSelectedImages(const QString& target) noexcept
  {
    QList<QString> res;
    for(const auto& image: qAsConst(storage))
    {
      if(image.marked_for_export)
        res.push_back(image.path.first);
    }

    if(not res.empty())
    {
      qInfo() << "[IMAGE] Marked" << res.size() << "images for export. Exporting...";
      emit markedForExport(res, target);
      return true;
    }
    else
    {
      qWarning() << "[IMAGE] No images marked for export";
      return false;
    }
  }

  QVector<TelescopicImage>* ImageModel::direct() { return &storage; }
  int ImageModel::totalCount() const { return m_totalCount; }
  void ImageModel::setTotalCount(int other)
  {
    if(m_totalCount == other)
      return;
    m_totalCount = other;
    emit totalCountChanged();
  }

  void ImageModel::addNeuralData(const QList<QuasarSDK::NeuralData>& data, const QString& filename)
  {
    qDebug() << "$ [NEURAL] Image model is being requested to add neural data to image";
    int j = -1;
    int i = 0;

    for(const auto& image : storage)
    {
        qDebug() << "$" << "[NEURAL] Try: " << image.filename.chopped(4) << filename.chopped(4);
      if(image.filename.chopped(4) == filename.chopped(4))
      {
        j = i;
        break;
      }
      i++;
    }

    //if(j < 0 or j >= rowCount())
    if(j < 0){
        qDebug() << "$" << "[NEURAL] Filename is not same: " << filename;
        return;
    }

    storage[j].neural_data = data;
    qDebug() << "$" << "[NEURAL] Image model received data for image" << filename << "at index" << j;
    for(const auto& a : data)
      qDebug() << "$" << a.tag() << a.rect() << a.color();
    emit dataChanged(index(j), index(j), {Neural});
  }
} // Map
