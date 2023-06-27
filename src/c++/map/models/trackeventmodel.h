#pragma once

#include <QtCore/QAbstractListModel>

class QGeoCoordinate;

namespace Map
{
  class TrackEventModel : public QAbstractListModel
  {
    Q_OBJECT
      enum ModelRoles
      {
        EventIndex = Qt::UserRole + 1,
        EventPath
      };

      struct EventData
      {
        QVariantList m_path;
      };

    public:
      explicit TrackEventModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      QHash<int, QByteArray> roleNames() const override;

      Q_INVOKABLE void createNewEvent();
      Q_INVOKABLE void appendNewValue(const QGeoCoordinate& coord);
      Q_INVOKABLE void setMaxEvents(int count);

    private:
      std::vector<EventData> m_data;
      int m_maxEvents;
  };
} // Map
