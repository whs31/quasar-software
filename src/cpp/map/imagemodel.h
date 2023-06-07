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
                MercatorZoomLevel
            };

            explicit ImageModel(QObject* parent = nullptr);

            int rowCount(const QModelIndex& parent = QModelIndex()) const override;
            QVariant data(const QModelIndex& index, int role) const override;
            bool setData(const QModelIndex& index, const QVariant& value, int role) override;

            Q_INVOKABLE void add(const Image& image);
            Q_INVOKABLE void remove(int index);
            Q_INVOKABLE void clear();

            Q_INVOKABLE QGeoCoordinate lastImagePosition();

            QVector<Image>* direct();

            int totalCount() const;
            void setTotalCount(int other);

            signals:
                void added();
                void totalCountChanged();

        protected:
            QHash<int, QByteArray> roleNames() const override;

        private:
            QVector<Image> storage;
            int m_totalCount;
    };
} // namespace Map;

Q_DECLARE_METATYPE(Map::ImageModel*)
