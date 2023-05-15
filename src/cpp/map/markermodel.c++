#include "markermodel.h"
#include <QtCore/QDebug>

using namespace Map;

MarkerModel::MarkerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> MarkerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Index] = "index";
    roles[Latitude] = "latitude";
    roles[Longitude] = "longitude";
    roles[MarkerName] = "marker_name";
    roles[MarkerColor] = "marker_color";
    roles[MarkerIcon] = "marker_icon";
    return roles;
}

int MarkerModel::rowCount(const QModelIndex& parent) const
{
    return storage.size();
}

QVariant MarkerModel::data(const QModelIndex& index, int role) const
{
    if(not index.isValid())
        return QVariant();

    switch (role)
    {
        case Index: return index.row();
        case Latitude: return QVariant::fromValue(storage[index.row()].latitude);
        case Longitude: return QVariant::fromValue(storage[index.row()].longitude);
        case MarkerName: return QVariant::fromValue(storage[index.row()].name);
        case MarkerColor: return QVariant::fromValue(storage[index.row()].color);
        case MarkerIcon: return QVariant::fromValue(storage[index.row()].icon);

        default: return "Error reading from model";
    }
}

bool MarkerModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value) {

        switch (role)
        {
            case Index: return false;
            case Latitude: storage[index.row()].latitude = value.toDouble(); break;
            case Longitude: storage[index.row()].longitude = value.toDouble(); break;
            case MarkerName: storage[index.row()].name = value.toString(); break;
            case MarkerColor: storage[index.row()].color = value.toString(); break;
            case MarkerIcon: storage[index.row()].icon = value.toString(); break;

            default: return false;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void MarkerModel::add(const Marker& image)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    storage.push_back(image);
    endInsertRows();
    emit added();

    qDebug() << "[MARKER] Model received new marker. Now it contains" << rowCount() << "markers";
}

void MarkerModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    storage.remove(index);
    endRemoveRows();

    qDebug() << "[MARKER] Model lost an marker. Now it contains" << rowCount() << "markers";
}

void MarkerModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    storage.clear();
    endRemoveRows();

    qDebug() << "[MARKER] Model cleared";
}


