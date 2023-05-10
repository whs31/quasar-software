#pragma once

#include <Definitions>
#include <QtCore/QAbstractListModel>
#include <QtCore/QVector>

#include "entities/image.h++"

namespace Map
{
    class ImageModel : public QAbstractListModel
    {
        Q_OBJECT

        public:
            enum ModelRole
            {
                Index,
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
                LOD0FilePath
            };

            explicit ImageModel(QObject* parent = nullptr);

            QHash<int, QByteArray> roleNames() const override;
            int rowCount(const QModelIndex &parent = QModelIndex()) const override;
            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
            bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

            __qml void add(const Image& image);
            __qml void remove(int index);
            __qml void clear();

        private:
            QVector<Image> storage;
    };
} // namespace Map;
