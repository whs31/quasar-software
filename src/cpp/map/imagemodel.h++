#pragma once

#include <Definitions>
#include <QtCore/QAbstractListModel>

#include "entities/image.h++"

namespace Map
{
    class ImageModel : public QAbstractListModel
    {
        Q_OBJECT

        public:
            enum ModelRole
            {
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
                LOD1File,
                LOD0File
            };

            explicit ImageModel(QObject *parent = nullptr);

            QHash<int, QByteArray> roleNames() const override;

            int rowCount(const QModelIndex &parent = QModelIndex()) const override;
            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
            bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
            bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
            bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

        private:
    };
} // namespace Map;
