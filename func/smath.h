#ifndef SMATH_H
#define SMATH_H

#include <QObject>
#include <QtMath>

class SMath : public QObject
{
    Q_OBJECT
public:
    explicit SMath(QObject *parent = nullptr);

    Q_INVOKABLE static qreal degreesToKilometers(qreal degrees);
    Q_INVOKABLE static qreal degreesToMeters(qreal degrees);
    Q_INVOKABLE static qreal metersToDegrees(qreal meters);

    Q_INVOKABLE static qreal mercatorZoomLevel(qreal dx, qreal latitude);

    Q_INVOKABLE static qreal log(qreal base, qreal exponent);
    Q_INVOKABLE static qreal degreesToRadians(qreal degrees);
    Q_INVOKABLE static qreal radiansToDegrees(qreal radians);

signals:

};

#endif // SMATH_H
