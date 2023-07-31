#pragma once

#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>
#include "map/entities/plannermark.h"

namespace Map
{
  class PlannerMarkModel : public QAbstractListModel
  {
    Q_OBJECT

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        MarkerCoordinate,
        MarkerName,
        MarkerColor,
        MarkerID,
        MarkerRadius,
        MarkerAddress,
        MarkerLifetime,
        MarkerCommand
      };

      explicit PlannerMarkModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      void add(const Map::PlannerMark& marker);
      Q_INVOKABLE void add(double latitude, double longitude, const QString& name, const QColor& color,
                           int radius, const QString& address, int lifetime, const QString& command);
      Q_INVOKABLE void remove(int index);
      Q_INVOKABLE void clear();

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      QVector<PlannerMark> m_storage;
  };
} // Map
