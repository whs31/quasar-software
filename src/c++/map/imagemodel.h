#pragma once

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>
#include <QtPositioning/QGeoCoordinate>

#include "entities/image.h"

namespace Map
{
  class ImageModel : public QAbstractListModel
  {
    Q_OBJECT
      Q_PROPERTY(int totalCount READ totalCount WRITE setTotalCount NOTIFY totalCountChanged)

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        Filename,
        Latitude,
        Longitude,
        DX,
        DY,
        X0,
        Y0,
        Angle,
        DriftAngle,
        LX,
        LY,
        Div,
        Velocity,
        Altitude,
        KR,
        TimeShift,
        TimeDuration,
        Mode,
        ImageType,
        Crc16,
        Valid,
        LOD1FilePath,
        LOD0FilePath,
        Transparency,
        Shown,
        MercatorZoomLevel,
        MarkedForExport
      };

      explicit ImageModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      Q_INVOKABLE void add(const Image& image);
      Q_INVOKABLE void remove(int index);
      Q_INVOKABLE void clear();

      Q_INVOKABLE QVariant getRole(int index, const QString& role) const;

      Q_INVOKABLE QGeoCoordinate lastImagePosition();
      Q_INVOKABLE bool exportSelectedImages(const QString& target) noexcept;

      QVector<Image>* direct();

      [[nodiscard]] int totalCount() const; void setTotalCount(int);

    signals:
      void added();
      void totalCountChanged();
      void markedForExport(const QList<QString>& abs_paths, const QString& folder);

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      QVector<Image> storage;
      int m_totalCount;
  };
} // namespace Map;

Q_DECLARE_METATYPE(Map::ImageModel*)
