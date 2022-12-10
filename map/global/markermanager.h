#ifndef MARKERMANAGER_H
#define MARKERMANAGER_H

#include <QObject>
#include <QVector>
#include "models/tmarker.h"
#include "markerdialog.h"

class MarkerManager : public QObject
{
    Q_OBJECT
public:
    static void newMarker();

signals:

private:
    explicit MarkerManager(QObject *parent = nullptr);
    static QVector<TMarker> markerList;
};

#endif // MARKERMANAGER_H
