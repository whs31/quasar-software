#include "linkerqml.h"

LinkerQML::LinkerQML(QQuickItem* map) : map(map) {

}

void LinkerQML::clearImageArray(void)                                               { QMetaObject::invokeMethod(map, "clearImageArray");                                                                    }
void LinkerQML::hideImage(QVariant i)                                               { QMetaObject::invokeMethod(map, "hideImage", Q_ARG(QVariant, i));                                                      }
void LinkerQML::showImage(QVariant i)                                               { QMetaObject::invokeMethod(map, "showImage", Q_ARG(QVariant, i));                                                      }
void LinkerQML::changeEnableTooltip(QVariant arg1)                                  { QMetaObject::invokeMethod(map, "changeEnableTooltip", Q_ARG(QVariant, arg1));                                         }
void LinkerQML::changeDrawRoute(QVariant arg1)                                      { QMetaObject::invokeMethod(map, "changeDrawRoute", Q_ARG(QVariant, arg1));                                             }
void LinkerQML::changeFollowPlane(QVariant arg1)                                    { QMetaObject::invokeMethod(map, "changeFollowPlane", Q_ARG(QVariant, arg1));                                           }
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

void LinkerQML::getTelemetry(float f1, float f2, float f3, float f4)
{
    QMetaObject::invokeMethod(map, "getTelemetry",
                              Q_ARG(QVariant, f1),
                              Q_ARG(QVariant, f2),
                              Q_ARG(QVariant, f3),
                              Q_ARG(QVariant, f4)
                              );
}

void LinkerQML::loadSettings(float predictRange, float diagramLength, float captureTime,
                             float thetaAzimuth, float driftAngle, QString antennaPosition,
                             QString path, bool testMode, bool usebase64)
{
    QMetaObject::invokeMethod(map, "loadSettings",
                              Q_ARG(QVariant, predictRange),
                              Q_ARG(QVariant, diagramLength),
                              Q_ARG(QVariant, captureTime),
                              Q_ARG(QVariant, thetaAzimuth),
                              Q_ARG(QVariant, driftAngle),
                              Q_ARG(QVariant, antennaPosition),
                              Q_ARG(QVariant, path),
                              Q_ARG(QVariant, testMode),
                              Q_ARG(QVariant, usebase64)
                              );
}
