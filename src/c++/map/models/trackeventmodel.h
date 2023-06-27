#ifndef TRACKEVENTMODEL_H
#define TRACKEVENTMODEL_H

#include <QtCore/QAbstractListModel>

class QGeoCoordinate;
namespace Map {
class TrackEventModel : public QAbstractListModel
{
    Q_OBJECT
    enum ModelRoles{
        EventIndex = Qt::UserRole + 1,
        EventPath
    };
    struct EventData{
        QVariantList m_path;

    };


public:
    explicit TrackEventModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void createNewEvent();
    Q_INVOKABLE void appendNewValue(const QGeoCoordinate &_coord);
    Q_INVOKABLE void setEventsCount(const quint8 _eventsCount);

signals:
private:
    std::vector<EventData> m_data;
    quint8 m_eventsCount = 2;
};
}

#endif // TRACKEVENTMODEL_H
