#include "linkerqml.h"

QQuickItem* LinkerQML::map = nullptr;
LinkerQML* LinkerQML::_instance = nullptr;
LinkerQML::LinkerQML(QObject* parent) : QObject{parent} { }
LinkerQML* LinkerQML::initialize(QQuickItem* map)
{
    LinkerQML::map = map;
    if(_instance != nullptr)
        return _instance;
    _instance = new LinkerQML(); //@TODO add parent
    return _instance;
}
                                                    }
void LinkerQML::panGPS(void)                                                        { QMetaObject::invokeMethod(map, "panGPS");                                                                             }
void LinkerQML::clearRoute(void)                                                    { QMetaObject::invokeMethod(map, "clearRoute");                                                                         }
void LinkerQML::panImage(int filecounter)                                           { QMetaObject::invokeMethod(map, "panImage", Q_ARG(QVariant, filecounter));                                             }

void LinkerQML::fixedUpdate()  { QMetaObject::invokeMethod(map, "fixedUpdate"); }

void LinkerQML::addModel(TMarker &marker)
{
    QMetaObject::invokeMethod(map, "addMarker", Q_ARG(QString, marker.name), Q_ARG(QColor, marker.color), Q_ARG(QString, marker.iconPath), Q_ARG(qreal, marker.latitude),
                                                Q_ARG(qreal, marker.longitude), Q_ARG(qreal, marker.anchorX), Q_ARG(qreal, marker.anchorY), Q_ARG(qreal, marker.zoomLevel));
}
