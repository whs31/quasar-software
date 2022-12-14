#ifndef LINKERQML_H
#define LINKERQML_H

#include <QObject>
#include <QQuickItem>
#include "models/tmarker.h"

class LinkerQML : public QObject
{
public:
    static LinkerQML* initialize(QQuickItem* map);

    static void fixedUpdate();
    static void panGPS(void);
    static void clearRoute(void);
    static void panImage(int filecounter);

    static void addModel(TMarker &marker);

protected:
    static QQuickItem* map;

private:
    LinkerQML(QObject* parent = nullptr);
    static LinkerQML* _instance;

};

#endif // LINKERQML_H
