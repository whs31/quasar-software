//
// Created by whs31 on 20.07.23.
//

#pragma once

#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>
#include <QuasarSDK/Map/MapImageSegment>

namespace Map
{
  class StreamSegmentModel : public QAbstractListModel
  {
    Q_OBJECT

    public:
      enum ModelRoles
      {
        Index = Qt::UserRole + 1,
        ChunkCoordinate,
        ChunkAzimuth,
        ChunkOffset,
        ChunkSize,
        ChunkZoomLevel,
        ChunkRatio,
        ChunkOpacity,
        ChunkVisibility,
        Base64
      };

      explicit StreamSegmentModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      bool setData(const QModelIndex& index, const QVariant& value, int role) override;

      void add(const QuasarSDK::Map::MapImageSegment& image_segment);
      Q_INVOKABLE void remove(int index);
      Q_INVOKABLE void clear();

    protected:
      QHash<int, QByteArray> roleNames() const override;

    private:
      QVector<QuasarSDK::Map::MapImageSegment> m_storage;
  };
} // Map
