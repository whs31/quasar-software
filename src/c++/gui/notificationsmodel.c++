#include "notificationsmodel.h"
#include <QtCore/QDebug>

namespace GUI
{
  NotificationsModel* NotificationsModel::get() { static NotificationsModel instance; return &instance; }
  NotificationsModel::NotificationsModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_dictionary({
      {NotConnected, "Отсутствует соединение с РЛС"},
      {Uncalibrated, "Не выполнена калибровка высоты!"},
    })
  {}

  int NotificationsModel::rowCount(const QModelIndex& parent) const { return static_cast<int>(m_storage.size()); }
  QVariant NotificationsModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return {};

    switch (role)
    {
      case Index: return index.row();
      case Message: return QVariant::fromValue(m_storage[index.row()].message);
      case WarnLevel: return QVariant::fromValue(m_storage[index.row()].level);

      default: return "Error reading from model";
    }
  }

  bool NotificationsModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if (data(index, role) != value)
    {
      switch (role)
      {
        case Index: return false;
        case Message: m_storage[index.row()].message = value.toString(); break;
        case WarnLevel: m_storage[index.row()].level = value.toInt(); break;

        default: return false;
      }

      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void NotificationsModel::add(int notification_type, int warn_level)
  {
    for(const auto& notification : m_storage)
      if(notification.type == notification_type)
        return;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_storage.emplace_back(notification_type, warn_level, m_dictionary[(NotificationType)notification_type]);
    endInsertRows();

    qDebug() << "[NOTIFICATIONS] Warning added: " << m_storage.size();
  }

  void NotificationsModel::remove(int notification_type) noexcept
  {
    int index = -1;
    int i = 0;
    for(const auto& notification : m_storage)
    {
      if(notification.type == notification_type) {
        index = i;
        break;
      }
      i++;
    }

    if(index < 0 or index >= m_storage.size())
      return;

    beginRemoveRows(QModelIndex(), index, index);
    m_storage.erase(m_storage.begin() + index);
    endRemoveRows();

    qDebug() << "[NOTIFICATIONS] Warning removed: " << m_storage.size();
  }

  void NotificationsModel::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_storage.clear();
    endRemoveRows();
  }

  QHash<int, QByteArray> NotificationsModel::roleNames() const
  {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[Index] = "index";
    roles[Message] = "message";
    roles[WarnLevel] = "level";
    return roles;
  }
} // GUI