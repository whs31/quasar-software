#include "linkerqml.h"

LinkerQML::LinkerQML(QQuickItem* map) : map(map) {

}

void LinkerQML::clearImageArray(void)                                               { QMetaObject::invokeMethod(map, "clearImageArray");                                                                    }
void LinkerQML::hideImage(QVariant i)                                               { QMetaObject::invokeMethod(map, "hideImage", Q_ARG(QVariant, i));                                                      }
void LinkerQML::showImage(QVariant i)                                               { QMetaObject::invokeMethod(map, "showImage", Q_ARG(QVariant, i));                                                      }
void LinkerQML::panGPS(void)                                                        { QMetaObject::invokeMethod(map, "panGPS");                                                                             }
void LinkerQML::clearRoute(void)                                                    { QMetaObject::invokeMethod(map, "clearRoute");                                                                         }
void LinkerQML::panImage(int filecounter)                                           { QMetaObject::invokeMethod(map, "panImage", Q_ARG(QVariant, filecounter));                                             }


void LinkerQML::addImage(double latitude, double longitude, float dx, float dy, float x0, float y0, float angle, QString filename, float height, QString base64encoding)
{
    QMetaObject::invokeMethod(map, "addImage",
                              Q_ARG(QVariant, (float)latitude),
                              Q_ARG(QVariant, (float)longitude),
                              Q_ARG(QVariant, dx),
                              Q_ARG(QVariant, dy),
                              Q_ARG(QVariant, x0),
                              Q_ARG(QVariant, y0),
                              Q_ARG(QVariant, angle),
                              Q_ARG(QVariant, filename),
                              Q_ARG(QVariant, height),
                              Q_ARG(QVariant, base64encoding)
                              );
}

void LinkerQML::fixedUpdate()  { QMetaObject::invokeMethod(map, "fixedUpdate"); }
