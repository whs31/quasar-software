#ifndef LINKERQML_H
#define LINKERQML_H

#include <QObject>
#include <QQuickItem>
#include "models/tmarker.h"

class LinkerQML : public QObject
{
public:
    static void initialize(QQuickItem* map);

    static void clearImageArray(void);
    static void hideImage(QVariant i);
    static void showImage(QVariant i);
    static void addImage(double latitude, double longitude, float dx, float dy,
                  float x0, float y0, float angle, QString filename,
                  float height, QString base64encoding);
    static void fixedUpdate();
    static void panGPS(void);
    static void clearRoute(void);
    static void panImage(int filecounter);

    static void addModel(TMarker &marker);

protected:
    static QQuickItem* map;

private:
    LinkerQML();

};

#endif // LINKERQML_H
