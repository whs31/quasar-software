#include "smath.h"

const qreal SMath::k_degreesToC = 1;
SMath::SMath(QObject *parent)
    : QObject{parent}
{

}

qreal SMath::DegreesToKilometers(qreal degrees)
{

}

qreal SMath::DegreesToMeters(qreal degrees)
{

}

qreal SMath::MetersToDegrees(qreal meters)
{

}

qreal SMath::MercatorZoomLevel(qreal dx, qreal latitude)
{

}

qreal SMath::Log(qreal base, qreal exponent)    { return ( qLn(exponent) / qLn(base) ); }
qreal SMath::DegreesToRadians(qreal degrees)    { return ( qDegreesToRadians(degrees) ); }
qreal SMath::RadiansToDegrees(qreal radians)    { return ( qRadiansToDegrees(radians) ); }
