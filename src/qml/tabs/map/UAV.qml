import QtQuick 2.15
import Network 1.0
import QtLocation 5.15
import QtPositioning 5.15

MapQuickItem {
    anchorPoint.x: 20;
    anchorPoint.y: 20;
    transform: Rotation {
        id: rotation;
        origin.x: 20;
        origin.y: 20;
        angle: Network.telemetry.course;
    }
    coordinate: QtPositioning.coordinate(Network.telemetry.latitude, Network.telemetry.longitude);
    z: 18;
    sourceItem: Item {
        Image {
            id: planeSource;
            layer.enabled: true;
            transformOrigin: Item.Center;
            smooth: true;
            source: "qrc:/map/items/gpsarrow.png";
            visible: true;
        }
    }
    Behavior on coordinate {
        CoordinateAnimation {
            duration: 250;
            easing.type: Easing.Linear;
        }
    }
}
