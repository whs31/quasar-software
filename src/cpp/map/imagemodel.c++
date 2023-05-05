#include "imagemodel.h++"

using namespace Map;

ImageModel::ImageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> ImageModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
//    roles[SegmentRoles::index] = "index";
//    roles[SegmentRoles::segment] = "segment";
//    roles[SegmentRoles::segmentLength] = "segmentLength";
//    roles[SegmentRoles::segmentCenter] = "segmentCenter";
    return roles;
}

int ImageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool ImageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

bool ImageModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool ImageModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

