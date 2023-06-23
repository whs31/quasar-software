#pragma once

#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>
#include <QtPositioning/QGeoCoordinate>
#include "entities/image.h"

namespace Map
{
  class StripModel : public QAbstractListModel
  {
    Q_OBJECT

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        Filename,
        Latitude,
        Longitude,
        Azimuth,
        LX,
        LY,
        DX,
        Valid,
        LOD1FilePath,
        LOD0FilePath,
        Transparency,
        Shown,
        MercatorZoomLevel,
        MarkedForExport
      };

      explicit StripModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      void add(const StripImage& image);
      Q_INVOKABLE void remove(int index);
      Q_INVOKABLE void clear();
      Q_INVOKABLE bool exportSelectedImages(const QString& target) noexcept;

      QVector<StripImage>* direct();

    signals:
      void markedForExport(const QList<QString>& abs_paths, const QString& folder);

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      QVector<StripImage> storage;
  };
} // Map
