#ifndef LINKERQML_H
#define LINKERQML_H

#include <QObject>
#include <QQuickItem>
#include <QVector>
#include "models/tmarker.h"
#include "models/timage.h"

class LinkerQML : public QObject
{
public:
    static LinkerQML* initialize(QQuickItem* map);

    static void fixedUpdate();
    static void panGPS(void);
    static void clearRoute(void);
    static void panImage();

    static void addModel(TMarker& marker);
    static void addModel(TImage& image);

protected:
    static QQuickItem* map;

private:
    LinkerQML(QObject* parent = nullptr);
    static LinkerQML* _instance;

};

#endif // LINKERQML_H
