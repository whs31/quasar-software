#include "linkerqml.h"

QQuickItem *LinkerQML::map = nullptr;
LinkerQML *LinkerQML::_instance = nullptr;
LinkerQML::LinkerQML(QObject *parent) : QObject{parent} {}
LinkerQML *LinkerQML::initialize(QQuickItem *map)
{ 
    if (_instance != nullptr)
        return _instance;
    LinkerQML::map = map;
    _instance = new LinkerQML(); //TODO: add parent
    return _instance;
}
void LinkerQML::callDestructor(void)
{
    QMetaObject::invokeMethod(map, "destructor");
}
void LinkerQML::panGPS(void) { QMetaObject::invokeMethod(map, "panGPS"); }
void LinkerQML::clearRoute(void) { QMetaObject::invokeMethod(map, "clearRoute"); }
void LinkerQML::panImage() { QMetaObject::invokeMethod(map, "panImage"); }

void LinkerQML::fixedUpdate() { QMetaObject::invokeMethod(map, "fixedUpdate"); }

void LinkerQML::addModel(TMarker &marker)
{
    QMetaObject::invokeMethod(map, "addMarker", Q_ARG(QString, marker.name), Q_ARG(QColor, marker.color), Q_ARG(QString, marker.iconPath), Q_ARG(qreal, marker.latitude),
                              Q_ARG(qreal, marker.longitude), Q_ARG(qreal, marker.anchorX), Q_ARG(qreal, marker.anchorY), Q_ARG(qreal, marker.zoomLevel));
}
void LinkerQML::addModel(TImage &image)
{
    QVariantList metalist = {image.meta.latitude,
                             image.meta.longitude,
                             image.meta.dx,
                             image.meta.dy,
                             image.meta.x0,
                             image.meta.y0,
                             image.meta.angle,
                             image.meta.driftAngle,
                             image.meta.thetaAzimuth,
                             image.meta.lx,
                             image.realHeight};
    QStringList guilist = {image.gui.latitude,
                           image.gui.longitude,
                           image.gui.dx,
                           image.gui.dy,
                           image.gui.x0,
                           image.gui.y0,
                           image.gui.angle,
                           image.gui.driftAngle,
                           image.gui.lx,
                           image.gui.ly,
                           image.gui.thetaAzimuth,
                           image.gui.checksum,
                           image.gui.filename,
                           image.gui.creationTime};

    QMetaObject::invokeMethod(map, "addImage",
                              Q_ARG(QVariant, QVariant::fromValue(metalist)),
                              Q_ARG(QVariant, QVariant::fromValue(guilist)),
                              Q_ARG(QString, image.base64),
                              Q_ARG(bool, image.checksumMatch));
}

void LinkerQML::reconnect()             { emit signalReconnect(); } 
void LinkerQML::disconnect()            { emit signalDisconnect(); }
void LinkerQML::startFlightEmulator()   { QMetaObject::invokeMethod(map, "startEmulator"); }
void LinkerQML::removeMarker(int index) { QMetaObject::invokeMethod(map, "markerRemoveFromBackend", Q_ARG(QVariant, index)); }
