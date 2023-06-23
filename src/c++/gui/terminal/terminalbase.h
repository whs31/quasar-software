#pragma once

#include <vector>
#include <QtCore/QAbstractListModel>

using std::vector;

namespace GUI
{
  class TerminalBase : public QAbstractListModel
  {
    public:
      enum MessageType
      {
        Debug,
        Info,
        Warning,
        Error,
        Extra1,
        Extra2,
        Extra3,
        Extra4,
        Extra5,
        Extra6,
        Extra7,
        Extra8,
        Extra9
      };

      struct BasicMessage
      {
        QString msg;
        QString mdl;
        MessageType type;
      };

    private:
    Q_OBJECT
      Q_ENUM(MessageType)

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        Message,
        Module,
        Type
      };

      explicit TerminalBase(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      Q_INVOKABLE virtual void append(const QString& message, const QString& module = "", GUI::TerminalBase::MessageType type = Debug);
      Q_INVOKABLE virtual void clear();

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      vector<BasicMessage> storage;
  };
} // GUI

