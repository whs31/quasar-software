#include "warningsmodel.h"
#include <QtCore/QDebug>

namespace GUI
{
  WarningsModel* WarningsModel::get() { static WarningsModel instance; return &instance; }

  WarningsModel::WarningsModel(QObject* parent)
    : QAbstractListModel(parent)
  {}

  QHash<int, QByteArray> WarningsModel::roleNames() const
  {
    QHash<int, QByteArray> roles;
    roles[Index] = "index";
    roles[Message] = "message";
    roles[Major] = "major";
    return roles;
  }

  int WarningsModel::rowCount(const QModelIndex& parent) const { return storage.size(); }
  QVariant WarningsModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return QVariant();

    switch (role)
    {
      case Index: return index.row();
      case Message: return QVariant::fromValue(storage[index.row()].msg);
      case Major: return QVariant::fromValue(storage[index.row()].is_major);

      default: return "Error reading from model";
    }
  }

  bool WarningsModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if (data(index, role) != value) {

      switch (role)
      {
        case Index: return false;
        case Message: storage[index.row()].msg = value.toString(); break;
        case Major: storage[index.row()].is_major = value.toBool(); break;

        default: return false;
      }

      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void WarningsModel::append(int type, const QString& message, bool is_major)
  {
    for(const auto& notification : storage)
      if(notification.type == type)
        return;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    storage.push_back({type, message, is_major});
    endInsertRows();

    qDebug() << "[NOTIFICATIONS] Warning added: " << storage.size();
  }

  void WarningsModel::remove(int type) noexcept
  {
    int index = -1;
    int i = 0;
    for(const auto& notification : storage)
    {
      if(notification.type == type) {
        index = i;
        break;
      }
      i++;
    }

    if(index < 0 or index >= storage.size())
      return;

    beginRemoveRows(QModelIndex(), index, index);
    storage.erase(storage.begin() + index);
    endRemoveRows();

    qDebug() << "[NOTIFICATIONS] Warning removed: " << storage.size();
  }

  void WarningsModel::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    storage.clear();
    endRemoveRows();
  }

} // GUI
