#include "linkerqml.h"

LinkerQML::LinkerQML(QQuickItem* map) : map(map) { }
void LinkerQML::clearImageArray()                                               { QMetaObject::invokeMethod(map, "clearImageArray");                                                                    }
void LinkerQML::hideImage(QVariant i)                                           { QMetaObject::invokeMethod(map, "hideImage", Q_ARG(QVariant, i));                                                      }
void LinkerQML::showImage(QVariant i)                                           { QMetaObject::invokeMethod(map, "showImage", Q_ARG(QVariant, i));                                                      }

void LinkerQML::addImage(double latitude, double longitude, float dx, float dy, float x0, float y0, float angle, QString filename, float height)
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
                              Q_ARG(QVariant, height)
                              );
}
