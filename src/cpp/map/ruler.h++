#pragma once

#include <definitions.h++>
#include "tools/orthodrom.h++"
#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <memory>

namespace Map
{
    class Ruler : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(qreal lastLatitude READ lastLatitude WRITE setLastLatitude NOTIFY lastLatitudeChanged)
        Q_PROPERTY(qreal lastLongitude READ lastLongitude WRITE setLastLongitude NOTIFY lastLongitudeChanged)
        Q_PROPERTY(qreal totalLength READ totalLength WRITE setTotalLength NOTIFY totalLengthChanged)

        QList<QVariantList> m_segments;
        QList<QGeoCoordinate> m_path;
        QList<QGeoCoordinate> m_segmentsCenter;
        Orthodrom m_orthodrom;

        qreal m_lastLatitude = 0;
        qreal m_lastLongitude = 0;
        qreal m_totalLength = 0;

        public:
            explicit Ruler(QObject *parent = nullptr);
            ~Ruler() override;

            enum SegmentRoles {
                index = Qt::UserRole + 1,
                segment,
                segmentLength,
                segmentCenter
            };

            __qml int rowCount(const QModelIndex &parent = QModelIndex()) const override;
            QVariant data(const QModelIndex &index, int role) const override;
            QHash<int, QByteArray> roleNames() const override;

            __qml void setRoute(const QList<QGeoCoordinate> &_path);
            __qml void resetRoute();
            __qml void insertPoint(const QGeoCoordinate & _point, quint16 _index);
            __qml void removePoint(quint16 _index);
            __qml void updatePoint(const QGeoCoordinate & _point, int _index);
            __qml QGeoCoordinate calculateCenter(quint16 _index);
            __qml qreal calculateAngle(const QGeoCoordinate _coord1, const QGeoCoordinate _coord2);

            qreal totalLength() const;
            void setTotalLength(qreal other);

            qreal lastLatitude() const;
            void setLastLatitude(qreal other);

            qreal lastLongitude() const;
            void setLastLongitude(qreal other);

            signals:
                __signal totalLengthChanged();
                __signal lastLatitudeChanged();
                __signal lastLongitudeChanged();
    };
} // namespace Map;

Q_DECLARE_METATYPE(Map::Ruler*)
