#include "imagemodel.h++"

using namespace Map;

ImageModel::ImageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> ImageModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[ModelRole::Index] = "index";
    roles[ModelRole::Filename] = "filename";
    roles[ModelRole::Latitude] = "latitude";
    roles[ModelRole::Longitude] = "longitude";
    roles[ModelRole::DX] = "dx";
    roles[ModelRole::DY] = "dy";
    roles[ModelRole::X0] = "x0";
    roles[ModelRole::Y0] = "y0";
    roles[ModelRole::Angle] = "angle";
    roles[ModelRole::DriftAngle] = "drift_angle";
    roles[ModelRole::LX] = "lx";
    roles[ModelRole::LY] = "ly";
    roles[ModelRole::Div] = "div";
    roles[ModelRole::Velocity] = "velocity";
    roles[ModelRole::Altitude] = "altitude";
    roles[ModelRole::KR] = "kr";
    roles[ModelRole::TimeShift] = "time_shift";
    roles[ModelRole::TimeDuration] = "time_duration";
    roles[ModelRole::Mode] = "mode";
    roles[ModelRole::Crc16] = "crc16";
    roles[ModelRole::Valid] = "valid";
    roles[ModelRole::LOD1FilePath] = "lod1";
    roles[ModelRole::LOD0FilePath] = "lod0";
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

    switch (role)
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
        case Crc16: return QVariant::fromValue(QString("0x" + QString::number(storage[index.row()].meta.crc16, 16)));
        case Valid: return QVariant::fromValue(storage[index.row()].valid);
        case LOD1FilePath: return QVariant::fromValue(storage[index.row()].path.second);
        case LOD0FilePath: return QVariant::fromValue(storage[index.row()].path.first);

        default: return "Error reading from model";
    }
}

bool ImageModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value) {

        switch (role)
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
            case Mode: storage[index.row()].meta.mode = value.toFloat(); break;
            case Crc16: storage[index.row()].meta.crc16 = value.toUInt(); break;
            case Valid: storage[index.row()].valid = value.toBool(); break;
            case LOD1FilePath: storage[index.row()].path.second = value.toString(); break;
            case LOD0FilePath: storage[index.row()].path.first = value.toString(); break;

            default: return false;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void ImageModel::add(const Image& image)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    storage.push_back(image);
    endInsertRows();
}

void ImageModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    storage.remove(index);
    endRemoveRows();
}

void ImageModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    storage.clear();
    endRemoveRows();
}


