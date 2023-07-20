#pragma once

#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>
#include "map/entities/geomarker.h"

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

      enum SaveFormat
      {
        JSON,
        PlainText
      };
      Q_ENUM(SaveFormat)

      explicit GeoMarkerModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      void add(const Map::GeoMarker& marker);
      Q_INVOKABLE void remove(int index);
      Q_INVOKABLE void clear();

      Q_INVOKABLE void save(const QString& path, Map::GeoMarkerModel::SaveFormat format) const noexcept;
      Q_INVOKABLE void load(const QString& path) noexcept;

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      QByteArray toJSON() const noexcept;
      QByteArray toPlainText() const noexcept;

    private:
      QVector<GeoMarker> m_storage;
  };
} // Map
