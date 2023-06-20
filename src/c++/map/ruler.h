#pragma once

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include <CCL/Orthodrom>
#include <memory>

namespace Map
{
    class Ruler : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(double lastLatitude READ lastLatitude WRITE setLastLatitude NOTIFY lastLatitudeChanged)
        Q_PROPERTY(double lastLongitude READ lastLongitude WRITE setLastLongitude NOTIFY lastLongitudeChanged)
        Q_PROPERTY(double totalLength READ totalLength WRITE setTotalLength NOTIFY totalLengthChanged)

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

            [[nodiscard]] double totalLength() const; void setTotalLength(double);
            [[nodiscard]] double lastLatitude() const; void setLastLatitude(double);
            [[nodiscard]] double lastLongitude() const; void setLastLongitude(double);

            signals:
                void totalLengthChanged();
                void lastLatitudeChanged();
                void lastLongitudeChanged();

        private:
            QList<QVariantList> m_segments;
            QList<QGeoCoordinate> m_path;
            QList<QGeoCoordinate> m_segmentsCenter;
            CCL::Orthodrom m_orthodrom;

            double m_lastLatitude = 0;
            double m_lastLongitude = 0;
            double m_totalLength = 0;
    };
} // namespace Map;

Q_DECLARE_METATYPE(Map::Ruler*)
