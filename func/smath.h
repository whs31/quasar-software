#ifndef SMATH_H
#define SMATH_H

#include <QObject>
#include <QtMath>

class SMath : public QObject
{
    Q_OBJECT
public:
    explicit SMath(QObject *parent = nullptr);

    static qreal DegreesToKilometers(qreal degrees);
    static qreal DegreesToMeters(qreal degrees);
    static qreal MetersToDegrees(qreal meters);

    static qreal MercatorZoomLevel(qreal dx, qreal latitude);

    static qreal Log(qreal base, qreal exponent);
    static qreal DegreesToRadians(qreal degrees);
    static qreal RadiansToDegrees(qreal radians);

signals:

private:
    static const qreal k_degreesToC;

};

#endif // SMATH_H
