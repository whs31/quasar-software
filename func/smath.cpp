#include "smath.h"

SMath::SMath(QObject *parent)
    : QObject{parent}
{
}

qreal SMath::degreesToKilometers(qreal degrees) { return (degrees * 111.111); }
qreal SMath::degreesToMeters(qreal degrees) { return (degrees * 111.111 * 1000); }
qreal SMath::metersToDegrees(qreal meters) { return (meters / (111.111 * 1000)); }
qreal SMath::mercatorZoomLevel(qreal dx, qreal latitude)
{
    if (dx == 0)
    {
        return log(2, 156543.03392 * qCos(latitude * M_PI / 180));
    }
    return log(2, 156543.03392 * qCos(latitude * M_PI / 180) / dx);
}
qreal SMath::log(qreal base, qreal exponent) { return (qLn(exponent) / qLn(base)); }
qreal SMath::degreesToRadians(qreal degrees) { return (qDegreesToRadians(degrees)); }
qreal SMath::radiansToDegrees(qreal radians) { return (qRadiansToDegrees(radians)); }

qreal SMath::mercatorToLongitude(qreal x, quint8 _zoom) {
    return x / qreal(1 << _zoom) * 360.0 - 180;
};

qreal SMath::mercatorToLatitude(qreal y, quint8 _zoom) {
    qreal n = M_PI *(1 - 2.0 * y / qreal(1 << _zoom));
    return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
};

QVector2D SMath::coordToMercator(QGeoCoordinate _point, quint8 _zoom)
{
    return QVector2D(static_cast<float>((1.0 - asinh(tan(_point.latitude() * M_PI / 180.0)) / M_PI) / 2.0 * (1 << _zoom)) ,
                     static_cast<float>((_point.longitude() + 180.0) / 360.0 * (1 << _zoom)));
};
