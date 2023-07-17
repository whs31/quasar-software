#include "CMessageModel.h"
#include <mutex>
#include <QtCore/QDebug>

namespace QuasarSDK::IO
{

  std::mutex locker;

  MessageModel::MessageModel(QObject* parent)
      : QAbstractListModel(parent)
  {}

  QHash<int, QByteArray> QuasarSDK::IO::MessageModel::roleNames() const
  {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[Index] = "index";
    roles[Message] = "message";
    roles[Type] = "type";
    return roles;
  }

  int QuasarSDK::IO::MessageModel::rowCount(const QModelIndex& parent) const { return static_cast<int>(m_storage.size()); }
  QVariant QuasarSDK::IO::MessageModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return {};

    switch (role)
    {
      case Index: return index.row();
      case Message: return QVariant::fromValue(m_storage[index.row()]->message());
      case Type: return QVariant::fromValue(m_storage[index.row()]->type());

      default: return "Error reading from model";
    }
  }

  bool QuasarSDK::IO::MessageModel::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if (data(index, role) != value) {
      switch (role)
      {
        case Index: return false;
        case Message: m_storage[index.row()]->setMessage(value.toString()); break;
        case Type: m_storage[index.row()]->setType(static_cast<IMessage::MessageType>(value.toInt())); break;

        default: return false;
      }

      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void MessageModel::append(unique_ptr<IMessage> message)
  {
    if(not message)
    {
      qCritical() << "[MESSAGE MODEL] Received nullptr!";
      return;
    }

    locker.lock();
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_storage.emplace_back(std::move(message));
    endInsertRows();
    locker.unlock();
  }

  void QuasarSDK::IO::MessageModel::clear()
  {
    qDebug() << "[MESSAGE MODEL] Model cleared";

    locker.lock();
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_storage.clear();
    endRemoveRows();
    locker.unlock();
  }

} // QuasarSDK::IO


