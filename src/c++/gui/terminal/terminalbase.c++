#include "terminalbase.h"

namespace GUI
{

  TerminalBase::TerminalBase(QObject* parent)
    : QAbstractListModel(parent)
  {}

  QHash<int, QByteArray> TerminalBase::roleNames() const
  {
    QHash<int, QByteArray> roles;
    roles[Index] = "index";
    roles[Message] = "message";
    roles[Module] = "module";
    roles[Type] = "type";
    return roles;
  }

  int TerminalBase::rowCount(const QModelIndex& parent) const { return storage.size(); }
  QVariant TerminalBase::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return QVariant();

    switch (role)
    {
      case Index: return index.row();
      case Message: return QVariant::fromValue(storage[index.row()].msg);
      case Module: return QVariant::fromValue(storage[index.row()].mdl);
      case Type: return storage[index.row()].type;

      default: return "Error reading from model";
    }
  }

  bool TerminalBase::setData(const QModelIndex& index, const QVariant& value, int role)
  {
    if (data(index, role) != value) {

      switch (role)
      {
        case Index: return false;
        case Message: storage[index.row()].msg = value.toString(); break;
        case Module: storage[index.row()].mdl = value.toString(); break;
        case Type: storage[index.row()].type = (MessageType)value.toInt(); break;

        default: return false;
      }
      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  void TerminalBase::append(const QString& message, const QString& module, MessageType type)
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    storage.push_back({message, module, type});
    endInsertRows();
  }

  void TerminalBase::clear()
  {
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    storage.clear();
    endRemoveRows();
  }

} // GUI
