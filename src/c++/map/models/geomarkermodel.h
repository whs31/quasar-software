#pragma once

#include <vector>
#include <QtCore/QAbstractListModel>
#include "map/entities/geomarker.h"

using std::vector;

namespace Map
{
  class GeoMarkerModel : public QAbstractListModel
  {
    Q_OBJECT

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        MarkerCoordinate,
        MarkerName,
        MarkerColor,
        MarkerIcon
      };

      explicit GeoMarkerModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      void add(const Map::GeoMarker& marker);
      Q_INVOKABLE void remove(int index);
      Q_INVOKABLE void clear();

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      vector<GeoMarker> m_storage;
  };
} // Map
