#include "ruler.h++"
#include "utils/numeric.h++"
#include <QtCore/QDebug>

using namespace Map;

Ruler::Ruler(QObject *parent)
    : QAbstractListModel{parent}
{
}

Ruler::~Ruler()
{
    beginResetModel();
    m_segments.clear();
    endResetModel();
}

int Ruler::rowCount(const QModelIndex &parent) const
{
    return m_segments.size();
}

QVariant Ruler::data(const QModelIndex& index, int role) const
{
    if (not index.isValid())
        return QVariant();

    switch(role) {
        case SegmentRoles::index: return index.row();
        case SegmentRoles::segment: return m_segments.at(index.row());
        case SegmentRoles::segmentLength: return std::round(m_path.at(index.row()).distanceTo(m_path.at(index.row() + 1)));
        case SegmentRoles::segmentCenter: return QVariant::fromValue(m_segmentsCenter.at(index.row()));
        default: return QVariant();
    }
}

QHash<int, QByteArray> Ruler::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[SegmentRoles::index] = "index";
    roles[SegmentRoles::segment] = "segment";
    roles[SegmentRoles::segmentLength] = "segmentLength";
    roles[SegmentRoles::segmentCenter] = "segmentCenter";
    return roles;
}

void Ruler::setRoute(const QList<QGeoCoordinate>& _path)
{
    beginResetModel();
    m_segments.clear();
    m_path = _path;
    for (int i = 0; i < _path.count() - 1; ++i) {
        m_orthodrom.setCoord1(_path.at(i));
        m_orthodrom.setCoord2(_path.at(i + 1));
        m_segments.append(m_orthodrom.getPoints());
        m_segmentsCenter.append(calculateCenter(m_segments.size() - 1));
    }
    endResetModel();
    for (int i = 0; i< m_path.size(); ++i){
        updatePoint(m_path.at(i), i);
    }
}

void Ruler::resetRoute()
{
    setLastLatitude(0);
    setLastLongitude(0);
    beginRemoveRows(QModelIndex(), 0 , m_segments.size() - 1);
    m_segments.clear();
    m_path.clear();
    m_segmentsCenter.clear();
    endRemoveRows();
}

void Ruler::insertPoint(const QGeoCoordinate& _point, quint16 _index)
{
    setLastLatitude(_point.latitude());
    setLastLongitude(_point.longitude());
    quint16 pointsCount = m_segments.size() + 1;
    if (_index > m_path.size() || _index < 0){
        qWarning() << "[MAP] Ruler : \t неправильный индекс при добавлении точки в маршрут. index: " << _index;
        return;
    }
    m_path.insert(_index, _point);
    if (m_path.size() == 1) {
        return;
    }
    else if (m_path.size() == 2){
        beginInsertRows(QModelIndex(), 0, 0);
        m_orthodrom.setCoord1(m_path.at(0));
        m_orthodrom.setCoord2(m_path.at(0 + 1));
        m_segmentsCenter.insert(0, calculateCenter(0));
        m_segments.insert(0, m_orthodrom.getPoints());
        endInsertRows();
        return;
    }
    if (_index == 0){
        beginInsertRows(QModelIndex(), 0, 0);
        m_orthodrom.setCoord1(_point);
        m_orthodrom.setCoord2(m_path.at(0));
        m_segmentsCenter.insert(0, calculateCenter(0));
        m_segments.insert(0, m_orthodrom.getPoints());
        endInsertRows();
    }
    else if (_index == m_path.size() - 1){
        beginInsertRows(QModelIndex(),m_segments.size(), m_segments.size());
        m_orthodrom.setCoord1(m_path.at(pointsCount - 1));  //???
        m_orthodrom.setCoord2(_point);
        m_segmentsCenter.insert(m_segments.size(), calculateCenter(m_segments.size()));
        m_segments.insert(m_segments.size(), m_orthodrom.getPoints());
        endInsertRows();
    }
    else {
        m_orthodrom.setCoord1(m_path.at(_index - 1));  //???
        m_orthodrom.setCoord2(m_path.at(_index));
        m_segments[_index - 1] =  m_orthodrom.getPoints();
        m_segmentsCenter[_index - 1] = calculateCenter(_index - 1);
        emit dataChanged(createIndex(_index - 1, 0), createIndex(_index - 1, 0));

        beginInsertRows(QModelIndex(), _index, _index);
        m_orthodrom.setCoord1(m_path.at(_index));  //???
        m_orthodrom.setCoord2(m_path.at(_index + 1));
        m_segmentsCenter.insert(_index, calculateCenter(_index));
        m_segments.insert(_index, m_orthodrom.getPoints());
        endInsertRows();
    }
}

void Ruler::removePoint(quint16 _index)
{
    quint16 pointsCount = m_segments.size() + 1;

    if (_index > pointsCount -1 || _index < 0){
        qWarning() << "[MAP] RouteOrthodromSegmentsModel : \t неправильный индекс при удаление точки из маршрута. index: " << _index;
        return;
    }
    if(m_path.size() == 1){
        m_path.removeAt(_index);
        return;
    }
    if (_index == 0){
        beginRemoveRows(QModelIndex(),_index, _index);
        m_segments.removeAt(_index);
        endRemoveRows();
        m_path.removeAt(_index);
    }
    else if (_index == pointsCount - 1){
        beginRemoveRows(QModelIndex(),m_segments.size() - 1, m_segments.size() - 1);
        m_segments.removeAt(m_segments.size() - 1);
        endRemoveRows();
        m_path.removeAt(_index);
    }
    else {
        beginRemoveRows(QModelIndex(),_index, _index);
        m_segments.removeAt(_index);
        endRemoveRows();
        m_orthodrom.setCoord1(m_path.at(_index - 1));  //???
        m_orthodrom.setCoord2(m_path.at(_index + 1));
        m_segments[_index - 1] =  m_orthodrom.getPoints();

        m_path.removeAt(_index);
        m_segmentsCenter.replace(_index - 1, calculateCenter(_index - 1));
        emit dataChanged(createIndex(_index - 1, 0), createIndex(_index - 1, 0));
    }
}

void Ruler::updatePoint(const QGeoCoordinate &_point, int _index)
{
    quint16 pointsCount = m_segments.size() + 1;
    if (_index > pointsCount -1 || _index < 0){
        qWarning() << "[MAP] RouteOrthodromSegmentsModel : \t неправильный индекс при обновлении точки из маршрута. index: " << _index;
        return;
    }
    m_path.replace(_index, _point);
    if(m_path.size() == 1){
        return;
    }
    if (_index == 0){
        m_orthodrom.setCoord1(m_path.at(0));
        m_orthodrom.setCoord2(m_path.at(0 + 1));
        m_segments[0] = m_orthodrom.getPoints();
        m_segmentsCenter[0] = calculateCenter(0);
        emit dataChanged(createIndex(0,0), createIndex(0,0));
    }
    else if (_index == pointsCount - 1) {
        m_orthodrom.setCoord1(m_path.at(pointsCount - 2));
        m_orthodrom.setCoord2(m_path.at(pointsCount - 1));
        m_segments[m_segments.size() - 1] = m_orthodrom.getPoints();
        m_segmentsCenter[m_segments.size() - 1] = calculateCenter(m_segments.size() - 1);
        emit dataChanged(createIndex(m_segments.size() - 1,0), createIndex(m_segments.size() - 1,0));
    }
    else {
        m_orthodrom.setCoord1(m_path.at(_index - 1));
        m_orthodrom.setCoord2(m_path.at(_index));
        m_segments[_index - 1] = m_orthodrom.getPoints();
        m_segmentsCenter[_index - 1] = calculateCenter(_index - 1);
        m_orthodrom.setCoord1(m_path.at(_index));  //???
        m_orthodrom.setCoord2(m_path.at(_index + 1));
        m_segments[_index] = m_orthodrom.getPoints();
        m_segmentsCenter[_index] = calculateCenter(_index);

        emit dataChanged(createIndex(_index - 1,0), createIndex(_index,0));
    }
}

QGeoCoordinate Ruler::calculateCenter(quint16 _index)
{
    auto coord1 = m_path.at(_index);
    auto coord2 = m_path.at(_index + 1);
    m_orthodrom.setCoord1(coord1);
    m_orthodrom.setCoord2(coord2);

    qreal centerLongitude;
    qreal centerLatitude;

    QGeoCoordinate centerCoord = coord1.atDistanceAndAzimuth( coord1.distanceTo(coord2)/2, coord1.azimuthTo(coord2));
    centerLongitude = centerCoord.longitude();
    centerLatitude = qIsNaN(m_orthodrom.getLatitude(centerLongitude)) ? (coord1.latitude() + coord2.latitude()) / 2 : m_orthodrom.getLatitude(centerLongitude);

    return QGeoCoordinate(centerLatitude, centerLongitude);
}

qreal Ruler::calculateAngle(const QGeoCoordinate _coord1, const QGeoCoordinate _coord2)
{
    qreal result;
    QPointF coord1 = Utilities::Numeric::geoCoordToWebMercator(_coord1);
    QPointF coord2 = Utilities::Numeric::geoCoordToWebMercator(_coord2);
    qreal newLong1 = _coord1.longitude();
    qreal newLong2 = _coord2.longitude();

    if (_coord1.longitude() < 0 && _coord2.longitude() > 0) {
        qreal shift = ( 180 - _coord2.longitude() + 1);
        if (_coord1.longitude() + shift < 0){
            newLong1 = _coord1.longitude() + shift;
            newLong2 = (_coord2.longitude() + shift) - 360;
            coord1 = Utilities::Numeric::geoCoordToWebMercator(QGeoCoordinate(_coord1.latitude(), _coord1.longitude() + shift));
            coord2 = Utilities::Numeric::geoCoordToWebMercator(QGeoCoordinate(_coord2.latitude(), (_coord2.longitude() + shift) - 360));
        }
    }
    else if (_coord2.longitude() < 0 && _coord1.longitude() > 0){
        qreal shift = (180 - _coord1.longitude() + 1);
        if (_coord2.longitude() + shift < 0){
            newLong1 = (_coord1.longitude() + shift) - 360;
            newLong2 = _coord2.longitude() + shift;
            coord2 = Utilities::Numeric::geoCoordToWebMercator(QGeoCoordinate(_coord2.latitude(), _coord2.longitude() + shift));
            coord1 = Utilities::Numeric::geoCoordToWebMercator(QGeoCoordinate(_coord1.latitude(), (_coord1.longitude() + shift) - 360));
        }
    }
    qreal angle = qAtan2(abs(coord1.y() - coord2.y()) , abs(coord1.x() - coord2.x())) * 180 / M_PI;
    result = ((_coord1.latitude() < _coord2.latitude() && newLong1 < newLong2) || (_coord1.latitude() > _coord2.latitude() && newLong1 > newLong2)) ? angle - 90 : 90 - angle;

    return result;
}
