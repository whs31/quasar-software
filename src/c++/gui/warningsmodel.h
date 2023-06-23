#pragma once

#include <vector>
#include <QtCore/QAbstractListModel>

using std::vector;

namespace GUI
{
  class WarningsModel : public QAbstractListModel
  {
    Q_OBJECT

    struct WarningData
    {
      int type;
      QString msg;
      bool is_major;
    };

    public:
      enum Notification
      {
        NotConnected,
        Uncalibrated
      };
      Q_ENUM(Notification)

      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        Message,
        Major
      };

      static WarningsModel* get();

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      Q_INVOKABLE void append(int type, const QString& message, bool is_major);
      Q_INVOKABLE void remove(int type) noexcept;
      Q_INVOKABLE void clear();

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      explicit WarningsModel(QObject* parent = nullptr);
      WarningsModel(const WarningsModel&);
      WarningsModel& operator=(const WarningsModel&);

    private:
      vector<WarningData> storage;
  };
} // GUI

