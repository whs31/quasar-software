#pragma once

#include <Definitions>
#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>
#include <QtPositioning/QGeoCoordinate>

#include "entities/image.h++"

namespace Map
{
    class ImageModel : public QAbstractListModel
    {
        Q_OBJECT

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

            __exposed void add(const Image& image);
            __exposed void remove(int index);
            __exposed void clear();

            __exposed QGeoCoordinate lastImagePosition();

            QVector<Image>* direct();

            signals:
                __signal added();

        protected:
            QHash<int, QByteArray> roleNames() const override;

        private:
            QVector<Image> storage;
    };
} // namespace Map;

Q_DECLARE_METATYPE(Map::ImageModel*)
