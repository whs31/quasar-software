#include "orthodrom.h++"
#include <QtCore/QDebug>

using namespace Map;

Orthodrom::Orthodrom()
    : _coord1(QGeoCoordinate(0,0))
    , _coord2(QGeoCoordinate(0,0))

{}

Orthodrom::Orthodrom(const QGeoCoordinate &coord1, const QGeoCoordinate &coord2)
{
    _coord1 = coord1;
    _coord2 = coord2;
    A1 = qTan(qDegreesToRadians(_coord1.latitude())) / qSin(qDegreesToRadians(_coord2.longitude() - _coord1.longitude()));
    A2 = qTan(qDegreesToRadians(_coord2.latitude())) / qSin(qDegreesToRadians(_coord2.longitude() - _coord1.longitude()));
    setPoints(10);
}

void Orthodrom::setCoord1(const QGeoCoordinate &coord1)
{
    _coord1 = coord1;
    A1 = qTan(qDegreesToRadians(_coord1.latitude())) / qSin(qDegreesToRadians(_coord2.longitude() - _coord1.longitude()));
    A2 = qTan(qDegreesToRadians(_coord2.latitude())) / qSin(qDegreesToRadians(_coord2.longitude() - _coord1.longitude()));
    setPoints(10);
}

void Orthodrom::setCoord2(const QGeoCoordinate &coord2)
{
    _coord2 = coord2;
    A1 = qTan(qDegreesToRadians(_coord1.latitude())) / qSin(qDegreesToRadians(_coord2.longitude() - _coord1.longitude()));
    A2 = qTan(qDegreesToRadians(_coord2.latitude())) / qSin(qDegreesToRadians(_coord2.longitude() - _coord1.longitude()));
    setPoints(10);
}

qreal Orthodrom::getDistance()
{
    double tmp = qSin(qDegreesToRadians(_coord1.latitude())) * qSin(qDegreesToRadians(_coord2.latitude())) +
                 qCos(qDegreesToRadians(_coord1.latitude())) * qCos(qDegreesToRadians(_coord2.latitude())) * qCos(qDegreesToRadians(_coord2.longitude() - _coord1.longitude()));
    double angle = qRadiansToDegrees(qAcos(tmp)) * 60;
    return angle * 1.853;//морская милья
}

qreal Orthodrom::getLatitude(qreal longitude)
{
    qreal angle = qAtan(A2 * qSin(qDegreesToRadians(longitude - _coord1.longitude()))
                        + A1 * qSin(qDegreesToRadians(_coord2.longitude() - longitude)));
    return qRadiansToDegrees(angle);
}

QVariantList Orthodrom::getPoints(/*quint16 spacing*/)
{
    if(qSin(_coord1.longitude() - _coord2.longitude())){
        return orthodromPath;
    }
    return {QVariant::fromValue(_coord1), QVariant::fromValue(_coord2)};
}

void Orthodrom::setPoints(quint16 spacing)
{
    if (qIsNaN(A1) || qIsNaN(A2)){
        return;
    }
    orthodromPath.clear();
    orthodromPath << QVariant::fromValue(_coord2);
    qreal az = _coord1.azimuthTo(_coord2);
    qreal distance = getDistance();
    while (distance - spacing > 0){
        QGeoCoordinate tmp = _coord1.atDistanceAndAzimuth(distance * 1000, az);
        orthodromPath << QVariant::fromValue(QGeoCoordinate(getLatitude(tmp.longitude()), tmp.longitude(), 0));
        distance -= spacing;
    }
    QGeoCoordinate tmp = _coord1.atDistanceAndAzimuth(distance, az);
    if (tmp.longitude() - _coord2.longitude() != 0)
        orthodromPath << QVariant::fromValue(QGeoCoordinate(getLatitude(tmp.longitude()), tmp.longitude(), 0));
    else
        orthodromPath <<  QVariant::fromValue(tmp);
}

