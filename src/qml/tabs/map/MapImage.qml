import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

MapQuickItem  {
    anchorPoint.x: -x0;
    anchorPoint.y: ly / 2;
    z: 2;
    visible: shown;
    zoomLevel: mercator_zoom_level;
    property real m_opacity: transparency;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(latitude, longitude);
    sourceItem: Item {
        Loader {
            active: maptab_root.zoomLevel > 15 ||
                    maptab_root.visibleRegion.contains(QtPositioning.coordinate(latitude, longitude));
            asynchronous: true;
            sourceComponent: Image { id: imageSource;
                layer.enabled: true;
                layer.smooth: true;
                layer.samples: 8;
                asynchronous: true;
                transform: Rotation {
                    id: imageRotation;
                    origin.x: -x0;
                    origin.y: ly / 2;
                    angle: model.angle + drift_angle;
                }
                smooth: true;
                antialiasing: true;
                source: "file:///" + lod0;
            }
        }
    }
}
