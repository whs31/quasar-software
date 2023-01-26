#ifndef MARKERMANAGER_H
#define MARKERMANAGER_H

#include <QObject>
#include <QVector>
#include <qqml.h>

#include "config/runtimedata.h"
#include "misc/debug.h"
#include "gui/markerdialog.h"
#include "map/linkerqml.h"

class MarkerManager : public QObject
{
    Q_OBJECT
public:
    static MarkerManager* initialize();

    static void newMarker(qreal latitude, qreal longitude, bool quiet = false);
    Q_INVOKABLE static void removeMarker(qint32 index);
    Q_INVOKABLE static void removeMarkerFromCoordinates(QGeoCoordinate coordinate);

signals:

private:
    explicit MarkerManager(QObject *parent = nullptr);
    static QVector<TMarker*> markerList;
    static MarkerManager* _instance;
};

#endif // MARKERMANAGER_H
