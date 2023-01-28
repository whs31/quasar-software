#ifndef MARKERWINDOWBACKEND_H
#define MARKERWINDOWBACKEND_H

#include <QObject>
#include "config/runtimedata.h"

class MarkerWindowBackend : public QObject
{
    Q_OBJECT

public:
    static MarkerWindowBackend* get(QObject* parent = nullptr);

signals:

private:
    explicit MarkerWindowBackend(QObject *parent = nullptr);
    static MarkerWindowBackend* pointer;

};

#endif // MARKERWINDOWBACKEND_H
