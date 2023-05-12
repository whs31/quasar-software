#pragma once

#include <Definitions>
#include "tools/orthodrom.h++"
#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <memory>

namespace Map
{
    class Ruler : public QAbstractListModel
    {
        Q_OBJECT
        PROPERTY_DEF(qreal, lastLatitude, setLastLatitude, m_lastLatitude)
        PROPERTY_DEF(qreal, lastLongitude, setLastLongitude, m_lastLongitude)
        PROPERTY_DEF(qreal, totalLength, setTotalLength, m_totalLength)

        public:
            explicit Ruler(QObject* parent = nullptr);
            ~Ruler() override;

            enum SegmentRoles {
                index = Qt::UserRole + 1,
                segment,
                segmentLength,
                segmentCenter
            };

            QVariant data(const QModelIndex &index, int role) const override;
            QHash<int, QByteArray> roleNames() const override;
            int rowCount(const QModelIndex &parent = QModelIndex()) const override;

            __exposed void setRoute(const QList<QGeoCoordinate> &_path);
            __exposed void resetRoute();
            __exposed void insertPoint(const QGeoCoordinate & _point, quint16 _index);
            __exposed void removePoint(quint16 _index);
            __exposed void updatePoint(const QGeoCoordinate & _point, int _index);
            __exposed QGeoCoordinate calculateCenter(quint16 _index);
            __exposed qreal calculateAngle(const QGeoCoordinate _coord1, const QGeoCoordinate _coord2);

            signals:
                __property_signal totalLengthChanged();
                __property_signal lastLatitudeChanged();
                __property_signal lastLongitudeChanged();

        private:
            QList<QVariantList> m_segments;
            QList<QGeoCoordinate> m_path;
            QList<QGeoCoordinate> m_segmentsCenter;
            Orthodrom m_orthodrom;

            qreal m_lastLatitude = 0;
            qreal m_lastLongitude = 0;
            qreal m_totalLength = 0;
    };
} // namespace Map;

Q_DECLARE_METATYPE(Map::Ruler*)
