#pragma once

#include <utility>
#include <vector>
#include <map>
#include <QtCore/QAbstractListModel>

using std::vector;
using std::map;

namespace GUI
{
  class NotificationsModel : public QAbstractListModel
  {
    Q_OBJECT

    struct Notification
    {
      Notification(int type, int level, QString msg) : type(type), level(level), message(std::move(msg)) {}
      int type;
      int level;
      QString message;
    };

    public:
      enum NotificationType
      {
        NotConnected,
        Uncalibrated
      };
      Q_ENUM(NotificationType)

      enum NotificationLevel
      {
        Info,
        Warn,
        Alert
      };
      Q_ENUM(NotificationLevel)

      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        Message,
        WarnLevel
      };

      static NotificationsModel* get();

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      Q_INVOKABLE void add(int notification_type, int warn_level);
      Q_INVOKABLE void remove(int notification_type) noexcept;
      Q_INVOKABLE void clear();

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      explicit NotificationsModel(QObject* parent = nullptr);
      NotificationsModel(const NotificationsModel&);
      NotificationsModel& operator=(const NotificationsModel&);

    private:
      vector<Notification> m_storage;
      map<NotificationType, QString> m_dictionary;
  };
} // GUI