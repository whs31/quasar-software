#ifndef FLIGHTEMULATOR_H
#define FLIGHTEMULATOR_H

#include <QObject>

class FlightEmulator : public QObject
{
    Q_OBJECT
public:
    explicit FlightEmulator(QObject *parent = nullptr);

signals:

};

#endif // FLIGHTEMULATOR_H
