#ifndef MARKERMANAGER_H
#define MARKERMANAGER_H

#include <QObject>
#include <QVector>
#include <qqml.h>

#include "config/runtimedata.h"
#include "misc/debug.h"
#include "gui/markerdialog.h"
#include "map/linkerqml.h"
#include "gui/windows/markerwindowbackend.h"

class MarkerManager : public QObject
{
    Q_OBJECT
public:
    static MarkerManager* get(QObject *parent = Q_NULLPTR);

    void newMarker(qreal latitude, qreal longitude);
    Q_INVOKABLE void removeMarker(qint32 index);
    Q_INVOKABLE void removeMarkerFromCoordinates(QGeoCoordinate coordinate);

signals:

private:
    explicit MarkerManager(QObject *parent = nullptr);
    QVector<Marker*> markerList;
    static MarkerManager* _instance;

    Marker* markerPointer = nullptr;

private slots:
    void dialogReturn();
};

#endif // MARKERMANAGER_H
