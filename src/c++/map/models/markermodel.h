#pragma once

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>
#include <QtPositioning/QGeoCoordinate>
#include "map/entities/marker.h"

namespace Map
{
  class MarkerModel : public QAbstractListModel
  {
    Q_OBJECT

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        Latitude,
        Longitude,
        MarkerName,
        MarkerColor,
        MarkerIcon
      };

      explicit MarkerModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      Q_INVOKABLE void add(const Map::Marker& image);
      Q_INVOKABLE void remove(int index);
      Q_INVOKABLE void clear();

    signals:
      void added();

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      QVector<Marker> storage;
  };
} // namespace Map;

Q_DECLARE_METATYPE(Map::MarkerModel*)
