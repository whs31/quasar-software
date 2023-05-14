#pragma once

#include "tools/orthodrom.h"
#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <memory>
#include <ccl/ccl_global.h>

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

            Q_INVOKABLE void setRoute(const QList<QGeoCoordinate> &_path);
            Q_INVOKABLE void resetRoute();
            Q_INVOKABLE void insertPoint(const QGeoCoordinate & _point, quint16 _index);
            Q_INVOKABLE void removePoint(quint16 _index);
            Q_INVOKABLE void updatePoint(const QGeoCoordinate & _point, int _index);
            Q_INVOKABLE QGeoCoordinate calculateCenter(quint16 _index);
            Q_INVOKABLE qreal calculateAngle(const QGeoCoordinate _coord1, const QGeoCoordinate _coord2);

            signals:
                void totalLengthChanged();
                void lastLatitudeChanged();
                void lastLongitudeChanged();

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
