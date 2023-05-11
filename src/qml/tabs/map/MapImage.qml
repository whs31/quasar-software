import QtQuick 2.15
import QtLocation 5.12
import QtPositioning 5.12

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
        Image {
            id: imageSource;
            layer.enabled: true;
            transform: Rotation {
                id: imageRotation;
                origin.x: -x0;
                origin.y: ly / 2;
                angle: angle + drift_angle;
            }
            smooth: true;
            source: "file://" + lod0;
        }
    }
}
