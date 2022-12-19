#ifndef MARKERMANAGER_H
#define MARKERMANAGER_H

#include <QObject>
#include <QVector>

#include "qqml.h"
#include "debug.h"
#include "markerdialog.h"
#include "linkerqml.h"

class MarkerManager : public QObject
{
    Q_OBJECT
public:
    static MarkerManager* initialize();

    static void newMarker(qreal latitude, qreal longitude, bool quiet = false);
    Q_INVOKABLE static void removeMarker(qint32 index);

signals:

private:
    explicit MarkerManager(QObject *parent = nullptr);
    static QVector<TMarker*> markerList;
    static MarkerManager* _instance;
};

#endif // MARKERMANAGER_H
